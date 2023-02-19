#include <cstdio>  // for printing to stdout
#include <iostream>

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

#include "plugins/Keyboard.hpp"
#include "ui/Slider.hpp"

class MyApp : public al::App {
 public:
 
  lofi::Keyboard bro;
  lofi::Slider man{{0,0}, {0.5,1}, {1, 0, 0}};


  al::Mesh bab;

  void onCreate() override {
    navControl().active(false);  // Disable navigation via keyboard, since we
                                 // will be using keyboard for note triggering
    gam::sampleRate(audioIO().framesPerSecond());

    // Cacluate the size of piano keys based on the app window size
    float w = float(width());
    float h = float(height());

  }

  // The audio callback function. Called when audio hardware requires data
  void onSound(al::AudioIOData& io) override {
    bro.onProcess(io);
  }

  // The graphics callback function.
  void onDraw(al::Graphics& g) override{
    g.camera(al::Viewpoint::UNIT_ORTHO_INCLUSIVE);
    g.meshColor();
    g.clear();
    man.onProcess(g);
    man.setPercentage(0.2);
  }

  // Whenever a key is pressed, this function is called
  bool onKeyDown(al::Keyboard const& k) override {
    bro.onTriggerOn(k);
    return true;
  }

  // Whenever a key is released this function is called
  bool onKeyUp(al::Keyboard const& k) override {
    bro.onTriggerOff(k);
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
}

