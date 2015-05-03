#include <cassert>

#include "kaleielak.hh"
#include "transform.hh"
#include "circle.hh"
#include "repeat.hh"

Kaleielak::Kaleielak(const std::string & config)
  : surface_(nullptr),
    cr_(nullptr),
    root_(nullptr),
    width_(800),
    height_(800),
    fps_(30),
    frame_(0),
    video_("video.vp9", width_, height_, fps_)
{
  surface_ = cairo_image_surface_create(CAIRO_FORMAT_RGB24, width_, height_);
  assert(surface_);

  cr_ = cairo_create(surface_);
  assert(cr_);

  // prepare the root node
  Transform *tr = new Transform;
  tr->scale(width_, height_);
  tr->translate(0.5, 0.5);

  RepeatedTransform *rep = new RepeatedTransform(12);
  rep->rotate(2 * M_PI / 12);
  AbstractValue *v = new AddValue(&rep->i_, 1);
  v = new DivValue(v, &rep->count_);
  v = new MulValue(v, &frame_);
  v = new AddValue(0.10, new MulValue(0.005, v));
  rep->addChild(new Circle(0, 0.3, v));
  tr->addChild(rep);

  root_ = tr;
}

Kaleielak::~Kaleielak()
{
  delete root_;

  if (cr_)
    cairo_destroy(cr_);
  if (surface_)
    cairo_surface_destroy(surface_);
}

void
Kaleielak::draw()
{
  char filename[64];

  snprintf(filename, sizeof (filename), "out-%06d.png", frame_);

  cairo_set_source_rgb(cr_, 0, 0, 0);
  cairo_paint(cr_);

  cairo_set_source_rgb(cr_, 1, 0.95, 0.15);
  cairo_set_line_width(cr_, 0.01);
  root_->draw(cr_);
  cairo_surface_flush(surface_);
  cairo_surface_write_to_png(surface_, filename);
  video_.encode(cairo_image_surface_get_data(surface_));

  ++frame_;
}
