#ifndef PALETTE_HH
# define PALETTE_HH

# include "pixel.hh"

class Palette
{
public:
  inline Pixel color(int index) const { return pixels_[index % pixels_.size()]; }

  inline void add(int offset, Pixel p) {
    if (pixels_.empty()) {
      pixels_.push_back(p);
      return;
    }

    Pixel p0 = pixels_.back();

    double ar = (p.a - p0.a) / (double)offset;
    double rr = (p.r - p0.r) / (double)offset;
    double gr = (p.g - p0.g) / (double)offset;
    double br = (p.b - p0.b) / (double)offset;

    for (int i = 0; i < offset; ++i) {
      p0.a += ar;
      p0.r += rr;
      p0.g += gr;
      p0.b += br;
      pixels_.push_back(p0);
    }
  }

  void scale(int size) {
    Palette p;
    p.pixels_.resize(size);
    p.pixels_.front() = pixels_.front();
    p.pixels_.back() = pixels_.back();

    double s = ((double)pixels_.size()) / (double)size;
    for (int i = 1; i < size - 1; ++i) {
      //Pixel p0 = pixels_[s * (i - 1)];
      Pixel p1 = pixels_[s * i];

      p.pixels_[i] = p1;
    }

    std::swap(p.pixels_, pixels_);
  }

  std::vector<Pixel> pixels_;
};

#endif /* !PALETTE_HH */
