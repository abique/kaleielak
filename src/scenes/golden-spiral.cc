#include "golden-spiral.hh"
#include "../arc.hh"
#include "../rectangle.hh"

GoldenSpiral::GoldenSpiral(const Kaleielak & k)
  : Scene(k)
{
  double u0 = 0.000;
  double u1 = 0.010;
  double u2;
  double x = 0;
  double y = 0;
  double angle = 0;

  for (int i = 0; i < 10; ++i) {
    addChild(new Arc(x, y, u1, angle, angle + M_PI / 2));

    switch (i % 4) {
    case 0: y -= u0; break;
    case 1: x += u0; break;
    case 2: y += u0; break;
    case 3: x -= u0; break;
    }

    u2 = u0 + u1;
    u0 = u1;
    u1 = u2;
    angle += M_PI / 2;
  }
}
