#ifndef KALEIELAK_HH
# define KALEIELAK_HH

# include <cstdint>
# include <string>

# include <cairo/cairo.h>

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

  cairo_surface_t *surface_;
  cairo_t         *cr_;
  Transform       *root_;

  uint32_t width_;
  uint32_t height_;
  uint32_t fps_;
  uint32_t frame_;

  VideoEncoder video_;
};

#endif /* !KALEIELAK_HH */
