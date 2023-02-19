#pragma once

#include "al/graphics/al_Graphics.hpp"

#include "ui/UiElement.hpp"

namespace lofi {

class Slider : public UiElement {
public:
  Slider(al::Vec2f dimensions = {0, 0}, al::Vec2f pos = {0, 0}, al::Color color = al::RGB(1,1,1)) {
    addRect(rect, pos[0], pos[1], dimensions[0], dimensions[1]);
    rect.color(color);
    rect.color(color);
    rect.color(color);
    rect.color(color);
  }

  void onProcess(al::Graphics& g) override {
    g.meshColor();
    g.draw(rect);
  }

  void onTriggerOn(const al::Keyboard& k) override {}
  void onTriggerOff(const al::Keyboard& k) override {}

private:
  al::Mesh rect;
};

}
