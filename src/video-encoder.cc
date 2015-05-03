#include <cassert>

#include "video-encoder.hh"

VideoEncoder::VideoEncoder(const std::string & filename,
                           uint32_t            width,
                           uint32_t            height,
                           uint32_t            fps)
  : filename_(filename),
    width_(width),
    height_(height),
    fps_(fps),
    frame_(0)
{
  vpx_codec_err_t res;

  iface_ = vpx_codec_vp9_cx();
  assert(iface_);

  res = vpx_codec_enc_config_default(iface_, &cfg_, 0);
  assert(res == VPX_CODEC_OK);

  cfg_.g_w = width;
  cfg_.g_h = height;
  cfg_.g_timebase.num = 1;
  cfg_.g_timebase.den = fps;

  res = vpx_codec_enc_init(&ctx_, iface_, &cfg_, 0);
  assert(res == VPX_CODEC_OK);
}

VideoEncoder::~VideoEncoder()
{
  vpx_codec_destroy(&ctx_);
}

void
VideoEncoder::encode(unsigned char *data)
{
  vpx_codec_err_t res;
  vpx_image_t     img;

  vpx_img_wrap(NULL, VPX_IMG_FMT_RGB24, width_, height_, 1, data);
  res = vpx_codec_encode(&ctx_, &img, frame_, 1, 0, VPX_DL_GOOD_QUALITY);
  if (res != VPX_CODEC_OK)
    fprintf(stderr, "encode: %s\n", vpx_codec_err_to_string(res));

  assert(res == VPX_CODEC_OK);
}
