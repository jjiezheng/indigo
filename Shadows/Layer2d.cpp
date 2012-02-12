#include "Layer2d.h"

#include "Shader.h"
#include "ShaderCache.h"
#include "MacPlatform.h"

void Layer2d::init() {
  shader_ = ShaderCache::instance()->addShader("vmpt.vsh", "ft.fsh");
}

void Layer2d::render(Camera *camera, Shader *shader, const Matrix4x4& transform) const {
  shader_->use();
  
  Vector2 screenSize = MacPlatform::instance()->screen_size();
  glm::mat4 ortho = glm::ortho(0.0f, screenSize.x, 0.0f, screenSize.y, 0.0f, 1.0f);
  shader_->set_uniform(ortho, "projection");
  
  for (SceneNode* child : children_) {
    child->render(camera, shader_, transform);
  }
}