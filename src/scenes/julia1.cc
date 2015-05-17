#include "julia1.hh"
#include "../julia.hh"
#include "../kaleielak.hh"

Julia1::Julia1(const Kaleielak & k)
  : Scene(k)
{
  auto julia = new Julia(k.width_, k.height_);
  julia->x_ = 0;
  julia->y_ = 0;
  julia->scale_ = 1.7;
  julia->max_iter_ = 1500;
  julia->cutoff_ = 80;
  julia->rpoly_ = [&k] (std::complex<double> z) {
    return z * z + std::complex<double>(
      -0.835 + 0.0003 * k.frame_, -0.2321 + 0.00014 * k.frame_);
  };

  julia->palette_.add(10, Pixel(0, 0, 0, 255));
  julia->palette_.add(10, Pixel(22, 115, 255, 255));
  julia->palette_.add(20, Pixel(189, 255, 74, 255));
  julia->palette_.add(20, Pixel(130, 201, 170, 255));
  julia->palette_.add(20, Pixel(160, 230, 200, 255));
  julia->palette_.add(20, Pixel(180, 127, 64, 255));
  julia->palette_.scale(julia->max_iter_);
  addChild(julia);
}