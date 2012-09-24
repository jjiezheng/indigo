#ifndef BINARYMODELDESERIALIZER_H_
#define BINARYMODELDESERIALIZER_H_

#include <string>
#include <fstream>

#include "maths/Vector3.h"

class Model;
class Material;

class BinaryModelDeserializer {

public:

  static Model* deserialize(const std::string& modelFilePath);

private:

  static void deserializeMaterial(Material& material, std::ifstream& input);
  
private:
  
  static unsigned int swap_uint32(unsigned int val);
  
  static std::string readString(std::ifstream& input);
  
  static unsigned int readUINT(std::ifstream& input);
  
  static int readINT(std::ifstream& input);
  
  static Vector3 readVector3(std::ifstream& input);
  
  static float readFloat(std::ifstream& input);

};

#endif