#if !defined(PG_GAME_SCENE_H)
#define PG_GAME_SCENE_H

#include "stdafx.h"

#include "PGCore.h"
#include "PGBaseRenderer.h"
#include "PGControler.h"
#include "PGEntity.h"
#include "PGBaseEvent.h"
#include "PGString.h"
#include "PGBaseObjectList.h"
#include "PGMousePicker.h"
#include "PGBaseCamera.h"

namespace PGEngine {
	class PGBaseScene : public PGBaseObject, PGBuildableObject {
		protected:
			PGBaseCamera * Camera;
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
				PGBaseObject(){
					this->ShouldUpdate = true;
					this->ShouldRender = true;
					this->ShouldHandleControler = true;
					this->Entities = new PGBaseObjList<PGEntity>(true);
			}
			~PGBaseScene() {
				delete(this->Entities);
				delete(this->Camera);
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
				renderer->SetWorldView(this->Camera->GetViewMatrice());	
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
#endif