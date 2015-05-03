#ifndef VIDEO_ENCODER_HH
# define VIDEO_ENCODER_HH

# include <cstdint>
# include <string>

# include <vpx/vpx_encoder.h>
# include <vpx/vp8cx.h>

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
  const std::string    filename_;
  const uint32_t       width_;
  const uint32_t       height_;
  const uint32_t       fps_;

  const vpx_codec_iface_t *iface_;
  vpx_codec_ctx_t          ctx_;
  vpx_codec_enc_cfg_t      cfg_;

  int                  frame_;
};

#endif /* !VIDEO_ENCODER_HH */
