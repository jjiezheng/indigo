#include "FPSLabel.h"

#include "Label.h"
#include <sstream>
#include <iostream>

static const int MAX_FPS_SAMPLES = 10;
static const int TAG_FPS = 100;
static const float TIME_TO_SKIP_SECS = 0.5f;

FPSLabel::FPSLabel() 
  : timeSkipAccum_(0.0f) {
  
}

FPSLabel* FPSLabel::label() {
  FPSLabel* layer = new FPSLabel();
  layer->init();
  return layer;
}

void FPSLabel::init() {
  Label* label = Label::label("0 FPS", "copperplate_18.fnt");
  addChild(label, TAG_FPS);
  
  scheduleUpdate();
}

void FPSLabel::update(float dt) {
  fpss_.push_back(dt);
  
  if (fpss_.size() >= MAX_FPS_SAMPLES) {
    fpss_.pop_front();
  }
  
  // only report at the TIME_TO_SKIP_SECS interval
  timeSkipAccum_ += dt;
  if (timeSkipAccum_ >= TIME_TO_SKIP_SECS) {
    timeSkipAccum_ = 0.0f;
    float totalfps = 0.0f;
    for (float fps : fpss_) {
      totalfps += fps;
    }
    totalfps /= fpss_.size();
    
    float avgFps = 1.0f/totalfps;
    
    std::stringstream fps;
    fps << (int)avgFps << " FPS" << std::endl;
    
    SceneNode* labelNode = getChildByTag(TAG_FPS);
    Label* label = static_cast<Label*>(labelNode);
    label->setText(fps.str().c_str());
  }
}

