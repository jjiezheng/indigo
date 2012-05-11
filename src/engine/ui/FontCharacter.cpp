#include "FontCharacter.h"

#include <iostream>

#include "renderer/OpenGL.h"
#include "renderer/Shader.h"
#include "renderer/ShaderAttribs.h"

#include "FontDescriptor.h"

FontCharacter* FontCharacter::character(FontCharacterInfo* characterInfo) {
  FontCharacter* character = new FontCharacter();
  character->init(characterInfo);
  return character;
}

void FontCharacter::init(FontCharacterInfo* characterInfo) {
  float width = (float)characterInfo->width;
  float height = (float)characterInfo->height;
  
  glGenVertexArrays(1, &vertexArray_);
  glBindVertexArray(vertexArray_);
  
  {
    float vertices[] = { 
      0,      height, 0.0f,
      0,      0,      0.0f,
      width,  height, 0.0f,
      
      width,  height, 0.0f,
      0,      0.0f,   0.0f,
      width,  0.0f,   0.0f };
    
    boundingBox_.width = width;
    boundingBox_.height = height;
    boundingBox_.x = 0;
    boundingBox_.y = 0;
    
    glGenBuffers(1, &vertexBuffer_);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_);
    glBufferData(GL_ARRAY_BUFFER, 6 * 3 * sizeof(float), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT, 0, 0, 0);
    glEnableVertexAttribArray(ATTRIB_VERTEX);
  }
  
  {
    float texel_left = (characterInfo->x - 1) / (float)characterInfo->sheet_width;
    float texel_right = texel_left + (characterInfo->width / (float)characterInfo->sheet_width);
    
    float texel_top = 1 - (characterInfo->y / (float)characterInfo->sheet_height);
    float texel_bottom = texel_top - (characterInfo->height / (float)characterInfo->sheet_height);
    
    float uvs[] = { 
      texel_left, texel_top,
      texel_left, texel_bottom, 
      texel_right, texel_top,
      
      texel_right, texel_top,
      texel_left, texel_bottom,
      texel_right, texel_bottom,
    };
    
    glGenBuffers(1, &uvBuffer_);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer_);
    glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), uvs, GL_STATIC_DRAW);
    glVertexAttribPointer(ATTRIB_UV, 2, GL_FLOAT, 0, 0, 0);
    glEnableVertexAttribArray(ATTRIB_UV);
  }
  
  glBindVertexArray(0);
}

void FontCharacter::render(Shader *shader) const {
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  
  glm::mat4 finalTransform = glm::translate(glm::mat4(1), glm::vec3(position_.x, position_.y, position_.z));
  shader->set_uniform(finalTransform, "model");
  
  glBindVertexArray(vertexArray_);  
  glDrawArrays(GL_TRIANGLES, 0, 6);
  
  glDisable(GL_BLEND);
  glDisable(GL_TEXTURE_2D);
}

Rect FontCharacter::boundingBox() const {
  return Rect(position_.x, position_.y, boundingBox_.width, boundingBox_.height);
}
