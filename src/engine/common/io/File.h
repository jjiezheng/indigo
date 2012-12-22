#ifndef FILE_H
#define FILE_H

#include <string>

class File {

public:

  File() 
    : hasData_(false) { }
  
public:

  void open(const std::string fullFilePath);

  char* data() const;

  unsigned int size() const;

private:

  char* data_;
  unsigned int size_;
  bool hasData_;
  
};

inline char* File::data() const {
  return data_;
}

inline unsigned int File::size() const {
  return size_;
}

#endif
