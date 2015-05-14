#include "mandel1.hh"
#include "../mandelbrot.hh"
#include "../kaleielak.hh"

Mandel1::Mandel1(const Kaleielak & k)
  : Scene(k)
{
  auto mandel = new Mandelbrot(k.width_, k.height_,
                               0, 0, 1,
                               5, 50);
  mandel->palette_.add(0, Pixel(0, 0, 0, 255));
  mandel->palette_.add(20, Pixel(22, 115, 255, 255));
  mandel->palette_.add(20, Pixel(189, 255, 74, 255));
  mandel->palette_.add(20, Pixel(255, 201, 5, 255));
  mandel->palette_.scale(50);
  addChild(mandel);
}
