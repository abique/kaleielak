#include <cassert>

#include <mimosa/options/options.hh>
#include <mimosa/log/log.hh>

#include "kaleielak.hh"
#include "transform.hh"
#include "scene.hh"
#include "scene-factory.hh"

std::string &SCENE = *mimosa::options::addOption<std::string>(
  "scene", "scene", "", "GoldenFlower");
bool &LIST_SCENES = *mimosa::options::addSwitch(
  "scene", "list-scenes", "list all the scenes");

const std::string &TARGET = *mimosa::options::addOption<std::string>(
  "rendering", "target", "movie, x11, png", "x11");
const std::string &OUT = *mimosa::options::addOption<std::string>(
  "rendering", "out", "output filename", "out.mp4");
const uint32_t &WIDTH = *mimosa::options::addOption<uint32_t>(
  "rendering", "width", "", 400);
const uint32_t &HEIGHT = *mimosa::options::addOption<uint32_t>(
  "rendering", "height", "", 400);
const uint32_t &FPS = *mimosa::options::addOption<uint32_t>(
  "rendering", "fps", "frames per seconds", 30);
const uint32_t &LENGTH = *mimosa::options::addOption<uint32_t>(
  "rendering", "length", "duration in seconds", 10);

const std::string &AUDIO_IN = *mimosa::options::addOption<std::string>(
  "input", "audio-in", "audio file to be played with the video", "");

Kaleielak::Kaleielak(const std::string & config)
  : surface_(nullptr),
    cr_(nullptr),
    root_(nullptr),
    width_(WIDTH),
    height_(HEIGHT),
    fps_(FPS),
    frame_(0),
    video_(TARGET == "movie" ? new VideoEncoder(OUT, WIDTH, HEIGHT, FPS) : nullptr),
    audio_file_(AUDIO_IN)
{
  // load audio data
  if (audio_file_) {
    audio_data_ = (float *)::malloc(sizeof (*audio_data_) * audio_file_.channels() * audio_file_.frames());
    audio_file_.readf(audio_data_, audio_file_.frames());
  }

  surface_ = cairo_image_surface_create(CAIRO_FORMAT_RGB24, width_, height_);
  assert(surface_);

  cr_ = cairo_create(surface_);
  assert(cr_);

  // best anti aliasing
  cairo_set_antialias(cr_, CAIRO_ANTIALIAS_BEST);

  // prepare the root node
  Transform *tr = new Transform;
  tr->scale(width_, height_);
  tr->translate(0.5, 0.5);

  auto scene = SceneFactory::create(SCENE, *this);
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
Kaleielak::render()
{
  for (frame_ = 0; true; ++frame_) {
    if (!(frame_ % FPS))
      mimosa::log::info("frame %d", frame_);

    mimosa::log::info("painting");

    draw();

    mimosa::log::info("rendering to target");

    if (TARGET == "movie") {
      video_->encode(cairo_image_surface_get_data(surface_));
      if (frame_ >= LENGTH * FPS)
        break;
    } else if (TARGET == "png") {
      cairo_surface_write_to_png(surface_, OUT.c_str());
      break;
    } else {
      mimosa::log::error("Unknown target: %s", TARGET);
      break;
    }
  }
}

void
Kaleielak::draw()
{
  cairo_set_source_rgb(cr_, 0, 0, 0);
  cairo_paint(cr_);

  cairo_set_source_rgb(cr_, 1, 0.95, 0.15);
  cairo_set_line_width(cr_, 0.001);
  root_->draw(cr_);
  cairo_surface_flush(surface_);
}
