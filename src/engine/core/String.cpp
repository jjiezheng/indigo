#include "String.h"

#include <iostream>

#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include <stdlib.h>

#include "platform/PlatformDefs.h"

String String::withFormat(const char* format, ...) {

#ifdef PLATFORM_WINDOWS
  va_list args;
  va_start(args, format);

  int length = _vscprintf( format, args ) + 1; // _vscprintf doesn't count terminating '\0'

  char* buffer = (char*)malloc(length * sizeof(char));

  vsprintf_s(buffer, length, format, args);

  va_end(args);
  return String(buffer);
#endif

#ifdef PLATFORM_POSIX
  va_list args;
  va_start(args, format);

  int length = 255;

  char* buffer = (char*)malloc(length * sizeof(char));

  vsprintf(buffer, format, args);

  va_end(args);
  return String(buffer);
#endif
}

String String::pathExtension() const {
  std::string key(".");
  size_t found = 0;
  
  found = string_.rfind(key);
  if (found != std::string::npos) {
    return string_.substr(found, string_.length() - found);
  }
  
  return "";
}

String String::removePathExtension() const {
  String extension = pathExtension();
  return replace(extension, "");
}

String String::lastPathComponent() const {
  String posixPath = this->replace("\\", "/");
  std::vector<String> components = posixPath.split('/');
  if (!components.empty()) {
    return components[components.size() - 1];
  }
  return "";
}

String String::pathComponent() const {
  return this->replace(this->lastPathComponent(), "");
}

String String::addPathComponent(const String& pathComponent) {
  char pathSeperator = '/';
#ifdef _WIN32
  pathSeperator = '\\';
#endif
  std::stringstream pathStream;
  pathStream << string_;
  int intSize = (int)size();
  char finalCharacter = charAt(intSize - 1);
  if (finalCharacter != pathSeperator) {
    pathStream << pathSeperator;
  }
  pathStream << pathComponent.c_str();
  return pathStream.str();
}

size_t String::size() const {
  return string_.size();
}

std::vector<String> String::split(char delimeter) const {
  using namespace std;
  std::vector<String> lines;
  std::stringstream stringStream(string_);  
  string item;
  while (getline(stringStream, item, delimeter)) {
    lines.push_back(item);
  }
  return lines;  
}

std::vector<std::string> String::split(const std::string& sourceString, const std::string& delimeter) {
  std::vector<std::string> output;

  std::string::size_type prev_pos = 0, pos = 0;

  while((pos = sourceString.find(delimeter, pos)) != std::string::npos)
  {
    std::string substring(sourceString.substr(prev_pos, pos-prev_pos));

    output.push_back(substring);

    prev_pos = ++pos;
  }

  output.push_back(sourceString.substr(prev_pos, pos-prev_pos)); // Last word

  return output;
}


std::vector<String> String::lines() const {
  return split('\n');
}

const char* String::c_str() const {
  return string_.c_str();
}

size_t String::length() const {
  return string_.length();
}

std::string String::str() const {
  return string_;
}

bool String::startsWith(const String& string) const {
  if (string_.length() > 0) {
    return string_.substr(0, 1).compare(string.str()) == 0;
  }
  return false;
}

String String::replace(const String& source, const String& destination) const {
  std::string result = string_;
  std::string::size_type next;
  
  for (next = result.find(source.str()); next != std::string::npos; next = result.find(source.str(), next)) {
    result.replace(next, source.length(), destination.str());
    next += destination.length();
  }
  
  return result;
}

std::string String::replace(const std::string& original, const std::string& source, const std::string& destination) {
  std::string result = original;
  std::string::size_type next;

  for (next = result.find(source); next != std::string::npos; next = result.find(source, next)) {
    result.replace(next, source.length(), destination);
		next += destination.length() ? destination.length() : 1;
  }

  return result;
}

String String::operator + (const String& other) const {
  return string_ + other.string_;
}

bool String::operator == (const String& other) const {
  return string_.compare(other.string_) == 0;
}

bool String::operator != (const String& other) const {
  return !(*this == other);
}

bool String::operator < (const String& other) const {
  return string_ < other.string_;
}

unsigned long String::hash() const {
  unsigned long hash = 5381;
  int c;
  
  const char* str = c_str();
  
  while ((c = *str++))
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  
  return hash;
}

bool String::contains(const String& token) const {
  return string_.find(token.str()) != std::string::npos;
}

float String::toFloat() const {
  return 0.0f;
  //return (float)atof(string_.c_str());
}

String String::concat(const String& other) const {
  return String::withFormat("%s%s", c_str(), other.c_str());
}

unsigned char String::charAt(int index) const {
  return string_[index];
}

String String::first_word() {
  return string_.substr(0, string_.find(' '));
}
