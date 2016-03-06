#include "julia1.hh"
#include "../julia.hh"
#include "../kaleielak.hh"

Julia1::Julia1(const Kaleielak & k)
  : Scene(k)
{
  auto julia = new Julia(k.width_, k.height_);
  julia->x_ = -0.026 + 4e-05 + 2.5e-7 - 2e-09 - 1.5538e-10 + 1.6e-14;
  julia->y_ = 0.065 - 5e-05 + 2.5e-7 - 8e-09 - 2.15e-14;
  julia->scale_ = Value(new MulValue(1.7, new PowValue(0.99, &k.frame_)));
  julia->iter_limit_ = 1000000;
  julia->cutoff_ = 8;
  /*julia->rpoly_ = [&k] (std::complex<double> z) {
    return z * z + std::complex<double>(
      -0.835 + 0.00015 * k.frame_, -0.2321 + 0.00007 * k.frame_);
  };*/
  julia->rpoly_ = [] (std::complex<Julia::float_type> z) {
      return z * z + std::complex<Julia::float_type>(-0.835, -0.2321);
    };

  julia->palette_.add(Pixel(0, 0, 0, 255));
  julia->palette_.add(Pixel(0, 10, 22, 255));
  julia->palette_.add(Pixel(0, 20, 50, 255));
  julia->palette_.add(Pixel(1, 33, 97, 255));
  julia->palette_.add(Pixel(13, 156, 212, 255));
  julia->palette_.add(Pixel(255, 0, 0, 255));
  julia->palette_.add(Pixel(255, 162, 0, 255));
  julia->palette_.add(Pixel(134, 53, 255, 255));
  julia->palette_.add(Pixel(255, 243, 106, 255));
  julia->palette_.add(Pixel(13, 123, 24, 255));
  julia->palette_.add(Pixel(255, 255, 255, 255));
  addChild(julia);
}
