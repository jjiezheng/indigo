#include "LevelFile.h"

#include "Standard.h"
#include "File.h"
#include "json/reader.h"
//#include "EntityComponent.h"
#include "LevelResource.h"
#include "SkyBox.h"

using namespace json;

LevelFile* LevelFile::level_file(LevelResource* level_resource) {
  return new LevelFile(level_resource);
}

SkyBox* LevelFile::skybox() {
  std::stringstream data;
  data << level_resource_->data();
  
  Object rootObject;
  Reader::Read(rootObject, data);

  const Object& jsonAttributes = rootObject["attributes"];
  const String& jsonSkyBox = jsonAttributes["skybox"];
    
  return SkyBox::skybox(jsonSkyBox.Value());
}

/*std::deque<EntityComponent*> LevelFile::components() {
  std::deque<EntityComponent*> components;
  INT component_id = 0;
  
  std::stringstream data;
  data << level_resource_->data();
  
  Object rootObject;
  Reader::Read(rootObject, data);
  
  const Array& jsonEntities = rootObject["entities"];

  Array::const_iterator itEntities = jsonEntities.Begin();
  for (; itEntities != jsonEntities.End(); ++itEntities) {
    
    ++component_id;
    
    const Array& jsonComponents = (*itEntities)["components"];
    Array::const_iterator itComponents = jsonComponents.Begin();
    for (; itComponents != jsonComponents.End(); ++itComponents) {
      
      const Object& component_object = *itComponents;
      Object::const_iterator itComponentValues(component_object.Begin());
      
      EntityComponent* component = EntityComponent::component(component_id);
      
      for (; itComponentValues != component_object.End(); ++itComponentValues) {
        const Object::Member& member = (*itComponentValues);
        const std::string& name = member.name;

        try {
          String value = member.element;
          component->set_attribute(name.c_str(), value.Value());
        } catch(Exception str) { }
        
        try { 
          Number value = member.element;
          component->set_attribute(name.c_str(), value.Value());
        } catch(Exception str) { }
        
        try { 
          Boolean value = member.element;
          component->set_attribute(name.c_str(), value.Value());
        } catch(Exception str) { }

      }
      
      components.push_back(component);
    }
  }
  
  return components;
}*/
