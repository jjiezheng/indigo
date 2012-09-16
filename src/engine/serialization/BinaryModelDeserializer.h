#ifndef BINARYMODELDESERIALIZER_H_
#define BINARYMODELDESERIALIZER_H_

#include <string>
#include <fstream>

class Model;
class Material;

class BinaryModelDeserializer {

public:

  static Model* deserialize(const std::string& modelFilePath);

private:

  static void deserializeMaterial(Material& material, std::ifstream& input);

};

#endif