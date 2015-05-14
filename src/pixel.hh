#ifndef PIXEL_HH
# define PIXEL_HH

struct Pixel
{
  inline Pixel(uint8_t _r = 0, uint8_t _g = 0, uint8_t _b = 0, uint8_t _a = 255)
    : b(_b), g(_g), r(_r), a(_a)
  {
  }

  uint8_t b;
  uint8_t g;
  uint8_t r;
  uint8_t a;
};

#endif /* !PIXEL_HH */
