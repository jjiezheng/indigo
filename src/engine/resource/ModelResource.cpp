#include "ModelResource.h"

#include <fstream>

#include "Standard.h"
#include "File.h"
#include "MeshResource.h"
#include "MaterialResource.h"
#include "TextureResource.h"

#include "json/reader.h"
#include "json/elements.h"
using namespace json;

static const char* MESHES_KEY = "meshes";

static const char* NORMALS_KEY = "normals";
static const char* NORMAL_STRIDE_KEY = "normal_stride";

static const char* VERTICES_KEY = "vertices";
static const char* VERTEX_STRIDE_KEY = "vertex_stride";

static const char* UVS_KEY = "uvs";
static const char* UVS_STRIDE_KEY = "uv_stride";

static const char* TRANSLATION_KEY = "translation";
static const char* ROTATION_KEY = "rotation";
static const char* SCALE_KEY = "scale";
static const char* MATERIALS_KEY = "materials";

static const char* DIFFUSE_KEY = "diffuse";
static const char* AMBIENT_KEY = "ambient";
static const char* SPECULAR_KEY = "specular";

static const char* TEXTURES_KEY = "textures";
static const char* FILENAME_KEY = "filename";

static const char* X_KEY = "x";
static const char* Y_KEY = "y";
static const char* Z_KEY = "z";
static const char* R_KEY = "r";
static const char* G_KEY = "g";
static const char* B_KEY = "b";

ModelResource* ModelResource::resource(const char* filepath) { 
  ModelResource* resource = new ModelResource();
  resource->load(filepath);
  return resource;
}

void ModelResource::load(const std::string &file) {
  File resource_file(file);
  std::stringstream file_data;
  file_data << resource_file.data();
  
  Object json_root;
  Reader::Read(json_root, file_data);
  
  Array meshes = json_root[MESHES_KEY];
  Array::const_iterator it_meshes = meshes.begin();
  Array::const_iterator it_meshes_end = meshes.end();
  for(; it_meshes != it_meshes_end; ++it_meshes) {
    const Object& mesh = *it_meshes;
    
    const Number& translation_x = mesh[TRANSLATION_KEY][X_KEY];
    const Number& translation_y = mesh[TRANSLATION_KEY][Y_KEY];
    const Number& translation_z = mesh[TRANSLATION_KEY][Z_KEY];
    VEC3 translation = VEC3(translation_x, translation_y, translation_z);

    const Number& rotation_x = mesh[ROTATION_KEY][X_KEY];
    const Number& rotation_y = mesh[ROTATION_KEY][Y_KEY];
    const Number& rotation_z = mesh[ROTATION_KEY][Z_KEY];
    VEC3 rotation = VEC3(rotation_x, rotation_y, rotation_z);

    const Number& scale_x = mesh[SCALE_KEY][X_KEY];
    const Number& scale_y = mesh[SCALE_KEY][Y_KEY];
    const Number& scale_z = mesh[SCALE_KEY][Z_KEY];
    VEC3 scale = VEC3(scale_x, scale_y, scale_z);
    
    const Array& vertices_data = mesh[VERTICES_KEY];
    const Number& vertex_stride = mesh[VERTEX_STRIDE_KEY];
    
    Array::const_iterator it_vertices = vertices_data.begin();
    Array::const_iterator it_vertices_end = vertices_data.end();
    int vertex_count = vertices_data.Size() / vertex_stride.Value();
    float* vertices = new float[vertices_data.Size()];
    int vi = 0;
    for(; it_vertices != it_vertices_end; ++it_vertices) {
      const Number& vertex_data = (*it_vertices);
      float vertex = vertex_data.Value();
      vertices[vi] = vertex;
      vi++;
    }

    const Array& normal_data = mesh[NORMALS_KEY];
    const Number& normal_stride = mesh[NORMAL_STRIDE_KEY];

    Array::const_iterator it_normals = normal_data.begin();
    Array::const_iterator it_normals_end = normal_data.end();
    int normal_count = normal_data.Size() / normal_stride.Value();
    float* normals = new float[normal_data.Size()];
    int ni = 0;
    for(; it_normals != it_normals_end; ++it_normals) {
      const Number& normal_data = (*it_normals);
      float normal = normal_data.Value();
      normals[ni] = normal;
      ni++;
    }

    const Array& uv_data = mesh[UVS_KEY];
    const Number& uv_stride = mesh[UVS_STRIDE_KEY];

    Array::const_iterator it_uvs = uv_data.begin();
    Array::const_iterator it_uvs_end = uv_data.end();
    int uv_count = uv_data.Size() / uv_stride.Value();
    float* uvs = new float[uv_data.Size()];
    int uvi = 0;
    for(; it_uvs != it_uvs_end; ++it_uvs) {
      const Number& uv_data = (*it_uvs);
      float uv = uv_data.Value();
      uvs[uvi] = uv;
      uvi++;
    }
    
    const Array& materials_data = mesh[MATERIALS_KEY];

    std::deque<MaterialResource*> materials;
    Array::const_iterator it_materials = materials_data.begin();
    Array::const_iterator it_materials_end = materials_data.end();
    for(; it_materials != it_materials_end; ++it_materials) {
      const Object& diffuse_data = (*it_materials)[DIFFUSE_KEY];
      Number diffuse_r = diffuse_data[R_KEY];
      Number diffuse_g = diffuse_data[G_KEY];
      Number diffuse_b = diffuse_data[B_KEY];
      glm::vec4 diffuse_color(diffuse_r, diffuse_g, diffuse_b, 1);
      
      const Object& ambient_data = (*it_materials)[AMBIENT_KEY];
      Number ambient_r = ambient_data[R_KEY];
      Number ambient_g = ambient_data[G_KEY];
      Number ambient_b = ambient_data[B_KEY];
      glm::vec4 ambient_color(ambient_r, ambient_g, ambient_b, 1);
      
      const Object& specular_data = (*it_materials)[SPECULAR_KEY];
      Number specular_r = specular_data[R_KEY];
      Number specular_g = specular_data[G_KEY];
      Number specular_b = specular_data[B_KEY];
      glm::vec4 specular_color(specular_r, specular_g, specular_b, 1);
    
      const Array& textures_data = (*it_materials)[TEXTURES_KEY];
      std::deque<TextureResource*> textures;
      Array::const_iterator it_textures = textures_data.begin();
      Array::const_iterator it_textures_end = textures_data.end();
      for(; it_textures != it_textures_end; ++it_textures) {
        const Object& texture_data = (*it_textures);
        String filename = texture_data[FILENAME_KEY];
        TextureResource* texture = 0;
//        TextureResource* texture = new TextureResource(platform_);
        texture->load(filename.Value());
        textures.push_back(texture);
      }
            
      MaterialResource* material = new MaterialResource(ambient_color, diffuse_color, specular_color, textures);
      materials.push_back(material);
    }
        
    MeshResource* mesh_resource = new MeshResource(vertices, vertex_count, vertex_stride.Value(), 
                                                   normals, normal_count, normal_stride.Value(), 
                                                   uvs, uv_count, uv_stride.Value(),
                                                   translation, rotation, scale, materials);
    meshes_.push_back(mesh_resource);
  }
}
