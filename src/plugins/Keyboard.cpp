#include "plugins/Keyboard.hpp"

namespace lofi {

Keyboard:: Keyboard() {

}

void Keyboard:: onProcess(al::AudioIOData &io) {
    synthManager.render(io);
}
void Keyboard:: onProcess(al::Graphics& g) {
    // mSineEnv.onProcess(g);
}
void Keyboard:: onTriggerOn(const al::Keyboard &k) {
    if (ParameterGUI::usingKeyboard()) {  // Ignore keys if GUI is using
                                          // keyboard
      return true;
    }
    if (k.shift()) {
      // If shift pressed then keyboard sets preset
      int presetNumber = asciiToIndex(k.key());
      synthManager.recallPreset(presetNumber);
    } else {
      // Otherwise trigger note for polyphonic synth
      int midiNote = asciiToMIDI(k.key());
      
      if (midiNote > 0) {
        // Check which key is pressed
        int keyIndex = asciiToKeyLabelIndex(k.key());
        
        bool isBlackKey = false;
        if(keyIndex >= 20) {
          keyIndex -= 20;
          isBlackKey = true;
        }

        synthManager.voice()->setInternalParameterValue(
            "frequency", ::pow(2.f, (midiNote - 69.f) / 12.f) * 432.f);

        float w = keyWidth;
        float h = keyHeight;
        float x = (keyWidth + keyPadding * 2) * (keyIndex % 10) + keyPadding;
        float y = 0;
        
        if(isBlackKey == true) {
          x += keyWidth * 0.5;
          y += keyHeight * 0.5;
          h *= 0.5;
        }
        
        if(keyIndex >= 10) {
          y += keyHeight + keyPadding * 2;
        }
        
        synthManager.voice()->setInternalParameterValue("pianoKeyWidth", w);
        synthManager.voice()->setInternalParameterValue("pianoKeyHeight", h);
        synthManager.voice()->setInternalParameterValue("pianoKeyX", x);
        synthManager.voice()->setInternalParameterValue("pianoKeyY", y);
        
        synthManager.triggerOn(midiNote);
      }
    }
    return true;

}
void Keyboard:: onTriggerOff(const al::Keyboard &k) {
    mSineEnv.onTriggerOff();
}

}