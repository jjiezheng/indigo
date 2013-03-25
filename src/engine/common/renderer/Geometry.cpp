#include "Geometry.h"

#include "GraphicsInterface.h"
#include "VertexDefinition.h"
#include "VertexFormat.h"
#include "maths/Angles.h"

VertexFormat Geometry::SCREEN_PLANE_VERTEX_FORMAT = TRIANGLE_LIST;

VertexFormat Geometry::FONT_PLANE_VERTEX_FORMAT = TRIANGLE_LIST;

VertexFormat Geometry::LINE_VERTEX_FORMAT = LINE_LIST;
VertexBuffer Geometry::LINE_VERTEX_BUFFER = 0;
VertexDef Geometry::LINE_VERTEX_DATA[LINE_VERTEX_COUNT];

VertexFormat Geometry::CONE_VERTEX_FORMAT = TRIANGLE_STRIP;
VertexBuffer Geometry::CONE_VERTEX_BUFFER = 0;
VertexDef Geometry::CONE_VERTEX_DATA[CONE_VERTEX_COUNT];

VertexFormat Geometry::UNIT_CUBE_VERTEX_FORMAT = TRIANGLE_LIST;
VertexBuffer Geometry::UNIT_CUBE_VERTEX_BUFFER = 0;
VertexDef Geometry::UNIT_CUBE_VERTEX_DATA[UNIT_CUBE_VERTEX_COUNT];

VertexFormat Geometry::UNIT_CIRCLE_VERTEX_FORMAT = LINE_STRIP;
VertexBuffer Geometry::UNIT_CIRCLE_VERTEX_BUFFER = 0;
VertexDef Geometry::UNIT_CIRCLE_VERTEX_DATA[UNIT_CIRCLE_VERTEX_COUNT];

VertexFormat Geometry::UNIT_SEMI_CIRCLE_VERTEX_FORMAT = LINE_STRIP;
VertexBuffer Geometry::UNIT_SEMI_CIRCLE_VERTEX_BUFFER = 0;
VertexDef Geometry::UNIT_SEMI_CIRCLE_VERTEX_DATA[UNIT_SEMI_CIRCLE_VERTEX_COUNT];

VertexBuffer Geometry::screenPlane() {
  VertexDef quadVertices[SCREEN_PLANE_VERTEX_COUNT];
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

  VertexBuffer vbo = GraphicsInterface::createVertexBuffer(quadVertices, SCREEN_PLANE_VERTEX_COUNT);
  return vbo;
}

VertexBuffer Geometry::fontCharacter(const CSize& characterSize, const CSize& uvOffset, const CSize& fontTextureSize) {
  VertexDef quadVertices[FONT_PLANE_VERTEX_COUNT];
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

  VertexBuffer vbo = GraphicsInterface::createVertexBuffer(quadVertices, FONT_PLANE_VERTEX_COUNT);
  return vbo;
}

VertexBuffer Geometry::line() {
	LINE_VERTEX_DATA[0].vertex = Vector3(0.0f, 0.0f,	0.0f);
	LINE_VERTEX_DATA[1].vertex = Vector3(0.0f, 0.0f,	1.0f);

	LINE_VERTEX_DATA[0].uv = Vector2(0.0f, 0.0f);
	LINE_VERTEX_DATA[1].uv = Vector2(0.0f, 0.0f);

	LINE_VERTEX_DATA[0].normal = Vector3(0.0f, 1.0f, 0.0f);
	LINE_VERTEX_DATA[1].normal = Vector3(0.0f, 1.0f, 0.0f);

  VertexBuffer vbo = GraphicsInterface::createVertexBuffer(LINE_VERTEX_DATA, LINE_VERTEX_COUNT);
  return vbo;
}

VertexBuffer Geometry::cone() {

  int index = 0;
  for (int i = 0; i < CONE_VERTEX_COUNT / 2.0f; i++) {
    float radians = toDegrees((float)i);

    float x = cos(radians);
    float y = sin(radians);

    CONE_VERTEX_DATA[index++].vertex = Vector3(x, y, 0.0f);
    CONE_VERTEX_DATA[index++].vertex = Vector3(0.0f, 0.0f, 2.0f);
  }

  VertexBuffer vbo = GraphicsInterface::createVertexBuffer(CONE_VERTEX_DATA, UNIT_CUBE_VERTEX_COUNT);
  return vbo;
}

VertexBuffer Geometry::unitCircle() {
  int index = 0;
  for (int i = 0; i < UNIT_CIRCLE_VERTEX_COUNT; i++) {
    float radians = toRadians((float)i);

    float x = cos(radians);
    float y = sin(radians);

    UNIT_CIRCLE_VERTEX_DATA[index++].vertex = Vector3(x, y, 0.0f);
  }

  VertexBuffer vbo = GraphicsInterface::createVertexBuffer(UNIT_CIRCLE_VERTEX_DATA, UNIT_CIRCLE_VERTEX_COUNT);
  return vbo;
}

