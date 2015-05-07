#ifndef SCENE_HH
# define SCENE_HH

# include <string>

# include "node.hh"

class Kaleielak;

class Scene : public Node
{
public:
  inline Scene(const Kaleielak & k) : Node(), kaleielak_(k) {}

  inline virtual std::string name() const { return "(no name)"; }

protected:
  const Kaleielak & kaleielak_;
};

#endif /* !SCENE_HH */
