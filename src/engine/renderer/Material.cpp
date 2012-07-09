#include "Material.h"

#include "IEffect.h"
#include "IViewer.h"
#include "SceneContext.h"

#include "GraphicsInterface.h"
#include "maths/Matrix3x3.h"

#include "io/Log.h"

void Material::bind(const Matrix4x4& projection, const Matrix4x4& view, const Matrix4x4& model, const Matrix3x3& normalMatrix, const SceneContext& sceneContext, IEffect* effect) const {  


  /*effect->setUniform(model, "World");
  
  Matrix4x4 worldView = view * model;
  effect->setUniform(worldView, "WorldView");
  
  Matrix4x4 worldViewProjection = projection * worldView;
  effect->setUniform(worldViewProjection, "WorldViewProj");

  Matrix4x4 viewProjection = projection * view;
  effect->setUniform(viewProjection, "ViewProj");

  Matrix4x4 normMatrix = view.inverse();
  effect->setUniform(normMatrix.mat3x3(), "NormalMatrix");*/
 
  std::map<std::string, Texture>::const_iterator tit = textures_.begin(); 
  for (; tit != textures_.end(); ++tit) {
    effect->setTexture((*tit).second.textureId(), (*tit).first.c_str()); 
  }

  std::vector<MaterialParameter*>::const_iterator mit = parameters_.begin(); 
  for (; mit != parameters_.end(); ++mit) {
    
  }
}