#if !defined(PG_GAME_SCENE_H)
#define PG_GAME_SCENE_H

#include "stdafx.h"

#include "PGCore.h"
#include "PGBaseRenderer.h"
#include "PGControler.h"
#include "PGSceneEntity.h"
#include "PGBaseEvent.h"
#include "PGString.h"
#include "PGBaseObjectList.h"
#include "PGMousePicker.h"
#include "PGBaseCamera.h"

namespace PGEngine {
	enum SceneParameters {
		GeneralWorkGroup = 1,
		SceneWorkGroup = 2,
		
	};
	class PGBaseScene : public PGBaseObject, PGBuildableObject {
		protected:
			PGBaseCamera * Camera;
			m4 Projection_Matrice; 
			virtual void PGBaseScene::HandleControler(PGControler *controler) {
				
			}
			virtual void PGBaseScene::HandlerEvents(PGEventWorkGroup *work_group) {
			
			}
			PGEventWorkGroup* WorkGroup; //Note(marc): <- Unmanaged resources
			PGBaseObjList<PGSceneEntity>* Entities;
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
					this->Entities = new PGBaseObjList<PGSceneEntity>();
			}
			~PGBaseScene() {
				delete(this->Entities);
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
			virtual void PGBaseScene::Build(PGEventWorkGroup* targetWorkGroup,PGMousePicker* mouse_picker) {
				this->PGBuildableObject::StartBuilding();
				this->WorkGroup = targetWorkGroup;
				this->MousePicker = mouse_picker;

				this->PGBuildableObject::EndBuilding();
			}
			virtual void PGBaseScene::Render(PGBaseRenderer *renderer) {		
				renderer->SetWorldView(&this->Camera->GetViewMatrice());	
				renderer->SetWorldProjection(&this->Projection_Matrice);

			}
			virtual void PGBaseScene::Update(PGControler *controler, double timeElapse) {
				if (controler != nullptr) {
					if (this->ShouldHandleControler == true) {
						this->HandleControler(controler);
					}
				}
				this->HandlerEvents(WorkGroup);
			}

	};


}
#endif