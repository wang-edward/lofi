#include "al/scene/al_SynthVoice.hpp"
#include "Gamma/Analysis.h"
#include "Gamma/Effects.h"
#include "Gamma/Envelope.h"
#include "Gamma/Oscillator.h"

#include "al/app/al_App.hpp"
#include "al/graphics/al_Shapes.hpp"
#include "al/scene/al_PolySynth.hpp"
#include "al/scene/al_SynthSequencer.hpp"
#include "al/ui/al_ControlGUI.hpp"
#include "al/ui/al_Parameter.hpp"

#include "al/graphics/al_Shapes.hpp"
#include "al/graphics/al_Font.hpp"

namespace lofi {
enum WAVEFORM {SQUARE, SAW, SINE};

class SineEnv : public al::SynthVoice {
 public:

  SineEnv();

    void update(double dt) {
        // updateFilter();
    }
  SineEnv& freq(float v);
  void updateFilter(float v);

  void onProcess(al::AudioIOData& io) override;

  void onProcess(al::Graphics& g) override;

  void onTriggerOn() override;

  void onTriggerOff() override;

 // protected:
  WAVEFORM mCurrentWaveform = WAVEFORM::SINE;
  float mAmp{0.2f};
  float mDur{1.5f};
  gam::Sine<> mOsc;
  gam::Square<> mOscSquare;
  gam::Saw<> mOscSaw;
  gam::Env<3> mAmpEnv{0.f, 0.2f, 1.f, 1.0f, 1.f, 0.5f, 0.f};
  gam::Biquad<> mBq;
  al::Mesh mMesh;

};
} // namespace lofi
