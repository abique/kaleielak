#include <cassert>
#include <cstdlib>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libavutil/common.h>
#include <libavutil/imgutils.h>
}

#include "mimosa/log/log.hh"

#include "video-encoder.hh"

VideoEncoder::VideoEncoder(const std::string & filename,
                           uint32_t            width,
                           uint32_t            height,
                           uint32_t            fps)
  : filename_(filename),
    width_(width),
    height_(height),
    fps_(fps),
    src_fmt_(AV_PIX_FMT_RGB32),
    dst_fmt_(AV_PIX_FMT_YUV420P),
    codec_(nullptr),
    codec_ctx_(nullptr),
    src_frame_(nullptr),
    dst_frame_(nullptr),
    sws_(nullptr),
    frame_count_(0)
{
  codec_ = avcodec_find_encoder(AV_CODEC_ID_H264);
  if (!codec_) {
    mimosa::log::fatal("failed to open the codec");
    std::abort();
  }

  codec_ctx_ = avcodec_alloc_context3(codec_);
  if (!codec_ctx_) {
    mimosa::log::fatal("failed to allocate codec context");
    std::abort();
  }

  codec_ctx_->width = width;
  codec_ctx_->height = height;
  codec_ctx_->time_base.num = 1;
  codec_ctx_->time_base.den = fps;
  codec_ctx_->pix_fmt = dst_fmt_;
  codec_ctx_->gop_size = 4;
  codec_ctx_->max_b_frames = 1;
  codec_ctx_->bit_rate = 1200000;

  if (avcodec_open2(codec_ctx_, codec_, nullptr) < 0) {
    mimosa::log::fatal("failed to instantiate the codec");
    std::abort();
  }

  stream_ = mimosa::stream::FdStream::openFile(filename.c_str(),
                                               O_CREAT | O_WRONLY | O_TRUNC);
  if (!stream_) {
    mimosa::log::fatal("failed to open %s", filename);
    std::abort();
  }

  src_frame_ = av_frame_alloc();
  if (!src_frame_) {
    mimosa::log::fatal("failed to allocate a frame");
    std::abort();
  }

  src_frame_->linesize[0] = 4 * width;
  src_frame_->width = width;
  src_frame_->height = height;
  src_frame_->format = src_fmt_;

  dst_frame_ = av_frame_alloc();
  if (!dst_frame_) {
    mimosa::log::fatal("failed to allocate a frame");
    std::abort();
  }

  int ret = av_image_alloc(dst_frame_->data, dst_frame_->linesize,
                           width, height, dst_fmt_, 32);
  if (ret < 0) {
    mimosa::log::fatal("could not allocate an image buffer");
    std::abort();
  }
  dst_frame_->width = width;
  dst_frame_->height = height;
  dst_frame_->format = dst_fmt_;

  sws_ = sws_getContext(width, height, src_fmt_,
                        width, height, dst_fmt_,
                        0, nullptr, nullptr, nullptr);
  if (!sws_) {
    mimosa::log::fatal("failed to create the scaling context");
    std::abort();
  }

  memset(&packet_, 0, sizeof (packet_));
}

VideoEncoder::~VideoEncoder()
{
  for (int got_packet = 1; got_packet;) {
    int ret = avcodec_encode_video2(codec_ctx_, &packet_, nullptr, &got_packet);
    if (ret < 0) {
      mimosa::log::fatal("failed to encode video");
      std::abort();
    }

    if (got_packet) {
      if (stream_->loopWrite((const char *)packet_.data, packet_.size) != packet_.size) {
        mimosa::log::fatal("write error: %s", strerror(errno));
        std::abort();
      }
      av_free_packet(&packet_);
    }
  }

  src_frame_->data[0] = nullptr;
  av_frame_free(&src_frame_);
  av_frame_free(&dst_frame_);
  avcodec_free_context(&codec_ctx_);
}

void
VideoEncoder::encode(unsigned char *data)
{
  av_init_packet(&packet_);
  packet_.data = nullptr;
  packet_.size = 0;

  src_frame_->data[0] = data;
  sws_scale(sws_, src_frame_->data, src_frame_->linesize,
            0, height_, dst_frame_->data, dst_frame_->linesize);
  dst_frame_->pts = frame_count_;

  // convert

  int got_packet = 0;
  int ret = avcodec_encode_video2(codec_ctx_, &packet_, dst_frame_, &got_packet);
  if (ret < 0) {
    mimosa::log::fatal("failed to encode video");
    std::abort();
  }

  if (got_packet) {
    if (stream_->loopWrite((const char *)packet_.data, packet_.size) != packet_.size) {
      mimosa::log::fatal("write error: %s", strerror(errno));
      std::abort();
    }
    av_free_packet(&packet_);
  }
  ++frame_count_;
}
