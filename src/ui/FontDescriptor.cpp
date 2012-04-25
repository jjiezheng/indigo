#include "FontDescriptor.h"

#include "ResourceCache.h"

#include "String.h"
#include <sstream>
#include <string>

FontDescriptor* FontDescriptor::descriptor(const char* fontFile) {
  FontDescriptor* descriptor = new FontDescriptor();
  descriptor->init(fontFile);
  return descriptor;
}

void FontDescriptor::init(const char* fontFile) {
  const char* data = ResourceCache::instance()->loadFile(fontFile);
  std::stringstream dataStream;
  dataStream << data;
  std::string line;
  while(std::getline(dataStream, line)) {
    String line_type = String(line).first_word().c_str();
    
    if (line_type == "common") {
      std::vector<String> parameters = String(line).split(' ');
      for (String parameter : parameters) {
        std::vector<String> tokens = parameter.split('=');
        
        if (tokens.front() == "scaleW") {
          width_ = atoi(tokens.back().c_str());

        }
        
        if (tokens.front() == "scaleH") {
          height_ = atoi(tokens.back().c_str());
        }
      }
    }
    
    if (line_type == "page") {
      std::vector<String> parameters = String(line).split(' ');
      for (String parameter : parameters) {
        std::vector<String> tokens = parameter.split('=');
        
        if (tokens.front() == "file") {
          asset_ = tokens.back().replace("\"", "").c_str();
        }
      }
    }
    
    if (line_type == "char") {
      std::vector<String> parameters = String(line).split(' ');
      
      FontCharacterInfo char_info;
      char_info.sheet_height = height_;
      char_info.sheet_width = width_;
      for (String parameter : parameters) {
        std::vector<String> tokens = parameter.split('=');
        
        if (tokens.front() == "width") {
          char_info.width = atoi(tokens.back().c_str());
        }
        
        if (tokens.front() == "height") {
          char_info.height = atoi(tokens.back().c_str());
        }
        
        if (tokens.front() == "x") {
          char_info.x = atoi(tokens.back().c_str());
        }
        
        if (tokens.front() == "y") {
          char_info.y = atoi(tokens.back().c_str());
        }
        
        if (tokens.front() == "id") {
          char_info.char_id = atoi(tokens.back().c_str());
        }
        
        if (tokens.front() == "xoffset") {
          char_info.offset_x = atoi(tokens.back().c_str());
        }
        
        if (tokens.front() == "yoffset") {
          char_info.offset_y = atoi(tokens.back().c_str());
        }
      }
      
      addCharInfo(char_info);
    }
  }
}

void FontDescriptor::addCharInfo(const FontCharacterInfo& char_info) {
  char_info_.insert(std::make_pair(char_info.char_id, char_info));
}

FontCharacterInfo FontDescriptor::charInfo(char character) {
  std::map<char, FontCharacterInfo>::iterator info = char_info_.find(character);
  if (info != char_info_.end()) {
    return (*info).second;
  }
  return FontCharacterInfo();
}
