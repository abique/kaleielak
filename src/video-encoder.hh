#ifndef VIDEO_ENCODER_HH
# define VIDEO_ENCODER_HH

# include <cstdint>
# include <string>

extern "C" {
# include <libavcodec/avcodec.h>
# include <libswscale/swscale.h>
}

# include <mimosa/stream/fd-stream.hh>

class VideoEncoder
{
public:
  VideoEncoder(const std::string & filename,
               uint32_t            width,
               uint32_t            height,
               uint32_t            fps);
  ~VideoEncoder();

  void encode(unsigned char *data);

private:
  /* settings */
  const std::string filename_;
  const uint32_t    width_;
  const uint32_t    height_;
  const uint32_t    fps_;
  AVPixelFormat     src_fmt_;
  AVPixelFormat     dst_fmt_;

  /* ffmpeg */
  AVCodec                       *codec_;
  AVCodecContext                *codec_ctx_;
  AVFrame                       *src_frame_;
  AVFrame                       *dst_frame_;
  AVPacket                       packet_;
  SwsContext                    *sws_;
  mimosa::stream::FdStream::Ptr  stream_;

  /* state */
  int64_t frame_count_;
};

#endif /* !VIDEO_ENCODER_HH */
