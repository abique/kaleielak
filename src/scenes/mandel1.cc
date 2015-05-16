#include "mandel1.hh"
#include "../mandelbrot.hh"
#include "../kaleielak.hh"

Mandel1::Mandel1(const Kaleielak & k)
  : Scene(k)
{
  int max_iter = 250;
  int power = 7;
  auto mandel = new Mandelbrot(k.width_, k.height_,
                               0, 0, 1.2,
                               power, max_iter);
  mandel->palette_.add(0, Pixel(0, 0, 0, 255));
  mandel->palette_.add(20, Pixel(22, 115, 255, 255));
  mandel->palette_.add(20, Pixel(189, 255, 74, 255));
  mandel->palette_.add(20, Pixel(255, 201, 5, 255));
  mandel->palette_.add(20, Pixel(220, 230, 200, 255));
  mandel->palette_.add(20, Pixel(18, 127, 64, 255));
  mandel->palette_.add(5, Pixel(75, 75, 75, 255));
  mandel->palette_.scale(max_iter);
  addChild(mandel);
}
