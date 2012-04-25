#include "Light.h"

#include "Renderer.h"

Light::Light(const Vector3& color) 
  : color_(color)
  , castsShadows_(false) {
  
}

void Light::queueRender(Renderer* renderer) {
  renderer->queueLight(this);
  if (castsShadows_) {
    renderer->queueShadowLight(this);
  }
}
