#include <stdexcept>

#include "scene-factory.hh"
#include "scenes/circles1.hh"

Scene *
SceneFactory::create(const std::string & name, Kaleielak & k)
{
  if (name == "circles1")
    return new Circles1(k);
  throw std::invalid_argument("scene not found: " + name);
  return nullptr;
}
