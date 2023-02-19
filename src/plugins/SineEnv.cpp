#include "plugins/SineEnv.hpp"

SineEnv:: SineEnv() {
  mAmpEnv.curve(0);
  mAmpEnv.sustainPoint(2);
  addSphere(mMesh, 0.25, 30, 30);
}

SineEnv& SineEnv:: freq(float v) {
  mOsc.freq(v);
  return *this;
}

void SineEnv:: onProcess(al::AudioIOData& io) {
  while (io()) {
    float s = mOsc() * mAmpEnv() * mAmp;
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
