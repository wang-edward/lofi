#pragma once

#include "core/Plugin.hpp"
#include "plugins/SineEnv.hpp"

#include "al/scene/al_PolySynth.hpp"
#include "al/app/al_App.hpp"

#include "serial/CompositeData.hpp"
// #include "utils/Utils.h"

namespace lofi {

class Keyboard : public Plugin {

public:

  Keyboard();
  void onProcess(al::AudioIOData &io);
  void onProcess(al::Graphics& g);
  void onTriggerOn(const al::Keyboard &k);
  void onTriggerOff(const al::Keyboard &k);
  void updateParameters(const CompositeData& c);
  void updateFilterFreq(float v);

private:
  al::PolySynth mSynth;
  float mFilterFreq = 200;
 WAVEFORM mGlobalWaveform = WAVEFORM::SQUARE;
 float mVolume = 0.5;
};

} // namespace lofi
