#ifndef STRING_H
#define STRING_H

#include "Standard.h"

class String {
  
  typedef typename std::string::const_iterator ConstIterator;
  typedef typename std::string::iterator Iterator;
  
public:
  
  String();
  
  String(const std::string& string);
  
  String(const char* string);
  
public:
  
  static 
  String withFormat(const char* format, ...);
  
public:
  
  String first_word();
  
  std::vector<String> lines() const;
  
  std::vector<String> split(char delimeter) const;
  
  size_t length() const;
  
  String lastPathComponent() const;
  
public:
  
  ConstIterator begin() const {
    return string_.begin();
  }
  
  ConstIterator end() const {
    return string_.end();
  }
  
public:
  
  const char* c_str() const;
  
  std::string str() const;
  
public:
  
  bool startsWith(const String& string) const;
  
  String replace(const String& source, const String& destination) const;
  
  unsigned long hash() const;
  
  bool contains(const String& token) const;
  
  String concat(const String& other) const;
  
  unsigned char charAt(int index) const;
  
public:
  
  float toFloat() const;
  
public:
  
  bool operator == (const String& other) const;
  bool operator != (const String& other) const;
  bool operator < (const String& other) const;
  
private:
  
  std::string string_;
  
  
};

#endif
