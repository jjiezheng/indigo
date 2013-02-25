#include "Material.h"

#include "IEffect.h"
#include "IViewer.h"
#include "SceneContext.h"

#include "GraphicsInterface.h"
#include "maths/Matrix3x3.h"

#include "io/Log.h"

#include "Vector3MaterialParameter.h"
#include "Vector4MaterialParameter.h"
#include "IntegerMaterialParameter.h"
#include "FloatMaterialParameter.h"

void Material::bind(const Matrix4x4& projection, const Matrix4x4& view, const Matrix4x4& model, IEffect* effect) {  

	if (NULL != callback_) {
		(callback_)(this, effect, callbackUserData_);
	}

	effect->setUniform(model, "World");

	Matrix4x4 worldView = view * model;
	effect->setUniform(worldView, "WorldView");

	Matrix4x4 worldViewProjection = projection * worldView;
	effect->setUniform(worldViewProjection, "WorldViewProj");

	effect->setUniform(projection, "Projection");

	Matrix4x4 viewProjection = projection * view;
	effect->setUniform(viewProjection, "ViewProj");

	Matrix3x3 normalMatrix = worldView.inverse().transpose().mat3x3();
	effect->setUniform(normalMatrix, "NormalMatrix");

	std::map<std::string, Texture>::const_iterator tit = textures_.begin(); 
	for (; tit != textures_.end(); ++tit) {
		effect->setTexture((*tit).second.textureId(), (*tit).first.c_str()); 
	}

	std::map<std::string, MaterialParameter*>::const_iterator mit = parameters_.begin(); 
	for (; mit != parameters_.end(); ++mit) {
		(*mit).second->setEffect(effect);
	}
}

void Material::setParameter(const std::string& name, const Vector3& parameter) {
	std::map<std::string, MaterialParameter*>::const_iterator it = parameters_.find(name);

	if (it != parameters_.end()) {
		MaterialParameter* param = (*it).second;
		Vector3MaterialParameter* vector3Param = static_cast<Vector3MaterialParameter*>(param);
		vector3Param->setValue(parameter);
	}
	else
	{
		MaterialParameter* param = new Vector3MaterialParameter(name, parameter);
		parameters_[name] = param;
	}
}

void Material::setParameter(const std::string& name, const Vector4& parameter) {
	std::map<std::string, MaterialParameter*>::const_iterator it = parameters_.find(name);
  
	if (it != parameters_.end()) {
		MaterialParameter* param = (*it).second;
		Vector4MaterialParameter* vector4Param = static_cast<Vector4MaterialParameter*>(param);
		vector4Param->setValue(parameter);
	}
	else
	{
		MaterialParameter* param = new Vector4MaterialParameter(name, parameter);
		parameters_[name] = param;
	}
}


void Material::setParameter(const std::string& name, int parameter) {
	std::map<std::string, MaterialParameter*>::const_iterator it = parameters_.find(name);

	if (it != parameters_.end()) {
		MaterialParameter* param = (*it).second;
		IntegerMaterialParameter* intParam = static_cast<IntegerMaterialParameter*>(param);
		intParam->setValue(parameter);
	}
	else
	{
		MaterialParameter* param = new IntegerMaterialParameter(name, parameter);
		parameters_[name] = param;
	}
}

void Material::setParameter(const std::string& name, float parameter) {
	std::map<std::string, MaterialParameter*>::const_iterator it = parameters_.find(name);

	if (it != parameters_.end()) {
		MaterialParameter* param = (*it).second;
		FloatMaterialParameter* floatParam = static_cast<FloatMaterialParameter*>(param);
		floatParam->setValue(parameter);
	}
	else
	{
		MaterialParameter* param = new FloatMaterialParameter(name, parameter);
		parameters_[name] = param;
	}
}

void Material::setTexture(const std::string& type, unsigned int textureId) {
	Texture* texture = &textures_[type];
	texture->setTextureId(textureId);
}
