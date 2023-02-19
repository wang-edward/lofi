#pragma once

#include "al/graphics/al_Graphics.hpp"

#include "ui/UiElement.hpp"

#include <iostream> // TODO REMOVE

namespace lofi {

class Slider : public UiElement {
public:
  Slider(al::Vec2f dimensions = {0, 0}, al::Vec2f pos = {0, 0}, al::Color color = al::RGB(1,1,1), float percentage = 1.f) {
    this->mDimensions = dimensions;
    this->mPos = pos;
    this->mColor = color;
    addRect(mOuter, pos.x, pos.y, dimensions.x, dimensions.y);
    addRect(mInner, pos.x, pos.y, dimensions.x * 0.9, dimensions.y * 0.9);
    for (auto v : mOuter.vertices()) {
      mOuter.color(mBackground);
    }
    for (auto v : mInner.vertices()) {
      mInner.color(mColor);
    }
  }

  void onProcess(al::Graphics& g) override {
    g.meshColor();
    g.draw(mOuter);
    g.draw(mInner); // remember to draw inner after outer
  }

  void onTriggerOn(const al::Keyboard& k) override {}
  void onTriggerOff(const al::Keyboard& k) override {}


  void setPercentage(float newPercentage) {
    mPercentage = newPercentage;
    std::cout<<mInner.vertices().size()<<std::endl;
    al::Vec2f total = {dimensions.x, dimensions.y * mPercentage};
    
    // do (mOuter * 0.9) * 
    

  }
private:
  const al::Color mBackground = al::RGB(1, 1, 1);

  al::Mesh mOuter;
  al::Mesh mInner;
  al::Vec2f mDimensions;
  al::Vec2f mPos;
  al::Color mColor;

  float mPercentage = 0;
};

}
