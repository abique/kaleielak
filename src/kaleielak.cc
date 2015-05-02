#include <cassert>

#include "kaleielak.hh"
#include "transform.hh"

Kaleielak::Kaleielak(const std::string & config)
  : surface_(nullptr),
    cr_(nullptr),
    root_(nullptr),
    width_(100),
    height_(100)
{
  surface_ = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width_, height_);
  assert(surface_);

  cr_ = cairo_create(surface_);

  // prepare the root node
  Transform::Ptr tr = new Transform;
  tr->translate(-0.5, -0.5);
  tr->scale(width_, height_);
  root_ = tr;
}

Kaleielak::~Kaleielak()
{
  if (cr_)
    cairo_destroy(cr_);
  if (surface_)
    cairo_surface_destroy(surface_);
}
