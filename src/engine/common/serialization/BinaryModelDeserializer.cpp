#include "BinaryModelDeserializer.h"

#include "renderer/Model.h"

#include <fstream>
#include <iostream>

#include "renderer/Vector3MaterialParameter.h"
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
  bigEndianOffset = swap_uint32(bigEndianOffset);
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
      //MaterialParameter* parameter = new FloatMaterialParameter(parameterKey, parameterValue);
      material.setParameter(parameterKey, parameterValue);
    }

    if (parameterType == PARAMETER_TYPE_VECTOR3) {
      Vector3 parameterValue = readVector3(input);
      //MaterialParameter* parameter = new Vector3MaterialParameter(parameterKey, parameterValue);
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