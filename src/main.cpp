#include <cstdio>  // for printing to stdout
#include <iostream>
#include <thread>

#include "Gamma/Analysis.h"
#include "Gamma/Effects.h"
#include "Gamma/Envelope.h"
#include "Gamma/Oscillator.h"

#include "al/app/al_App.hpp"
#include "al/graphics/al_Shapes.hpp"
#include "al/scene/al_PolySynth.hpp"
#include "al/scene/al_SynthSequencer.hpp"
#include "al/system/al_PeriodicThread.hpp"
#include "al/ui/al_ControlGUI.hpp"
#include "al/ui/al_Parameter.hpp"

#include "al/graphics/al_Shapes.hpp"
#include "al/graphics/al_Font.hpp"

#include "al/math/al_Random.hpp"

#include "plugins/Keyboard.hpp"
#include "serial/Serial.hpp"
#include "ui/Slider.hpp"

class MyApp : public al::App {
 public:
 
  enum CURRENT_PLUGIN {SAMPLER, SYNTH};
  lofi::Keyboard mKeyboard;
  lofi::Serial mSerial;
  lofi::CompositeData mData;

  al::Mesh bab;
  al::Mesh rbo;
  al::Mesh tri;
  lofi::Slider man{{0,0}, {0.5,1}, {1, 0, 0}};
  lofi::Slider gro{{0,0}, {1, 0.5}, {0.3, 0.3, 1}};
  CURRENT_PLUGIN mCurrentPlugin = SYNTH;
    
  void onCreate() override {
    navControl().active(false);  // Disable navigation via keyboard, since we
                                 // will be using keyboard for note triggering
    gam::sampleRate(audioIO().framesPerSecond());
    addDisc(bab, 0.3, 100);
    addCube(rbo, false, 0.1);
    tri.vertex(1,0);
    tri.vertex(1,-2);
    tri.vertex(2.19,-2.19);
    tri.scale(0.2,0.2);
    tri.color(al::RGB(0,2,0));
    tri.color(al::RGB(0,2,0));
    tri.color(al::RGB(1,0,1));
    bab.color(al::RGB(0,1,0));
    rbo.color(al::RGB(0,0,1));
    rbo.color(al::RGB(0,1,1));
    rbo.color(al::RGB(1,0,0));
    rbo.color(al::RGB(1,1,0));
  }

  // The audio callback function. Called when audio hardware requires data
  void onSound(al::AudioIOData& io) override {
    mKeyboard.onProcess(io);
  }

  int mTimer = 10;

  void onAnimate(double dt) override {
    if (mTimer > 2) {
      mSerial.read(mData);
      mKeyboard.updateParameters(mData);
      std::cout<<mData.pos2<<std::endl;
      mTimer = 0;
    } else {
      mTimer++;
    }
    // std::cout<<mTimer<<std::endl;
  }

  // The graphics callback function.
  void onDraw(al::Graphics& g) override{
    g.clear();
    g.camera(al::Viewpoint::UNIT_ORTHO_INCLUSIVE);
    g.meshColor();
    gro.onProcess(g);
    man.onProcess(g);
    g.draw(bab);
    g.draw(rbo);
    g.draw(tri);
    // mKeyboard.onProcess(g);
  }

  // Whenever a key is pressed, this function is called
  bool onKeyDown(al::Keyboard const& k) override {
    bab.colors().clear();
    bab.color(mData.pos0 * 5, 0, 0);

    tri.colors().clear();
    tri.color(0, mData.pos1 * 5, 0);
    tri.color(0, mData.pos1 * 5, 0);
    tri.color(0, mData.pos1 * 5, 0);
    rbo.colors().clear();
    rbo.color(mData.pos2 * 5, 0, 0);
    rbo.color(0, mData.pos2 * 5, 0);
    rbo.color(0, 0, mData.pos2 * 5);
    rbo.color(mData.pos2 * 5, mData.pos2 * 5, 0);
    mKeyboard.onTriggerOn(k);
    return true;
  }

  // Whenever a key is released this function is called
  bool onKeyUp(al::Keyboard const& k) override {
    switch(mCurrentPlugin) {
      case SYNTH:
        mKeyboard.onTriggerOff(k);
      case SAMPLER:
        int x;

    }
    return true;
  }
  
  // Whenever the window size changes this function is called
  void onResize(int w, int h) override {
    // Recaculate the size of piano keys based new window size
  }

  void onExit() override { }
};

int main() {
  // Create app instance
  MyApp app;
  
  // Set window size
  app.dimensions(1200, 600);
  
  // Set up audio
  app.configureAudio(48000., 512, 2, 0);
  printf("cnfigued");
  app.start();
  return 0;
};

