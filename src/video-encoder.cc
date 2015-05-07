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
}

VideoEncoder::~VideoEncoder()
{
}

void
VideoEncoder::encode(unsigned char *data)
{
}