VertexBuffer Geometry::unitSemiCircle() {
  int index = 0;
  for (int i = 0; i < UNIT_SEMI_CIRCLE_VERTEX_COUNT; i++) {
    float radians = toRadians((float)i);
    
    float x = cos(radians);
    float y = sin(radians);
    
    UNIT_CIRCLE_VERTEX_DATA[index++].vertex = Vector3(x, y, 0.0f);
  }
  
  VertexBuffer vbo = GraphicsInterface::createVertexBuffer(UNIT_CIRCLE_VERTEX_DATA, UNIT_CIRCLE_VERTEX_COUNT);
  return vbo;
}


VertexBuffer Geometry::unitCube() {
	// front
	UNIT_CUBE_VERTEX_DATA[0].vertex = Vector3(-1.0f, -1.0f, 1.0f);
	UNIT_CUBE_VERTEX_DATA[1].vertex = Vector3(1.0f, 1.0f, 1.0f);
	UNIT_CUBE_VERTEX_DATA[2].vertex = Vector3(-1.0f, 1.0f, 1.0f);
	UNIT_CUBE_VERTEX_DATA[3].vertex = Vector3(-1.0f, -1.0f, 1.0f);
	UNIT_CUBE_VERTEX_DATA[4].vertex = Vector3(1.0f, -1.0f, 1.0f);
	UNIT_CUBE_VERTEX_DATA[5].vertex = Vector3(1.0f, 1.0f, 1.0f);

	UNIT_CUBE_VERTEX_DATA[0].normal = Vector3(0.0f, 0.0f, 1.0f);
	UNIT_CUBE_VERTEX_DATA[1].normal = Vector3(0.0f, 0.0f, 1.0f);
	UNIT_CUBE_VERTEX_DATA[2].normal = Vector3(0.0f, 0.0f, 1.0f);
	UNIT_CUBE_VERTEX_DATA[3].normal = Vector3(0.0f, 0.0f, 1.0f);
	UNIT_CUBE_VERTEX_DATA[4].normal = Vector3(0.0f, 0.0f, 1.0f);
	UNIT_CUBE_VERTEX_DATA[5].normal = Vector3(0.0f, 0.0f, 1.0f);

	UNIT_CUBE_VERTEX_DATA[0].uv = Vector2(0.0f, 1.0f);
	UNIT_CUBE_VERTEX_DATA[1].uv = Vector2(1.0f, 0.0f);
	UNIT_CUBE_VERTEX_DATA[2].uv = Vector2(0.0f, 0.0f);
	UNIT_CUBE_VERTEX_DATA[3].uv = Vector2(0.0f, 1.0f);
	UNIT_CUBE_VERTEX_DATA[4].uv = Vector2(1.0f, 1.0f);
	UNIT_CUBE_VERTEX_DATA[5].uv = Vector2(1.0f, 0.0f);

	// back

	UNIT_CUBE_VERTEX_DATA[6].vertex = Vector3(1.0f, -1.0f, -1.0f);
	UNIT_CUBE_VERTEX_DATA[7].vertex = Vector3(-1.0f, 1.0f, -1.0f);
	UNIT_CUBE_VERTEX_DATA[8].vertex = Vector3(1.0f, 1.0f, -1.0f);
	UNIT_CUBE_VERTEX_DATA[9].vertex = Vector3(1.0f, -1.0f, -1.0f);
	UNIT_CUBE_VERTEX_DATA[10].vertex = Vector3(-1.0f, -1.0f, -1.0f);
	UNIT_CUBE_VERTEX_DATA[11].vertex = Vector3(-1.0f, 1.0f, -1.0f);

	UNIT_CUBE_VERTEX_DATA[6].normal = Vector3(0.0f, 0.0f, -1.0f);
	UNIT_CUBE_VERTEX_DATA[7].normal = Vector3(0.0f, 0.0f, -1.0f);
	UNIT_CUBE_VERTEX_DATA[8].normal = Vector3(0.0f, 0.0f, -1.0f);
	UNIT_CUBE_VERTEX_DATA[9].normal = Vector3(0.0f, 0.0f, -1.0f);
	UNIT_CUBE_VERTEX_DATA[10].normal = Vector3(0.0f, 0.0f, -1.0f);
	UNIT_CUBE_VERTEX_DATA[11].normal = Vector3(0.0f, 0.0f, -1.0f);

	UNIT_CUBE_VERTEX_DATA[6].uv = Vector2(0.0f, 1.0f);
	UNIT_CUBE_VERTEX_DATA[7].uv = Vector2(1.0f, 0.0f);
	UNIT_CUBE_VERTEX_DATA[8].uv = Vector2(0.0f, 0.0f);
	UNIT_CUBE_VERTEX_DATA[9].uv = Vector2(0.0f, 1.0f);
	UNIT_CUBE_VERTEX_DATA[10].uv = Vector2(1.0f, 1.0f);
	UNIT_CUBE_VERTEX_DATA[11].uv = Vector2(1.0f, 0.0f);

	// right

	UNIT_CUBE_VERTEX_DATA[12].vertex = Vector3(1.0f, -1.0f, 1.0f);
	UNIT_CUBE_VERTEX_DATA[13].vertex = Vector3(1.0f, 1.0f,  -1.0f);
	UNIT_CUBE_VERTEX_DATA[14].vertex = Vector3(1.0f, 1.0f, 1.0f);
	UNIT_CUBE_VERTEX_DATA[15].vertex = Vector3(1.0f, -1.0f, 1.0f);
	UNIT_CUBE_VERTEX_DATA[16].vertex = Vector3(1.0f, -1.0f, -1.0f);
	UNIT_CUBE_VERTEX_DATA[17].vertex = Vector3(1.0f, 1.0f, -1.0f);

	UNIT_CUBE_VERTEX_DATA[12].normal = Vector3(1.0f, 0.0f, 0.0f);
	UNIT_CUBE_VERTEX_DATA[13].normal = Vector3(1.0f, 0.0f, 0.0f);
	UNIT_CUBE_VERTEX_DATA[14].normal = Vector3(1.0f, 0.0f, 0.0f);
	UNIT_CUBE_VERTEX_DATA[15].normal = Vector3(1.0f, 0.0f, 0.0f);
	UNIT_CUBE_VERTEX_DATA[16].normal = Vector3(1.0f, 0.0f, 0.0f);
	UNIT_CUBE_VERTEX_DATA[17].normal = Vector3(1.0f, 0.0f, 0.0f);

	UNIT_CUBE_VERTEX_DATA[12].uv = Vector2(0.0f, 1.0f);
	UNIT_CUBE_VERTEX_DATA[13].uv = Vector2(1.0f, 0.0f);
	UNIT_CUBE_VERTEX_DATA[14].uv = Vector2(0.0f, 0.0f);
	UNIT_CUBE_VERTEX_DATA[15].uv = Vector2(0.0f, 1.0f);
	UNIT_CUBE_VERTEX_DATA[16].uv = Vector2(1.0f, 1.0f);
	UNIT_CUBE_VERTEX_DATA[17].uv = Vector2(1.0f, 0.0f);

	// left

	UNIT_CUBE_VERTEX_DATA[18].vertex = Vector3(-1.0f, -1.0f, -1.0f);
	UNIT_CUBE_VERTEX_DATA[19].vertex = Vector3(-1.0f, 1.0f,  1.0f);
	UNIT_CUBE_VERTEX_DATA[20].vertex = Vector3(-1.0f, 1.0f, -1.0f);
	UNIT_CUBE_VERTEX_DATA[21].vertex = Vector3(-1.0f, -1.0f, -1.0f);
	UNIT_CUBE_VERTEX_DATA[22].vertex = Vector3(-1.0f, -1.0f, 1.0f);
	UNIT_CUBE_VERTEX_DATA[23].vertex = Vector3(-1.0f, 1.0f, 1.0f);

	UNIT_CUBE_VERTEX_DATA[18].normal = Vector3(-1.0f, 0.0f, 0.0f);
	UNIT_CUBE_VERTEX_DATA[19].normal = Vector3(-1.0f, 0.0f, 0.0f);
	UNIT_CUBE_VERTEX_DATA[20].normal = Vector3(-1.0f, 0.0f, 0.0f);
	UNIT_CUBE_VERTEX_DATA[21].normal = Vector3(-1.0f, 0.0f, 0.0f);
	UNIT_CUBE_VERTEX_DATA[22].normal = Vector3(-1.0f, 0.0f, 0.0f);
	UNIT_CUBE_VERTEX_DATA[23].normal = Vector3(-1.0f, 0.0f, 0.0f);

	UNIT_CUBE_VERTEX_DATA[18].uv = Vector2(0.0f, 1.0f);
	UNIT_CUBE_VERTEX_DATA[19].uv = Vector2(1.0f, 0.0f);
	UNIT_CUBE_VERTEX_DATA[20].uv = Vector2(0.0f, 0.0f);
	UNIT_CUBE_VERTEX_DATA[21].uv = Vector2(0.0f, 1.0f);
	UNIT_CUBE_VERTEX_DATA[22].uv = Vector2(1.0f, 1.0f);
	UNIT_CUBE_VERTEX_DATA[23].uv = Vector2(1.0f, 0.0f);

	// top

	UNIT_CUBE_VERTEX_DATA[24].vertex = Vector3(-1.0f, 1.0f, 1.0f);
	UNIT_CUBE_VERTEX_DATA[25].vertex = Vector3(1.0f, 1.0f,  -1.0f);
	UNIT_CUBE_VERTEX_DATA[26].vertex = Vector3(-1.0f, 1.0f, -1.0f);
	UNIT_CUBE_VERTEX_DATA[27].vertex = Vector3(-1.0f, 1.0f, 1.0f);
	UNIT_CUBE_VERTEX_DATA[28].vertex = Vector3(1.0f, 1.0f, 1.0f);
	UNIT_CUBE_VERTEX_DATA[29].vertex = Vector3(1.0f, 1.0f, -1.0f);

	UNIT_CUBE_VERTEX_DATA[24].normal = Vector3(0.0f, 1.0f, 0.0f);
	UNIT_CUBE_VERTEX_DATA[25].normal = Vector3(0.0f, 1.0f, 0.0f);
	UNIT_CUBE_VERTEX_DATA[26].normal = Vector3(0.0f, 1.0f, 0.0f);
	UNIT_CUBE_VERTEX_DATA[27].normal = Vector3(0.0f, 1.0f, 0.0f);
	UNIT_CUBE_VERTEX_DATA[28].normal = Vector3(0.0f, 1.0f, 0.0f);
	UNIT_CUBE_VERTEX_DATA[29].normal = Vector3(0.0f, 1.0f, 0.0f);

	UNIT_CUBE_VERTEX_DATA[24].uv = Vector2(0.0f, 1.0f);
	UNIT_CUBE_VERTEX_DATA[25].uv = Vector2(1.0f, 0.0f);
	UNIT_CUBE_VERTEX_DATA[26].uv = Vector2(0.0f, 0.0f);
	UNIT_CUBE_VERTEX_DATA[27].uv = Vector2(0.0f, 1.0f);
	UNIT_CUBE_VERTEX_DATA[28].uv = Vector2(1.0f, 1.0f);
	UNIT_CUBE_VERTEX_DATA[29].uv = Vector2(1.0f, 0.0f);

	// bottom

	UNIT_CUBE_VERTEX_DATA[30].vertex = Vector3(1.0f, -1.0f, 1.0f);
	UNIT_CUBE_VERTEX_DATA[31].vertex = Vector3(-1.0f, -1.0f, -1.0f);
	UNIT_CUBE_VERTEX_DATA[32].vertex = Vector3(1.0f, -1.0f, -1.0f);
	UNIT_CUBE_VERTEX_DATA[33].vertex = Vector3(1.0f, -1.0f, 1.0f);
	UNIT_CUBE_VERTEX_DATA[34].vertex = Vector3(-1.0f, -1.0f, 1.0f);
	UNIT_CUBE_VERTEX_DATA[35].vertex = Vector3(-1.0f, -1.0f, -1.0f);

	UNIT_CUBE_VERTEX_DATA[30].normal = Vector3(0.0f, -1.0f, 0.0f);
	UNIT_CUBE_VERTEX_DATA[31].normal = Vector3(0.0f, -1.0f, 0.0f);
	UNIT_CUBE_VERTEX_DATA[32].normal = Vector3(0.0f, -1.0f, 0.0f);
	UNIT_CUBE_VERTEX_DATA[33].normal = Vector3(0.0f, -1.0f, 0.0f);
	UNIT_CUBE_VERTEX_DATA[34].normal = Vector3(0.0f, -1.0f, 0.0f);
	UNIT_CUBE_VERTEX_DATA[35].normal = Vector3(0.0f, -1.0f, 0.0f);

	UNIT_CUBE_VERTEX_DATA[30].uv = Vector2(0.0f, 1.0f);
	UNIT_CUBE_VERTEX_DATA[21].uv = Vector2(1.0f, 0.0f);
	UNIT_CUBE_VERTEX_DATA[32].uv = Vector2(0.0f, 0.0f);
	UNIT_CUBE_VERTEX_DATA[33].uv = Vector2(0.0f, 1.0f);
	UNIT_CUBE_VERTEX_DATA[34].uv = Vector2(1.0f, 1.0f);
	UNIT_CUBE_VERTEX_DATA[35].uv = Vector2(1.0f, 0.0f);

	VertexBuffer vbo = GraphicsInterface::createVertexBuffer(UNIT_CUBE_VERTEX_DATA, UNIT_CUBE_VERTEX_COUNT);
	return vbo;
}

void Geometry::init() {
  LINE_VERTEX_BUFFER = line();
  CONE_VERTEX_BUFFER = cone();
  UNIT_CUBE_VERTEX_BUFFER = unitCube();
  UNIT_CIRCLE_VERTEX_BUFFER = unitCircle();
  UNIT_SEMI_CIRCLE_VERTEX_BUFFER = unitSemiCircle();
}
