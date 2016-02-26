#include <cmath>
#include <iostream>

extern "C" {
#include <libavutil/opt.h>
#include <libavcodec/avcodec.h>
#include <libavutil/channel_layout.h>
#include <libavutil/common.h>
#include <libavutil/imgutils.h>
#include <libavutil/mathematics.h>
#include <libavutil/samplefmt.h>
}


#include <mimosa/init.hh>

#include "kaleielak.hh"

int main(int argc, char **argv)
{
  mimosa::init(argc, argv);

  /* register all the codecs */
  avcodec_register_all();

  Kaleielak k("");
  k.render();

  mimosa::deinit();
  return 0;
}
