#include <mimosa/init.hh>

#include "kaleielak.hh"

int main(int argc, char **argv)
{
  mimosa::init(argc, argv);

  Kaleielak k("");

  mimosa::deinit();
  return 0;
}