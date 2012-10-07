#include "Material.h"

#include "IEffect.h"
#include "IViewer.h"
#include "SceneContext.h"

#include "GraphicsInterface.h"
#include "maths/Matrix3x3.h"

#include "io/Log.h"

void Material::bind(const Matrix4x4& projection, const Matrix4x4& view, const Matrix4x4& model, IEffect* effect) const {  
  effect->setUniform(model, "World");
  
  Matrix4x4 worldView = view * model;
  effect->setUniform(worldView, "WorldView");
  
  Matrix4x4 worldViewProjection = projection * worldView;
  effect->setUniform(worldViewProjection, "WorldViewProj");

  effect->setUniform(projection, "Projection");

  Matrix4x4 viewProjection = projection * view;
  effect->setUniform(viewProjection, "ViewProj");

  //worldView.inverse().transpose().mat3x3()
  effect->setUniform(Matrix4x4::IDENTITY.mat3x3(), "NormalMatrix");
 
  std::map<std::string, Texture>::const_iterator tit = textures_.begin(); 
  for (; tit != textures_.end(); ++tit) {
    effect->setTexture((*tit).second.textureId(), (*tit).first.c_str()); 
  }

  std::vector<MaterialParameter*>::const_iterator mit = parameters_.begin(); 
  for (; mit != parameters_.end(); ++mit) {
    (*mit)->setEffect(effect);
  }
}