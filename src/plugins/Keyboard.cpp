#include "plugins/Keyboard.hpp"

namespace lofi {

Keyboard:: Keyboard() {
  mSynth.allocatePolyphony<SineEnv>(16);
}

void Keyboard:: updateParameters(const CompositeData& c) {
  mFilterFreq = c.pos0 * 10000; // max freq
}

void Keyboard:: onProcess(al::AudioIOData &io) {
  mSynth.render(io);
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
