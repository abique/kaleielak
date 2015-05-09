#include <cassert>
#include <cstdlib>

extern "C" {
#include <libavcodec/avcodec.h>
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
    codec_(nullptr),
    codec_ctx_(nullptr),
    frame_(nullptr),
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
  codec_ctx_->pix_fmt = AV_PIX_FMT_YUV420P;//AV_PIX_FMT_0RGB;
  codec_ctx_->gop_size = 10;
  codec_ctx_->max_b_frames = 1;
  codec_ctx_->bit_rate = 400000;

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

  frame_ = av_frame_alloc();
  if (!frame_) {
    mimosa::log::fatal("failed to allocate a frame");
    std::abort();
  }

  int ret = av_image_alloc(frame_->data, frame_->linesize,
                           width, height, AV_PIX_FMT_YUV420P, 32);
  if (ret < 0) {
    mimosa::log::fatal("could not allocate an image buffer");
    std::abort();
  }
  frame_->width = width;
  frame_->height = height;
  frame_->format = AV_PIX_FMT_YUV420P;

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
  av_frame_free(&frame_);
  avcodec_free_context(&codec_ctx_);
}

void
VideoEncoder::encode(unsigned char *data)
{
  av_init_packet(&packet_);
  packet_.data = nullptr;
  packet_.size = 0;

  //memcpy(frame_->data[0], data, 4 * width_ * height_);
  //frame_->data[0] = data;
  frame_->pts = frame_count_;

  int got_packet = 0;
  int ret = avcodec_encode_video2(codec_ctx_, &packet_, frame_, &got_packet);
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
