#if !defined(PG_GAME_SCENE_H)
#define PG_GAME_SCENE_H

#include "stdafx.h"

#include "Core.h"
#include "BaseRenderer.h"
#include "Controler.h"
#include "Entity.h"

#include "String.h"
#include "EngineObjectList.h"
#include "MousePicker.h"
#include "Camera.h"


using namespace PG::Engine;
namespace PG {
	namespace Engine {
		class Scene : public EngineObject, BuildableObject {
		protected:
			Camera * scene_camera;
			m4 Projection_Matrice;
			virtual void Scene::HandleControler(Controler *controler) {

			}

			EngineObjectList<Entity>* Entities;
			MousePicker* Mouse_Picker; //Note(marc): <- Unmanaged resources
		private:
		public:
			bool ShouldUpdate;
			bool ShouldHandleControler;
			bool ShouldRender;
			Scene() :
				EngineObject() {
				this->scene_camera = nullptr;
				this->ShouldUpdate = true;
				this->ShouldRender = true;
				this->ShouldHandleControler = true;
				this->Entities = new EngineObjectList<Entity>(true);
			}
			virtual ~Scene() {
				delete(this->Entities);
				delete(this->scene_camera);
			}
			bool Scene::IsRenderable() {
				if (this->BuildableObject::IsLock() == true) return false;
				if (this->BuildableObject::IsBuild() == false) return false;
				if (this->ShouldRender == false) return false;
				return true;
			}
			bool Scene::IsUpdatable() {
				if (this->BuildableObject::IsLock() == true) return false;
				if (this->BuildableObject::IsBuild() == false) return false;
				if (this->ShouldUpdate == false) return false;
				return true;
			}
			virtual void Scene::Build(MousePicker* mouse_picker) {
				this->BuildableObject::StartBuilding();
				this->Mouse_Picker = mouse_picker;

				this->BuildableObject::EndBuilding();
			}
			virtual void Scene::Render(BaseRenderer *renderer) {
				renderer->SetWorldView(this->scene_camera->GetViewMatrice());
				renderer->SetWorldProjection(&this->Projection_Matrice);

			}
			virtual void Scene::Update(Controler *controler, double timeElapse) {
				if (controler != nullptr) {
					if (this->ShouldHandleControler == true) {
						this->HandleControler(controler);
					}
				}

			}

		};


	}
}
#endif