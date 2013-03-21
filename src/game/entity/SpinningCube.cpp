#include "SpinningCube.h"

#include "maths/Vector4.h"
#include "renderer/Model.h"

#include <math.h>

void SpinningCube::update(float dt) {
  time_ += dt;
//  float y = cosf(time_) * 0.01f;
//  Matrix4x4 localToWorld = model_->localToWorld();
//  localToWorld = localToWorld * Matrix4x4::rotation(Vector4::UP, 1.0f * dt);
//  localToWorld = localToWorld * Matrix4x4::translation(Vector3(0, y, 0));
//  model_->setLocalToWorld(localToWorld);
}