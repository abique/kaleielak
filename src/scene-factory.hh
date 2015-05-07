#ifndef SCENE_FACTORY_HH
# define SCENE_FACTORY_HH

# include <string>

class Kaleielak;
class Scene;

class SceneFactory
{
public:
  static Scene *create(const std::string & name, Kaleielak & k);
};

#endif /* !SCENE_FACTORY_HH */
