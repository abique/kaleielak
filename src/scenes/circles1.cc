#include "circles1.hh"
#include "../kaleielak.hh"
#include "../circle.hh"
#include "../repeat.hh"

Circles1::Circles1(const Kaleielak & k)
  : Scene(k)
{
  RepeatedTransform *rep = new RepeatedTransform(12);
  rep->rotate(2 * M_PI / 12);

  ValueBuilder v;
  v = v + 1 + &rep->i_;
  v = v / &rep->count_ * &kaleielak_.frame_ * 0.002 + 0.10;
  rep->addChild(new Circle(0, 0.3, v.get()));

  addChild(rep);
}
