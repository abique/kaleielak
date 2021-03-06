#ifndef KALEIELAK_HH
# define KALEIELAK_HH

# include <cstdint>
# include <string>
# include <memory>

# include <cairo/cairo.h>

# include <sndfile.hh>
# include <fftw3.h>

# include "node.hh"
# include "transform.hh"
# include "video-encoder.hh"

class Kaleielak
{
public:
  Kaleielak(const std::string & config);
  ~Kaleielak();

  void draw();
  void render();
  void calculateVolume();
  void syncAudio();

  cairo_surface_t *surface_;
  cairo_t         *cr_;
  Transform       *root_;

  uint32_t width_;
  uint32_t height_;
  uint32_t fps_;
  uint32_t frame_;

  std::unique_ptr<VideoEncoder> video_;

  SndfileHandle  audio_file_;
  float         *audio_data_ = nullptr;
  float         *audio_rms_  = nullptr;
  int32_t        audio_rms_window_ = 2205;
  int32_t        audio_rms_num_windows_ = 0;
  int32_t        audio_rms_index_ = 0;
  float          audio_rms_left_ = 0;
  float          audio_rms_right_ = 0;
};

#endif /* !KALEIELAK_HH */
