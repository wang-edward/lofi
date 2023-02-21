#include "plugins/SineEnv.hpp"

namespace lofi {

SineEnv:: SineEnv() {
  mAmpEnv.curve(0);
  mAmpEnv.sustainPoint(2);
  addSphere(mMesh, 0.25, 30, 30);
  mBq.type(gam::LOW_PASS);
  mBq.res(1);
}

SineEnv& SineEnv:: freq(float v) {
  mOsc.freq(v);
  mOscSquare.freq(v);
  mOscSaw.freq(v);
  return *this;
}

void SineEnv:: updateFilter(float v) {
    mBq.freq(v);
}

void SineEnv:: onProcess(al::AudioIOData& io) {
  while (io()) {
    float osc = 0; 
    if (mCurrentWaveform == WAVEFORM::SINE) {
        osc = mOsc();
    } else if (mCurrentWaveform == WAVEFORM::SQUARE) {
        osc = mOscSquare(); 
    } else if (mCurrentWaveform == WAVEFORM::SAW) {
        osc = mOscSaw();
    }
    
    float s = osc * mAmpEnv() * mAmp;
    s = mBq(s);
    io.out(0) += s;
    io.out(1) += s;
  }
  if (mAmpEnv.done()) {
    free();
  }
}

void SineEnv:: onProcess(al::Graphics& g) {
  float spatialEnv = mAmpEnv.value();
  g.pushMatrix();
  g.blending(true);
  g.blendTrans();
  g.translate(mOsc.freq() / 500 - 1.25, spatialEnv - 0.5, 0);
  g.color(spatialEnv, mOsc.freq() / 1000, spatialEnv, spatialEnv);
  g.draw(mMesh);
  g.popMatrix();
}

void SineEnv:: onTriggerOn() { 
  mAmpEnv.reset(); 
}

void SineEnv:: onTriggerOff() { 
  mAmpEnv.release(); 
}

} // namespace lofi
