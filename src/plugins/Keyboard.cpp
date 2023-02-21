#include "plugins/Keyboard.hpp"
#include <iostream>

namespace lofi {

Keyboard:: Keyboard() {
  mSynth.allocatePolyphony<SineEnv>(16);
}

void Keyboard:: updateParameters(const CompositeData& c) {
  std::cout<<c.pos2<<std::endl;
  mFilterFreq = c.pos2 * 15000; // max freq
  mVolume = c.pos1;
  float curr = c.pos1;
  if(curr <= 0.33) {
    mGlobalWaveform = WAVEFORM::SINE;
  } else if (curr <= 0.66) {
    mGlobalWaveform = WAVEFORM::SQUARE;
  } else {
    mGlobalWaveform = WAVEFORM::SAW;
  }
}

void Keyboard:: onProcess(al::AudioIOData &io) {
  mSynth.render(io);
  while (io()) {
    io.out(0) *= mVolume; 
    io.out(1) *= mVolume; 
  }
}
void Keyboard:: onProcess(al::Graphics& g) {
  mSynth.render(g);
    // mSineEnv.onProcess(g);
}
void Keyboard:: onTriggerOn(const al::Keyboard &k) {
  int midiNote = al::asciiToMIDI(k.key());
  if (midiNote > 0) {
    float frequency = ::pow(2., (midiNote - 69.) / 12.) * 440.;
    SineEnv* voice = mSynth.getVoice<SineEnv>();
    std::cout<<frequency<<std::endl;
    voice->freq(frequency); 
    voice->updateFilter(mFilterFreq);
    voice->mCurrentWaveform = mGlobalWaveform; 
    mSynth.triggerOn(voice, 0, midiNote);
  }
}
void Keyboard:: onTriggerOff(const al::Keyboard &k) {
  int midiNote = al::asciiToMIDI(k.key());
  if (midiNote > 0) {
    mSynth.triggerOff(midiNote);
  }
}

} // namespace lofi
