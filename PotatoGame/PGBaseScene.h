#if !defined(PG_GAME_SCENE_H)
#define PG_GAME_SCENE_H

#include "stdafx.h"

#include "PGCore.h"
#include "PGBaseRenderer.h"
#include "PGControler.h"
#include "PGEntity.h"

#include "PGString.h"
#include "PGBaseObjectList.h"
#include "PGMousePicker.h"
#include "Camera.h"

namespace PG {
	namespace Engine {
		class PGBaseScene : public PGBaseObject, PGBuildableObject {
		protected:
			Camera * scene_camera;
			m4 Projection_Matrice;
			virtual void PGBaseScene::HandleControler(PGControler *controler) {

			}

			PGBaseObjList<PGEntity>* Entities;
			PGMousePicker* MousePicker; //Note(marc): <- Unmanaged resources
		private:
		public:
			bool ShouldUpdate;
			bool ShouldHandleControler;
			bool ShouldRender;
			PGBaseScene() :
				PGBaseObject() {
				this->ShouldUpdate = true;
				this->ShouldRender = true;
				this->ShouldHandleControler = true;
				this->Entities = new PGBaseObjList<PGEntity>(true);
			}
			virtual ~PGBaseScene() {
				delete(this->Entities);
				delete(this->scene_camera);
			}
			bool PGBaseScene::IsRenderable() {
				if (this->PGBuildableObject::IsLock() == true) return false;
				if (this->PGBuildableObject::IsBuild() == false) return false;
				if (this->ShouldRender == false) return false;
				return true;
			}
			bool PGBaseScene::IsUpdatable() {
				if (this->PGBuildableObject::IsLock() == true) return false;
				if (this->PGBuildableObject::IsBuild() == false) return false;
				if (this->ShouldUpdate == false) return false;
				return true;
			}
			virtual void PGBaseScene::Build(PGMousePicker* mouse_picker) {
				this->PGBuildableObject::StartBuilding();
				this->MousePicker = mouse_picker;

				this->PGBuildableObject::EndBuilding();
			}
			virtual void PGBaseScene::Render(PGBaseRenderer *renderer) {
				renderer->SetWorldView(this->scene_camera->GetViewMatrice());
				renderer->SetWorldProjection(&this->Projection_Matrice);

			}
			virtual void PGBaseScene::Update(PGControler *controler, double timeElapse) {
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