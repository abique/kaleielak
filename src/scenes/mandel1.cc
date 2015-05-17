#include "mandel1.hh"
#include "../mandelbrot.hh"
#include "../kaleielak.hh"

Mandel1::Mandel1(const Kaleielak & k)
  : Scene(k)
{
  auto mandel = new Mandelbrot(k.width_, k.height_);
  mandel->x_ = 0;
  mandel->y_ = 0;
  mandel->scale_ = 1.2;
  mandel->power_ = 7;
  mandel->max_iter_ = 250;

  mandel->palette_.add(0, Pixel(0, 0, 0, 255));
  mandel->palette_.add(20, Pixel(22, 115, 255, 255));
  mandel->palette_.add(20, Pixel(189, 255, 74, 255));
  mandel->palette_.add(20, Pixel(255, 201, 5, 255));
  mandel->palette_.add(20, Pixel(220, 230, 200, 255));
  mandel->palette_.add(20, Pixel(18, 127, 64, 255));
  mandel->palette_.add(5, Pixel(75, 75, 75, 255));
  mandel->palette_.scale(mandel->max_iter_);
  addChild(mandel);
}
