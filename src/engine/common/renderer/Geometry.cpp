#include "Geometry.h"

#include "GraphicsInterface.h"
#include "VertexDefinition.h"
#include "VertexFormat.h"
#include "maths/Angles.h"

const int Geometry::SCREEN_PLANE_VERTEX_COUNT = 6;
VertexFormat Geometry::SCREEN_PLANE_VERTEX_FORMAT = TRIANGLE_LIST;

const int Geometry::FONT_PLANE_VERTEX_COUNT = 6;
VertexFormat Geometry::FONT_PLANE_VERTEX_FORMAT = TRIANGLE_LIST;

VertexFormat Geometry::LINE_VERTEX_FORMAT = LINE_LIST;
VertexBuffer Geometry::LINE_VERTEX_BUFFER = 0;
VertexDef Geometry::LINE_VERTEX_DATA[LINE_VERTEX_COUNT];

VertexFormat Geometry::CONE_VERTEX_FORMAT = TRIANGLE_STRIP;
VertexBuffer Geometry::CONE_VERTEX_BUFFER = 0;
VertexDef Geometry::CONE_VERTEX_DATA[CONE_VERTEX_COUNT];

const int Geometry::UNIT_CUBE_VERTEX_COUNT = 36;
VertexFormat Geometry::UNIT_CUBE_VERTEX_FORMAT = TRIANGLE_LIST;
VertexBuffer Geometry::UNIT_CUBE_VERTEX_BUFFER = 0;

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

	VertexBuffer vbo = GraphicsInterface::createVertexBuffer(CONE_VERTEX_DATA, CONE_VERTEX_COUNT);
	return vbo;
}

