#include "audio-meter.hh"
#include "../rectangle.hh"
#include "../kaleielak.hh"

AudioMeter::AudioMeter(const Kaleielak &k)
  : Scene(k)
{
  Rectangle *rect = new Rectangle(0, new MulValue(&k.audio_rms_left_, 0.01), 1, 1);
  addChild(rect);
}
