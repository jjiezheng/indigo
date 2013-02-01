#include "BinaryModelDeserializer.h"

#include "renderer/Model.h"

#include <fstream>
#include <iostream>

#include "renderer/Vector3MaterialParameter.h"
#include "renderer/Vector4MaterialParameter.h"
#include "renderer/FloatMaterialParameter.h"
#include "renderer/Texture.h"
#include "renderer/VertexDefinition.h"
#include "renderer/EffectCache.h"

#include "io/Path.h"
#include "io/Endian.h"

enum MaterialParameterType {
  PARAMETER_TYPE_UNKNOWN = 0,
  PARAMETER_TYPE_STRING = 1,
  PARAMETER_TYPE_FLOAT = 2,
  PARAMETER_TYPE_VECTOR3 = 3,
  PARAMETER_TYPE_VECTOR4 = 4,
};

std::string BinaryModelDeserializer::readString(std::ifstream& input) {
  unsigned int stringLength = 0;
  input.read((char*)&stringLength, sizeof(unsigned int));

  char* stringRaw = new char[stringLength];
  input.read((char*)stringRaw, sizeof(char) * stringLength);

  std::string result(stringRaw);

  delete stringRaw;

  return result;
}

unsigned int BinaryModelDeserializer::readUINT(std::ifstream& input) {
  unsigned int value = 0;
  input.read((char*)&value, sizeof(unsigned int));
  return value;
}

int BinaryModelDeserializer::readINT(std::ifstream& input) {
  int value = 0;
  input.read((char*)&value, sizeof(int));
  return value;
}

Vector3 BinaryModelDeserializer::readVector3(std::ifstream& input) {
  Vector3 value;
  input.read((char*)&value, sizeof(Vector3));
  return value;
}

Vector4 BinaryModelDeserializer::readVector4(std::ifstream& input) {
  Vector4 value;
  input.read((char*)&value, sizeof(Vector4));
  return value;
}

float BinaryModelDeserializer::readFloat(std::ifstream& input) {
  float value;
  input.read((char*)&value, sizeof(float));
  return value;
}

Model* BinaryModelDeserializer::deserialize(const std::string& modelFilePath) {
  Model* model = new Model();

  std::ifstream input;
  input.open(modelFilePath.c_str(), std::ifstream::in | std::ios::binary);
  input.seekg(0); 

#ifdef BIG_ENDIAN
  unsigned int bigEndianOffset;
  input.read((char*)&bigEndianOffset, sizeof(unsigned int));
  bigEndianOffset = binary_uint32(bigEndianOffset);
  input.seekg(0);
  input.seekg(bigEndianOffset);
#else
  input.seekg(sizeof(unsigned int));
#endif

  if (!input.is_open()) {
    LOG(LOG_CHANNEL_IO, "Failed to open %s", modelFilePath.c_str());
    return model; 
  }

  unsigned int subMeshCount = readUINT(input);

  for (unsigned int i = 0; i < subMeshCount; i++) {
    Material material;
    deserializeMaterial(material, input);

    unsigned int vertexCount = readUINT(input);
    VertexDef* vertexData = new VertexDef[vertexCount];
    input.read((char*)vertexData, sizeof(VertexDef) * vertexCount);

    Mesh mesh;
    mesh.init(vertexData, vertexCount, TRIANGLE_LIST);
    mesh.setMaterial(material);
    model->addMesh(mesh);
  }

  return model;
}

void BinaryModelDeserializer::deserializeMaterial(Material& material, std::ifstream& input) {

	std::string materialName = readString(input);
	material.setName(materialName);

  std::string effectFile = readString(input);

  IEffect* effect = EffectCache::instance()->loadEffect(effectFile);
  material.setEffect(effect);

  unsigned int parameterCount = readUINT(input);

  for (unsigned int i = 0; i < parameterCount; i++) {
    std::string parameterKey = readString(input);
   
    MaterialParameterType parameterType = (MaterialParameterType)readINT(input);

    if (parameterType == PARAMETER_TYPE_FLOAT) {
      float parameterValue = readFloat(input);
      material.setParameter(parameterKey, parameterValue);
    }

    if (parameterType == PARAMETER_TYPE_VECTOR3) {
      Vector3 parameterValue = readVector3(input);
      material.setParameter(parameterKey, parameterValue);
    }
    
    if (parameterType == PARAMETER_TYPE_VECTOR4) {
      Vector4 parameterValue = readVector4(input);
      material.setParameter(parameterKey, parameterValue);
    }
  }

  unsigned int textureCount = readUINT(input);

  for (unsigned int i = 0; i < textureCount; i++) {
    std::string textureKey = readString(input);
    std::string texturePath = readString(input);
    
    Texture texture;
    texture.init(texturePath);
    material.addTexture(textureKey, texture);
  }
}
