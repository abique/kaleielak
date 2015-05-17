#include <stdexcept>
#include <string>
#include <functional>
#include <iostream>

#include "scene-factory.hh"
#include "scenes/circles1.hh"
#include "scenes/golden-flower.hh"
#include "scenes/golden-spiral.hh"
#include "scenes/mandel1.hh"
#include "scenes/julia1.hh"

struct {
  std::string name;
  std::function<Scene *(Kaleielak & k)> create;
} entries[] = {

#define ENTRY(Name)                                             \
  { #Name, [] (Kaleielak & k) { return new Name(k); } }

  ENTRY(Circles1),
  ENTRY(GoldenFlower),
  ENTRY(GoldenSpiral),
  ENTRY(Mandel1),
  ENTRY(Julia1),
};

void
SceneFactory::list()
{
  for (auto & entry : entries)
    std::cout << entry.name << std::endl;
}

Scene *
SceneFactory::create(const std::string & name, Kaleielak & k)
{
  for (auto & entry : entries)
    if (entry.name == name)
      return entry.create(k);
  throw std::invalid_argument("scene not found: " + name);
  return nullptr;
}
