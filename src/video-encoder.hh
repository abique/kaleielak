#ifndef VIDEO_ENCODER_HH
# define VIDEO_ENCODER_HH

# include <cstdint>
# include <string>

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


  int                  frame_;
};

#endif /* !VIDEO_ENCODER_HH */
