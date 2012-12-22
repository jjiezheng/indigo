#include "Mesh.h"

#include "GraphicsInterface.h"
#include "Model.h"

void Mesh::init(VertexDef* vertexData, unsigned int numVertices, VertexFormat vertexFormat) {
  numVertices_ = numVertices;
  vertexFormat_ = vertexFormat;
  vertexBuffer_ = GraphicsInterface::createVertexBuffer(vertexData, numVertices);
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

void Mesh::setMaterialCallback(const std::string& materialName, Material::MaterialCallback callback) {
	std::string name = material_.name();

	if (name.compare(materialName) == 0) {
		material_.setCallback(callback);
	}
}
