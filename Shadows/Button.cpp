#include "Button.h"

//#include "Standard.h"
//
//#include "Shader.h"
//#include "ShaderAttribs.h"
//
//void Button::render(const Shader& shader) {
//  MAT4 model = glm::translate(MAT4(1.0f), position_);
//  
//  //  texture->render(*shader);
//  
//  shader.set_uniform(model, "model");
//  
//  float width = 20;
//  float height = 10;
//  
//  float vertices[] = { 0.0f,  height, 0.0f,
//    0.0f,  0, 0.0f, 
//    width,  height, 0.0f,
//    
//    width, height, 0.0f,
//    0.0f, 0.0f, 0.0f,
//    width, 0.0f, 0.0f };
//  
//  glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT, 0, 0, vertices);
//  glEnableVertexAttribArray(ATTRIB_VERTEX);
//  
//  //  float uvs[] = { 0.0f, 1.0f,
//  //                  0.0f, 0.0f, 
//  //                  1.0f, 1.0f,
//  //                  
//  //                  1.0f, 1.0f,
//  //                  0.0f, 0.0f,
//  //                  0.0f, 1.0f };
//  //    
//  //  glVertexAttribPointer(ATTRIB_UV, 2, GL_FLOAT, 0, 0, uvs);
//  //  glEnableVertexAttribArray(ATTRIB_UV);
//  
//  glDrawArrays(GL_TRIANGLES, 0, 6);      
//}
