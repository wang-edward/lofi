#pragma once

#include "Gamma/SamplePlayer.h"
#include "Gamma/Envelope.h"
#include "al/graphics/al_Shapes.hpp"
#include <iostream>
#include <random>
#include <cstdlib>

#include "plugins/Plugin.hpp"
namespace box {

class Sample : Plugin {
public:
  Sample (const char* _path, float _gain);
  Sample (Sample& s); // copy constructor
  Sample& operator=(Sample& s); // copy assignment operator
  Sample(Sample&& s); // move constructor
  Sample& operator=(Sample&& s); // move assignment operator
  
  void update_gain(float _gain);
  void update_envelope(float a, float d, float s, float r);

  void onProcess(al::AudioIOData& io) override;
  void onProcess(al::Graphics& g) override;
  void onTriggerOn(al::Keyboard const &k) override;
  void onTriggerOff(al::Keyboard const &k) override;
private:
  const char* path;
  float gain;

  gam::SamplePlayer<> player;
  gam::ADSR<> envelope;
    
  void load_path(const char* _path);
  void reset_color();
    
};

}
