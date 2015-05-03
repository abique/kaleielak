#include <mimosa/init.hh>

#include "kaleielak.hh"

int main(int argc, char **argv)
{
  mimosa::init(argc, argv);

  Kaleielak k("");
  for (int i = 0; i < 50; ++i)
    k.draw();

  mimosa::deinit();
  return 0;
}
