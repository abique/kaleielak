#include <cassert>

#include <mimosa/options/options.hh>

#include "kaleielak.hh"
#include "transform.hh"
#include "scene.hh"
#include "scene-factory.hh"

std::string &SCENE = *mimosa::options::addOption<std::string>(
  "scene", "scene", "", "");
bool &LIST_SCENES = *mimosa::options::addSwitch(
  "scene", "list-scenes", "list all the scenes");

const std::string &TARGET = *mimosa::options::addOption<std::string>(
  "rendering", "target", "movie, x11", "x11");
const std::string &OUT = *mimosa::options::addOption<std::string>(
  "rendering", "out", "output filename", "out.mp4");
const uint32_t &WIDTH = *mimosa::options::addOption<uint32_t>(
  "rendering", "width", "", 400);
const uint32_t &HEIGHT = *mimosa::options::addOption<uint32_t>(
  "rendering", "height", "", 400);
const uint32_t &FPS = *mimosa::options::addOption<uint32_t>(
  "rendering", "fps", "frames per seconds", 30);

Kaleielak::Kaleielak(const std::string & config)
  : surface_(nullptr),
    cr_(nullptr),
    root_(nullptr),
    width_(WIDTH),
    height_(HEIGHT),
    fps_(FPS),
    frame_(0),
    video_(OUT, HEIGHT, WIDTH, FPS)
{
  surface_ = cairo_image_surface_create(CAIRO_FORMAT_RGB24, width_, height_);
  assert(surface_);

  cr_ = cairo_create(surface_);
  assert(cr_);

  // prepare the root node
  Transform *tr = new Transform;
  tr->scale(width_, height_);
  tr->translate(0.5, 0.5);

  auto scene = SceneFactory::create("circles1", *this);
  tr->addChild(scene);

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