VertexBuffer Geometry::unitCube() {
	VertexDef quadVertices[UNIT_CUBE_VERTEX_COUNT];

	// front
	quadVertices[0].vertex = Vector3(-1.0f, -1.0f, 1.0f);
	quadVertices[1].vertex = Vector3(1.0f, 1.0f, 1.0f);
	quadVertices[2].vertex = Vector3(-1.0f, 1.0f, 1.0f);
	quadVertices[3].vertex = Vector3(-1.0f, -1.0f, 1.0f);
	quadVertices[4].vertex = Vector3(1.0f, -1.0f, 1.0f);
	quadVertices[5].vertex = Vector3(1.0f, 1.0f, 1.0f);

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

	// back

	quadVertices[6].vertex = Vector3(1.0f, -1.0f, -1.0f);
	quadVertices[7].vertex = Vector3(-1.0f, 1.0f, -1.0f);
	quadVertices[8].vertex = Vector3(1.0f, 1.0f, -1.0f);
	quadVertices[9].vertex = Vector3(1.0f, -1.0f, -1.0f);
	quadVertices[10].vertex = Vector3(-1.0f, -1.0f, -1.0f);
	quadVertices[11].vertex = Vector3(-1.0f, 1.0f, -1.0f);

	quadVertices[6].normal = Vector3(0.0f, 0.0f, -1.0f);
	quadVertices[7].normal = Vector3(0.0f, 0.0f, -1.0f);
	quadVertices[8].normal = Vector3(0.0f, 0.0f, -1.0f);
	quadVertices[9].normal = Vector3(0.0f, 0.0f, -1.0f);
	quadVertices[10].normal = Vector3(0.0f, 0.0f, -1.0f);
	quadVertices[11].normal = Vector3(0.0f, 0.0f, -1.0f);

	quadVertices[6].uv = Vector2(0.0f, 1.0f);
	quadVertices[7].uv = Vector2(1.0f, 0.0f);
	quadVertices[8].uv = Vector2(0.0f, 0.0f);
	quadVertices[9].uv = Vector2(0.0f, 1.0f);
	quadVertices[10].uv = Vector2(1.0f, 1.0f);
	quadVertices[11].uv = Vector2(1.0f, 0.0f);

	// right

	quadVertices[12].vertex = Vector3(1.0f, -1.0f, 1.0f);
	quadVertices[13].vertex = Vector3(1.0f, 1.0f,  -1.0f);
	quadVertices[14].vertex = Vector3(1.0f, 1.0f, 1.0f);
	quadVertices[15].vertex = Vector3(1.0f, -1.0f, 1.0f);
	quadVertices[16].vertex = Vector3(1.0f, -1.0f, -1.0f);
	quadVertices[17].vertex = Vector3(1.0f, 1.0f, -1.0f);

	quadVertices[12].normal = Vector3(1.0f, 0.0f, 0.0f);
	quadVertices[13].normal = Vector3(1.0f, 0.0f, 0.0f);
	quadVertices[14].normal = Vector3(1.0f, 0.0f, 0.0f);
	quadVertices[15].normal = Vector3(1.0f, 0.0f, 0.0f);
	quadVertices[16].normal = Vector3(1.0f, 0.0f, 0.0f);
	quadVertices[17].normal = Vector3(1.0f, 0.0f, 0.0f);

	quadVertices[12].uv = Vector2(0.0f, 1.0f);
	quadVertices[13].uv = Vector2(1.0f, 0.0f);
	quadVertices[14].uv = Vector2(0.0f, 0.0f);
	quadVertices[15].uv = Vector2(0.0f, 1.0f);
	quadVertices[16].uv = Vector2(1.0f, 1.0f);
	quadVertices[17].uv = Vector2(1.0f, 0.0f);

	// left

	quadVertices[18].vertex = Vector3(-1.0f, -1.0f, -1.0f);
	quadVertices[19].vertex = Vector3(-1.0f, 1.0f,  1.0f);
	quadVertices[20].vertex = Vector3(-1.0f, 1.0f, -1.0f);
	quadVertices[21].vertex = Vector3(-1.0f, -1.0f, -1.0f);
	quadVertices[22].vertex = Vector3(-1.0f, -1.0f, 1.0f);
	quadVertices[23].vertex = Vector3(-1.0f, 1.0f, 1.0f);

	quadVertices[18].normal = Vector3(-1.0f, 0.0f, 0.0f);
	quadVertices[19].normal = Vector3(-1.0f, 0.0f, 0.0f);
	quadVertices[20].normal = Vector3(-1.0f, 0.0f, 0.0f);
	quadVertices[21].normal = Vector3(-1.0f, 0.0f, 0.0f);
	quadVertices[22].normal = Vector3(-1.0f, 0.0f, 0.0f);
	quadVertices[23].normal = Vector3(-1.0f, 0.0f, 0.0f);

	quadVertices[18].uv = Vector2(0.0f, 1.0f);
	quadVertices[19].uv = Vector2(1.0f, 0.0f);
	quadVertices[20].uv = Vector2(0.0f, 0.0f);
	quadVertices[21].uv = Vector2(0.0f, 1.0f);
	quadVertices[22].uv = Vector2(1.0f, 1.0f);
	quadVertices[23].uv = Vector2(1.0f, 0.0f);

	// top

	quadVertices[24].vertex = Vector3(-1.0f, 1.0f, 1.0f);
	quadVertices[25].vertex = Vector3(1.0f, 1.0f,  -1.0f);
	quadVertices[26].vertex = Vector3(-1.0f, 1.0f, -1.0f);
	quadVertices[27].vertex = Vector3(-1.0f, 1.0f, 1.0f);
	quadVertices[28].vertex = Vector3(1.0f, 1.0f, 1.0f);
	quadVertices[29].vertex = Vector3(1.0f, 1.0f, -1.0f);

	quadVertices[24].normal = Vector3(0.0f, 1.0f, 0.0f);
	quadVertices[25].normal = Vector3(0.0f, 1.0f, 0.0f);
	quadVertices[26].normal = Vector3(0.0f, 1.0f, 0.0f);
	quadVertices[27].normal = Vector3(0.0f, 1.0f, 0.0f);
	quadVertices[28].normal = Vector3(0.0f, 1.0f, 0.0f);
	quadVertices[29].normal = Vector3(0.0f, 1.0f, 0.0f);

	quadVertices[24].uv = Vector2(0.0f, 1.0f);
	quadVertices[25].uv = Vector2(1.0f, 0.0f);
	quadVertices[26].uv = Vector2(0.0f, 0.0f);
	quadVertices[27].uv = Vector2(0.0f, 1.0f);
	quadVertices[28].uv = Vector2(1.0f, 1.0f);
	quadVertices[29].uv = Vector2(1.0f, 0.0f);

	// bottom

	quadVertices[30].vertex = Vector3(1.0f, -1.0f, 1.0f);
	quadVertices[31].vertex = Vector3(-1.0f, -1.0f, -1.0f);
	quadVertices[32].vertex = Vector3(1.0f, -1.0f, -1.0f);
	quadVertices[33].vertex = Vector3(1.0f, -1.0f, 1.0f);
	quadVertices[34].vertex = Vector3(-1.0f, -1.0f, 1.0f);
	quadVertices[35].vertex = Vector3(-1.0f, -1.0f, -1.0f);

	quadVertices[30].normal = Vector3(0.0f, -1.0f, 0.0f);
	quadVertices[31].normal = Vector3(0.0f, -1.0f, 0.0f);
	quadVertices[32].normal = Vector3(0.0f, -1.0f, 0.0f);
	quadVertices[33].normal = Vector3(0.0f, -1.0f, 0.0f);
	quadVertices[34].normal = Vector3(0.0f, -1.0f, 0.0f);
	quadVertices[35].normal = Vector3(0.0f, -1.0f, 0.0f);

	quadVertices[30].uv = Vector2(0.0f, 1.0f);
	quadVertices[21].uv = Vector2(1.0f, 0.0f);
	quadVertices[32].uv = Vector2(0.0f, 0.0f);
	quadVertices[33].uv = Vector2(0.0f, 1.0f);
	quadVertices[34].uv = Vector2(1.0f, 1.0f);
	quadVertices[35].uv = Vector2(1.0f, 0.0f);

	VertexBuffer vbo = GraphicsInterface::createVertexBuffer(quadVertices, UNIT_CUBE_VERTEX_COUNT);
	return vbo;
}

void Geometry::init() {
  LINE_VERTEX_BUFFER = line();
  CONE_VERTEX_BUFFER = cone();
  UNIT_CUBE_VERTEX_BUFFER = unitCube();
}

