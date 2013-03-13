#include "Mesh.h"

#include "GraphicsInterface.h"
#include "Model.h"

#include "VertexDefinition.h"
#include <algorithm>

void Mesh::init(VertexDef* vertexData, unsigned int numVertices, VertexFormat vertexFormat) {
  numVertices_ = numVertices;
  vertexFormat_ = vertexFormat;
  vertexBuffer_ = GraphicsInterface::createVertexBuffer(vertexData, numVertices);

	computeBoundingBox(vertexData, numVertices);
}

void Mesh::render() const {
  GraphicsInterface::drawVertexBuffer(vertexBuffer_, numVertices_, vertexFormat_);
}

void Mesh::visit(hash_map<IEffect*, std::vector<Mesh*> >& meshes) {
  meshes[material().effect()].push_back(this);
}

Matrix4x4 Mesh::localToWorld() const {
  return parent_->localToWorld();
}

void Mesh::setMaterialCallback(const std::string& materialName, Material::MaterialCallback callback, void* userData) {
	std::string name = material_.name();

	if (name.compare(materialName) == 0) {
		material_.setCallback(callback, userData);
	}
}

void Mesh::computeBoundingBox(VertexDef* vertexData, unsigned int numVertices) {
	for (unsigned int i = 0; i < numVertices; i++) {
		VertexDef vertex = vertexData[i];
		boundingBox_.min.x = std::min(boundingBox_.min.x, vertex.vertex.x);
		boundingBox_.max.x = std::max(boundingBox_.max.x, vertex.vertex.x);
		boundingBox_.min.y = std::min(boundingBox_.min.y, vertex.vertex.y);
		boundingBox_.max.y = std::max(boundingBox_.max.y, vertex.vertex.y);
		boundingBox_.min.z = std::min(boundingBox_.min.z, vertex.vertex.z);
		boundingBox_.max.z = std::max(boundingBox_.max.z, vertex.vertex.z);
	}
}
