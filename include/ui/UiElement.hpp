#pragma once

#include "al/io/al_Window.hpp"
#include "al/graphics/al_Graphics.hpp"

namespace lofi {

class UiElement {

public:
  virtual void onProcess(al::Graphics& g) = 0;
  virtual void onTriggerOn(const al::Keyboard &k) = 0;
  virtual void onTriggerOff(const al::Keyboard &k) = 0;
};

} // namespace lofi 
