#pragma once

#include <cmath>

#include "pixel.hh"

class Palette
{
public:
  inline Pixel color(int index) const { return pixels_[index % pixels_.size()]; }
  inline Pixel gradient(float alpha) const
  {
     float a = alpha * pixels_.size();
     uint32_t b = std::floor(a);
     float c = a - b;
     float d = (1 - c);

     const Pixel &p0 = pixels_[b % pixels_.size()];
     const Pixel &p1 = pixels_[(b + 1) % pixels_.size()];
     return Pixel(p0.r * d + p1.r * c,
                  p0.g * d + p1.g * c,
                  p0.b * d + p1.b * c,
                  p0.a * d + p1.a * c);
  }

  inline void add(Pixel p) {
      pixels_.push_back(p);
  }

  std::vector<Pixel> pixels_;
};
