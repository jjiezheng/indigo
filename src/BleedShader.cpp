#include "BleedShader.h"

#include "ShaderCache.h"
#include "ShaderResource.h"
#include "ResourceCache.h"

#include "ShaderAttribs.h"

#include "Texture.h"

#include "Shader.h"

#include <iostream>

#include "Vector2.h"

BleedShader* BleedShader::shader() {
  BleedShader* shader = new BleedShader();
  shader->init();
  return shader;
}

void BleedShader::init() {
  ShaderResource* resource = ResourceCache::instance()->load_shader("vmvpt.vsh", "ft.fsh");
  
  this->compile_vertex(resource->vertex_source());
  this->compile_fragment(resource->fragment_source());
  
  this->bind_attribute(ATTRIB_VERTEX, "vertex");
  this->bind_attribute(ATTRIB_UV, "textureCoords");
  
  this->link();
  
  this->add_uniform("model");
  this->add_uniform("view");
  this->add_uniform("projection");
  
  this->add_uniform("colorMap");
  this->add_uniform("bleedColorMap");
}

void BleedShader::render() {  
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture_->textureId());
  this->set_uniform(0, "colorMap");

  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, bleedTexture_);
  this->set_uniform(1, "bleedColorMap");
}

int ccDrawCircle(const Vector2& center, float r, float a, int segs, bool drawLineToCenter);
int ccDrawCircle(const Vector2& center, float r, float a, int segs, bool drawLineToCenter)
{
	int additionalSegment = 1;

	const float coef = 2.0f * (float) (M_PI) / segs;
  
	float *vertices = new float[2*(segs+2)]; //	float *vertices = (float *)malloc( sizeof(float)*2*(segs+2));
	if(!vertices) {
		return 0 ;
	}
	
  int numVertices = sizeof(float)*2*(segs+2);
	memset(vertices,0, numVertices);	
	for(int i=0;i<=segs;i++)
	{
		float rads = i*coef;
		float j = r * cosf(rads + a) + center.x;
		float k = r * sinf(rads + a) + center.y;
		
		vertices[i*2] = j;
		vertices[i*2+1] =k;
	}
	
  glBufferData(GL_ARRAY_BUFFER, numVertices, vertices, GL_STATIC_DRAW);

	delete[] vertices; //	free(vertices);
  
  return segs+additionalSegment;
}

void BleedShader::setTexture(Texture* texture) {
  texture_ = texture;
  
  { // create the render texture
    glGenTextures(1, &bleedTexture_);
    glBindTexture(GL_TEXTURE_2D, bleedTexture_);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture_->width(), texture_->height(), 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);    
  }
  
  GLuint frameBuffer = 0;
  glGenFramebuffers(1, &frameBuffer);
  glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
  glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, bleedTexture_, 0);

  if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    std::clog << "Failed to create bleed render buffer" << std::endl;
  }
  
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  
  { // render to the texture
    ShaderResource* resource = ResourceCache::instance()->load_shader("v.vsh", "f.fsh");
    Shader* shader = Shader::shader(resource);
    shader->bind_attribute(ATTRIB_VERTEX, "vertex");
    shader->link();  
    shader->use();

    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glViewport(0, 0, texture_->width(), texture_->height());

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    float alphaVerts[] = {
      -0.5, -0.5, 0,
       0.5f,  0.5, 0,
      -0.5,  0.5, 0,
      
      -0.5, -0.5, 0,
       0.5f, -0.5, 0, 
       0.5f,  0.5, 0
    };
    
    GLuint alphaVertexArray = 0;
    glGenVertexArrays(1, &alphaVertexArray);
    glBindVertexArray(alphaVertexArray);
        
    GLuint alphaVertexBuffer = 0;
    
    glGenBuffers(1, &alphaVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, alphaVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float) * 6, alphaVerts, GL_STATIC_DRAW);
//    int count = ccDrawCircle(Vector2(0, 0), 0.5, 0, 10, false);
    glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT, 0, 0, 0);
    glEnableVertexAttribArray(ATTRIB_VERTEX);
    
    glBindVertexArray(alphaVertexArray);
    glDrawArrays(GL_TRIANGLES, 0, 6);
//    glDrawArrays(GL_TRIANGLE_FAN, 0, count);
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }
}

