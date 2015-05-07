#include "circles1.hh"
#include "../kaleielak.hh"
#include "../circle.hh"
#include "../repeat.hh"

Circles1::Circles1(const Kaleielak & k)
  : Scene(k)
{
  RepeatedTransform *rep = new RepeatedTransform(12);
  rep->rotate(2 * M_PI / 12);

  AbstractValue *v = new AddValue(&rep->i_, 1);
  v = new DivValue(v, &rep->count_);
  v = new MulValue(v, &kaleielak_.frame_);
  v = new AddValue(0.10, new MulValue(0.005, v));
  rep->addChild(new Circle(0, 0.3, v));

  addChild(rep);
}
