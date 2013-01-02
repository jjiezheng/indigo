#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
#include <vector>
#include <map>

#include "MaterialParameter.h"
#include "Texture.h"

class IViewer;
class SceneContext;
class IEffect;
class Matrix4x4;
class Matrix3x3;
class Vector3;

class Material {

public:

	typedef void (*MaterialCallback)(Material* material, void* userData);

public:

  Material() 
    : callback_(NULL)
		, effect_(0) { }
  
public:
  
  void bind(const Matrix4x4& projection, const Matrix4x4& view, const Matrix4x4& model, IEffect* effect);
  
  void addTexture(const std::string& type, const Texture& texture);

	void setTexture(const std::string& type, unsigned int textureId);

  void setEffect(IEffect* effect);

  IEffect* effect() const;

public:

	void setParameter(const std::string& name, const Vector3& parameter);

	void setParameter(const std::string& name, int parameter);

	void setParameter(const std::string& name, float parameter);

public:

	std::string name() const;

	void setName(const std::string& name);

public:

	void setCallback(MaterialCallback callback, void* userData);
  
private:
  
  std::map<std::string, MaterialParameter*> parameters_;
  std::map<std::string, Texture> textures_;

	MaterialCallback callback_;
	void* callbackUserData_;
  
  IEffect* effect_;

	std::string name_;
};

inline IEffect* Material::effect() const {
  return effect_;
}

inline void Material::setEffect(IEffect* effect) {
  effect_ = effect;
}

inline void Material::addTexture(const std::string& type, const Texture& texture) {
  textures_.insert(std::make_pair(type, texture));
}

inline void Material::setName(const std::string& name) {
	name_ = name;
}

inline std::string Material::name() const {
	return name_;
}

inline void Material::setCallback(MaterialCallback callback, void* userData) {
	callback_ = callback;
	callbackUserData_ = userData;
}

#endif
