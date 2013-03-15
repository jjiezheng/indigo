#include "TranslateGizmo.h"

#include "renderer/EffectCache.h"
#include "renderer/IViewer.h"
#include "renderer/IEffect.h"
#include "renderer/GraphicsInterface.h"
#include "renderer/Model.h"
#include "renderer/Geometry.h"

#include "maths/Angles.h"

#include "maths/Matrix4x4.h"

void TranslateGizmo::init() {
  effect_ = EffectCache::instance()->loadEffect("shaders/compiled/color.shader");

	coneMesh_.createBuffers(Geometry::CONE_VERTEX_DATA, Geometry::CONE_VERTEX_COUNT, Geometry::CONE_VERTEX_FORMAT);
	coneMesh_.computeBoundingBox(Geometry::CONE_VERTEX_DATA, Geometry::CONE_VERTEX_COUNT, Geometry::CONE_VERTEX_FORMAT);
}

void TranslateGizmo::render(IViewer* viewer) {
  //if (NULL != selected_) {

  //     BoundingBox bounds = selected_->boundingBox();
  // 
  //     Vector4 translation(bounds.max.x + bounds.min.x, bounds.max.y + bounds.min.y, bounds.max.z + bounds.min.z, 2.0f);
  //     translation /= 2.0f;
  // 
  //     Matrix4x4 model = selected_->localToWorld() * Matrix4x4::translation(translation);

  //     Vector3 selectedPosition = selected_->localToWorld().translation();
  //     float kDistanceToScaleFactor = 0.1f;
  //     float distanceToSelection = viewer->position().distance(selectedPosition);
  //     Matrix4x4 viewScale = Matrix4x4::scale(distanceToSelection * kDistanceToScaleFactor);


    GraphicsInterface::beginPerformanceEvent("Selection");
    GraphicsInterface::resetRenderTarget(false);
    GraphicsInterface::setViewport(GraphicsInterface::backBufferSize());
    GraphicsInterface::setBlendState(IGraphicsInterface::NOBLEND);
    GraphicsInterface::setRenderState(CULL_MODE_NONE, true);
    
    // + z
    {
      Model arrowModel;
			Node arrowNode;

      {
				arrowModel.addMesh(coneMesh_);


        Mesh coneMesh;
        coneMesh.createBuffers(Geometry::CONE_VERTEX_DATA, Geometry::CONE_VERTEX_COUNT, Geometry::CONE_VERTEX_FORMAT);
        coneMesh.computeBoundingBox(Geometry::CONE_VERTEX_DATA, Geometry::CONE_VERTEX_COUNT);

        Matrix4x4 translationAlongLine = Matrix4x4::translation(Vector4(0, 0, 1, 0));
        Matrix4x4 coneLocalToParent = translationAlongLine * Matrix4x4::scale(0.1f) * Matrix4x4::scale(Vector4(0.5f, 0.5f, 2.0f, 1.0f));
        coneMesh.setLocalToParent(coneLocalToParent);

        arrowModel.addMesh(coneMesh);

				Mesh lineMesh;
				lineMesh.createBuffers(Geometry::LINE_VERTEX_DATA, Geometry::LINE_VERTEX_COUNT, Geometry::LINE_VERTEX_FORMAT);
				lineMesh.computeBoundingBox(Geometry::LINE_VERTEX_DATA, Geometry::LINE_VERTEX_COUNT);
        arrowModel.addMesh(lineMesh);

        arrowModel.computeBoundingBox();
      }
   
      {
        effect_->beginDraw();

        BoundingBox bounds = arrowModel.boundingBox();

        Vector4 scale(bounds.max.x - bounds.min.x, bounds.max.y - bounds.min.y, bounds.max.z - bounds.min.z, 2.0f);
        scale /= 2.0f;

        Vector4 translation(bounds.max.x + bounds.min.x, bounds.max.y + bounds.min.y, bounds.max.z + bounds.min.z, 2.0f);
        translation /= 2.0f;

        Matrix4x4 model = arrowModel.localToWorld() * Matrix4x4::translation(translation) * Matrix4x4::scale(scale);
        Matrix4x4 modelViewProjection = viewer->projection() * viewer->viewTransform() * model * Matrix4x4::scale(1.0001f);

        effect_->setUniform(modelViewProjection, "ModelViewProj");
        effect_->setUniform(Color3::GREEN, "Color");

        effect_->commitBuffers();
        GraphicsInterface::drawVertexBuffer(Geometry::UNIT_CUBE_VERTEX_BUFFER, Geometry::UNIT_CUBE_VERTEX_COUNT, Geometry::UNIT_CUBE_VERTEX_FORMAT);
        effect_->endDraw();
      }

      hash_map<IEffect*, std::vector<Mesh*> > effects;
      arrowModel.visit(effects);

      hash_map<IEffect*, std::vector<Mesh*> >::iterator i = effects.begin();
      for (; i != effects.end(); ++i) {
        std::vector<Mesh*> effectMeshes = (*i).second;
        for (std::vector<Mesh*>::iterator meshIt = effectMeshes.begin(); meshIt != effectMeshes.end(); ++meshIt) {

          effect_->beginDraw();

          Matrix4x4 modelViewProjection = viewer->projection() * viewer->viewTransform() * (*meshIt)->localToWorld();
          effect_->setUniform(modelViewProjection, "ModelViewProj");
          effect_->setUniform(Color3::GREEN, "Color");

          GraphicsInterface::setRenderState(CULL_MODE_NONE, false);

          effect_->setUniform(Color3::RED, "Color");
          effect_->commitBuffers();
          (*meshIt)->render();

          effect_->endDraw();
        }

      }

      // lines
      /*{
        // +y line
        {
          effect_->beginDraw();

          Matrix4x4 modelViewProjection = viewer->projection() * viewer->viewTransform() * model * Matrix4x4::rotationX(toRadians(-90)) * viewScale;
          effect_->setUniform(modelViewProjection, "ModelViewProj");
          effect_->setUniform(Color3::GREEN, "Color");

          effect_->commitBuffers();
          GraphicsInterface::drawVertexBuffer(Geometry::LINE_VERTEX_BUFFER, Geometry::LINE_VERTEX_COUNT, Geometry::LINE_VERTEX_FORMAT);
          effect_->endDraw();
        }

        // +x line
        {
          effect_->beginDraw();

          Matrix4x4 modelViewProjection = viewer->projection() * viewer->viewTransform() * model * Matrix4x4::rotationY(toRadians(90)) * viewScale;
          effect_->setUniform(modelViewProjection, "ModelViewProj");
          effect_->setUniform(Color3::RED, "Color");

          effect_->commitBuffers();
          GraphicsInterface::drawVertexBuffer(Geometry::LINE_VERTEX_BUFFER, Geometry::LINE_VERTEX_COUNT, Geometry::LINE_VERTEX_FORMAT);
          effect_->endDraw();
        }

        // +z line
        {
          effect_->beginDraw();

          Matrix4x4 modelViewProjection = viewer->projection() * viewer->viewTransform() * model * viewScale;
          effect_->setUniform(modelViewProjection, "ModelViewProj");
          effect_->setUniform(Color3::BLUE, "Color");

          effect_->commitBuffers();
          GraphicsInterface::drawVertexBuffer(Geometry::LINE_VERTEX_BUFFER, Geometry::LINE_VERTEX_COUNT, Geometry::LINE_VERTEX_FORMAT);
          effect_->endDraw();
        }
      }
      
      // cones
      {
        // +x cone
        {
          effect_->beginDraw();

          Matrix4x4 translationAlongLine = Matrix4x4::translation(Vector4(1 * distanceToSelection * 0.1f, 0, 0, 0));

          Matrix4x4 modelViewProjection = viewer->projection() * viewer->viewTransform() * model * translationAlongLine * Matrix4x4::rotationY(toRadians(90)) * viewScale * Matrix4x4::scale(0.1f) * Matrix4x4::scale(Vector4(0.5f, 0.5f, 2.0f, 1.0f));
          effect_->setUniform(modelViewProjection, "ModelViewProj");
          effect_->setUniform(Color3::RED, "Color");

          effect_->commitBuffers();
          GraphicsInterface::drawVertexBuffer(Geometry::CONE_VERTEX_BUFFER, Geometry::CONE_VERTEX_COUNT, Geometry::CONE_VERTEX_FORMAT);
          effect_->endDraw();
        }

        // +y cone
        {
          effect_->beginDraw();

          Matrix4x4 translationAlongLine = Matrix4x4::translation(Vector4(0, 1 * distanceToSelection * 0.1f, 0, 0));

          Matrix4x4 modelViewProjection = viewer->projection() * viewer->viewTransform() * model * translationAlongLine * Matrix4x4::rotationX(toRadians(-90)) * viewScale * Matrix4x4::scale(0.1f) * Matrix4x4::scale(Vector4(0.5f, 0.5f, 2.0f, 1.0f));
          effect_->setUniform(modelViewProjection, "ModelViewProj");
          effect_->setUniform(Color3::GREEN, "Color");

          effect_->commitBuffers();
          GraphicsInterface::drawVertexBuffer(Geometry::CONE_VERTEX_BUFFER, Geometry::CONE_VERTEX_COUNT, Geometry::CONE_VERTEX_FORMAT);
          effect_->endDraw();
        }

        // +z cone
        {
          effect_->beginDraw();

          Matrix4x4 translationAlongLine = Matrix4x4::translation(Vector4(0, 0, 1 * distanceToSelection * 0.1f, 0));

          Matrix4x4 modelViewProjection = viewer->projection() * viewer->viewTransform() * model * translationAlongLine * viewScale * Matrix4x4::scale(0.1f) * Matrix4x4::scale(Vector4(0.5f, 0.5f, 2.0f, 1.0f));
          effect_->setUniform(modelViewProjection, "ModelViewProj");
          effect_->setUniform(Color3::BLUE, "Color");

          effect_->commitBuffers();
          GraphicsInterface::drawVertexBuffer(Geometry::CONE_VERTEX_BUFFER, Geometry::CONE_VERTEX_COUNT, Geometry::CONE_VERTEX_FORMAT);
          effect_->endDraw();
        }
      }*/

      GraphicsInterface::endPerformanceEvent();
    }
 // }
}