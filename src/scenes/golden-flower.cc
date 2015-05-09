#include "golden-flower.hh"
#include "golden-spiral.hh"
#include "../repeat.hh"
#include "../rotation.hh"
#include "../kaleielak.hh"
#include "../color.hh"

GoldenFlower::GoldenFlower(const Kaleielak & k)
  : Scene(k)
{
  const uint32_t nb = 3;
  RepeatedTransform *rep = new RepeatedTransform(nb);
  rep->rotate(2 * M_PI / (double)nb);

  auto *color = new Color(
    (V(0.7) + (V(0.3) * new SinValue((V(&k.frame_) / k.fps_).get())).get()).get(),
    (V(0.5) + (V(0.4) * new SinValue((V(&k.frame_) / k.fps_ / 2).get())).get()).get(),
    (V(0.3) + (V(0.2) * new SinValue((V(&k.frame_) / k.fps_ / 3).get())).get()).get());
  color->addChild(new GoldenSpiral(k));
  rep->addChild(color);

  auto angle = ValueBuilder(M_PI / 50.0) * &k.frame_;
  auto rot = new Rotation(angle.get());
  rot->addChild(rep);
  addChild(rot);

  auto t = new Transform;
  t->m_.xx = -1;
  t->addChild(rep);
  rot = new Rotation((-angle / 2).get());
  rot->addChild(t);
  addChild(rot);
}
