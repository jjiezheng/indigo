#include "Geometry.h"

#include "GraphicsInterface.h"
#include "VertexDefinition.h"
#include "VertexFormat.h"

int Geometry::SCREEN_PLANE_VERTEX_COUNT = 6;
VertexFormat Geometry::SCREEN_PLANE_VERTEX_FORMAT = TRIANGLE_LIST;

int Geometry::FONT_PLANE_VERTEX_COUNT = 6;
VertexFormat Geometry::FONT_PLANE_VERTEX_FORMAT = TRIANGLE_LIST;

int Geometry::LINE_VERTEX_COUNT = 2;
VertexFormat Geometry::LINE_VERTEX_FORMAT = LINE_LIST;

unsigned int Geometry::screenPlane() {
  VertexDef quadVertices[6];
  quadVertices[0].vertex = Vector3(-1.0f, -1.0f, 0.0f);
  quadVertices[1].vertex = Vector3(1.0f, 1.0f, 0.0f);
  quadVertices[2].vertex = Vector3(-1.0f, 1.0f, 0.0f);
  quadVertices[3].vertex = Vector3(-1.0f, -1.0f, 0.0f);
  quadVertices[4].vertex = Vector3(1.0f, -1.0f, 0.0f);
  quadVertices[5].vertex = Vector3(1.0f, 1.0f, 0.0f);

  quadVertices[0].normal = Vector3(0.0f, 0.0f, 1.0f);
  quadVertices[1].normal = Vector3(0.0f, 0.0f, 1.0f);
  quadVertices[2].normal = Vector3(0.0f, 0.0f, 1.0f);
  quadVertices[3].normal = Vector3(0.0f, 0.0f, 1.0f);
  quadVertices[4].normal = Vector3(0.0f, 0.0f, 1.0f);
  quadVertices[5].normal = Vector3(0.0f, 0.0f, 1.0f);

  quadVertices[0].uv = Vector2(0.0f, 1.0f);
  quadVertices[1].uv = Vector2(1.0f, 0.0f);
  quadVertices[2].uv = Vector2(0.0f, 0.0f);
  quadVertices[3].uv = Vector2(0.0f, 1.0f);
  quadVertices[4].uv = Vector2(1.0f, 1.0f);
  quadVertices[5].uv = Vector2(1.0f, 0.0f);

  GraphicsInterface::VertexBuffer vbo = GraphicsInterface::createVertexBuffer(quadVertices, SCREEN_PLANE_VERTEX_COUNT);
  return vbo;
}

unsigned int Geometry::fontCharacter(const CSize& characterSize, const CSize& uvOffset, const CSize& fontTextureSize) {
  VertexDef quadVertices[6];
  quadVertices[0].vertex = Vector3(0.0f,                       (float)characterSize.height, 0.0f);
  quadVertices[1].vertex = Vector3(0.0f,                        0.0f,                       0.0f);
  quadVertices[2].vertex = Vector3((float)characterSize.width, (float)characterSize.height, 0.0f);
  
  quadVertices[3].vertex = Vector3((float)characterSize.width,  (float)characterSize.height,  0.0f);
  quadVertices[4].vertex = Vector3(0.0f,                        0.0f,                         0.0f);
  quadVertices[5].vertex = Vector3((float)characterSize.width,  0.0f,                         0.0f);

  quadVertices[0].normal = Vector3(0.0f, 0.0f, 1.0f);
  quadVertices[1].normal = Vector3(0.0f, 0.0f, 1.0f);
  quadVertices[2].normal = Vector3(0.0f, 0.0f, 1.0f);
  quadVertices[3].normal = Vector3(0.0f, 0.0f, 1.0f);
  quadVertices[4].normal = Vector3(0.0f, 0.0f, 1.0f);
  quadVertices[5].normal = Vector3(0.0f, 0.0f, 1.0f);

	Vector2 fontScale(1.0f/fontTextureSize.width, 1.0f/fontTextureSize.height);

	float uvLeft = fontScale.x * uvOffset.width;
	float uvRight = fontScale.x * uvOffset.width + fontScale.x * characterSize.width;

	float uvTop = fontScale.y * uvOffset.height;
	float uvBottom = fontScale.y * uvOffset.height + fontScale.y * characterSize.height;

  quadVertices[0].uv = Vector2(uvLeft,	uvTop);
  quadVertices[1].uv = Vector2(uvLeft, uvBottom);
  quadVertices[2].uv = Vector2(uvRight,	uvTop);
  quadVertices[3].uv = Vector2(uvRight,	uvTop);
  quadVertices[4].uv = Vector2(uvLeft, uvBottom);
  quadVertices[5].uv = Vector2(uvRight, uvBottom);

  GraphicsInterface::VertexBuffer vbo = GraphicsInterface::createVertexBuffer(quadVertices, FONT_PLANE_VERTEX_COUNT);
  return vbo;
}

unsigned int Geometry::line() {
	VertexDef lineVertices[2];

	lineVertices[0].vertex = Vector3(0.0f, 0.0f,	0.0f);
	lineVertices[1].vertex = Vector3(0.0f, 0.0f,	1.0f);

	lineVertices[0].uv = Vector2(0.0f, 0.0f);
	lineVertices[1].uv = Vector2(0.0f, 0.0f);

	lineVertices[0].normal = Vector3(0.0f, 1.0f, 0.0f);
	lineVertices[1].normal = Vector3(0.0f, 1.0f, 0.0f);

	GraphicsInterface::VertexBuffer vbo = GraphicsInterface::createVertexBuffer(lineVertices, LINE_VERTEX_COUNT);

	return vbo;
}
