#include "GNMEffect.h"

#include <fstream>
#include <algorithm>

#include "io/Log.h"
#include "io/Path.h"
#include "io/File.h"

#include "renderer/IGraphicsInterface.h"
#include "renderer/GraphicsInterface.h"
#include "renderer/Color3.h"

#include "GNMGraphicsInterface.h"

#define BASED_ALIGN	128	

void GNMEffect::load(const std::string& filePath) {

}

void GNMEffect::beginDraw() {
 
}

void GNMEffect::commitBuffers() {
 
}

void GNMEffect::endDraw() {

}

void GNMEffect::setUniform(const Matrix3x3& uniformData, const char* uniformName) const {
  
}

void GNMEffect::setUniform(const Matrix4x4& uniformData, const char* uniformName) const {
 
}

void GNMEffect::setUniform(const Color3& uniformData, const char* uniformName) const {
 
}

void GNMEffect::setUniform(const Vector2& uniformData, const char* uniformName) const {

}

void GNMEffect::setUniform(const Vector3& uniformData, const char* uniformName) const {
  
}

void GNMEffect::setUniform(const Vector4& uniformData, const char* uniformName) const {
 
}

void GNMEffect::setUniform(const Vector4* uniformData, unsigned int uniformDataSize, const char* uniformName) const {
 
}

void GNMEffect::setUniform(int uniformData, const char* uniformName) const {
 
}

void GNMEffect::setUniform(float uniformData, const char* uniformName) const {
  
}

void GNMEffect::setTexture(unsigned int textureId, const char* uniformName) {
 
}

void GNMEffect::setSamplerState(unsigned int samplerSlot, SAMPLER_UV_ADDRESS_MODE addressMode, SAMPLER_COMPARISON_FILTER comparisonFilter, SAMPLER_COMPARISON_FUNC compartisonFunction) {

}

