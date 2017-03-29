#if !defined(ENGINE_INSTANCE_H)
#define ENGINE_INSTANCE_H

#include "stdafx.h"

#include "PGCore.h"
#include "PGList.h"
#include "PGString.h"
using namespace PG::Core;

#include "PGBaseRenderer.h"
#include "PGGameWindow.h"
#include "PGBaseScene.h"
#include "AssetManager.h"
#include "PGUICanvas.h"
#include "PGEditorScene.h"
#include "PGMousePicker.h"

namespace PG {
	namespace Engine {
		class EngineInstance : public PGBuildableObject {
		protected:
			PGFont *Default_Engine_Font; //Note(Marc): Unmanaged ptr
			char fps_info_buffer[40];
			char frame_cpt_buffer[40];

			PGBaseScene* CurrentViewedScene;
			PGBaseObjList<PGBaseScene>* LoadedScenes;
			PGControler* Controlers;
			PGGameWindow* GameWindow;
			PGBaseRenderer* GameRenderer;
			AssetManager* Asset_Manager;

			PGMousePicker* MousePicker;


			virtual void EngineInstance::HandlerEvents() {
				if (glfwWindowShouldClose(this->GameWindow->Gl_Window) == 1) {
					this->ShouldGameClose = true;
				}

			}
			virtual void EngineInstance::HandleControler() {
				if (glfwGetKey(this->GameWindow->Gl_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
					this->ShouldGameClose = true;
				}

			}
			virtual void EngineInstance::Render() {
				if (this->CurrentViewedScene != nullptr) {
					if (this->CurrentViewedScene->IsRenderable() == true)
						this->CurrentViewedScene->Render(this->GameRenderer);
				}
			}
			virtual void EngineInstance::Update(double _TimeElapse) {
				this->HandleControler();
				this->HandlerEvents();
				if (this->CurrentViewedScene != nullptr) {
					if (this->CurrentViewedScene->IsUpdatable() == true) {
						this->CurrentViewedScene->Update(this->Controlers, _TimeElapse);
					}
				}
			}
		private:
			bool ShouldGameClose; //Note(Marc): Global loop end
			bool IsBuild;

		public:
			EngineInstance() {
				fps_info_buffer[0] = ENDSTR;
				frame_cpt_buffer[0] = ENDSTR;
				this->ShouldGameClose = false;
				this->IsBuild = false;
				this->CurrentViewedScene = nullptr;
				this->LoadedScenes = new PGBaseObjList<PGBaseScene>(true);
				this->Controlers = new PGControler();
				this->GameWindow = new PGGameWindow(false, 1024, 768);
				this->GameRenderer = new PGBaseRenderer();
				this->Asset_Manager = new AssetManager();
				this->MousePicker = new PGMousePicker(this->GameWindow);
			}
			virtual ~EngineInstance() {
				delete(this->LoadedScenes);
				delete(this->Controlers);
				delete(this->GameRenderer);
				delete(this->GameWindow);
				delete(this->Asset_Manager);
				delete(this->MousePicker);
			}
			void EngineInstance::Start() {
				unsigned int FrameRenderGlobalCount = 0;

				uint32 renderFctCallCpt = 0;
				uint32 updateFctCallCpt = 0;

				double generalFctTime = 0;


				double last_pass_time_stamp = glfwGetTime();
				double current_pass_time_stamp;

				double updateFctTimer = 0;
				double UpdateFrequency = PG_60HZT;
				double last_update_pass_stamp = 0;

				while (this->ShouldGameClose == false) {

					current_pass_time_stamp = glfwGetTime();
					double delta_time = (current_pass_time_stamp - last_pass_time_stamp);
					last_pass_time_stamp = current_pass_time_stamp;

					glfwPollEvents();


					updateFctTimer += delta_time;
					while (updateFctTimer >= UpdateFrequency) {
						double deltaTimeForUpdate = (glfwGetTime() - last_update_pass_stamp);
						last_update_pass_stamp = glfwGetTime();

						this->Controlers->Update(this->GameWindow);
						this->Update(deltaTimeForUpdate);

						updateFctCallCpt++;
						updateFctTimer -= UpdateFrequency;
					}


					this->Render();
					//Note(Marc): Render debug stuff here
					this->GameRenderer->RenderUIText(fps_info_buffer, v3(0.f, 0.f, 1.f), v4(0.3f, 0.5f, 0.2f, 1.f), 0.3f, this->Default_Engine_Font);

					renderFctCallCpt++;
					generalFctTime += delta_time;
					if (generalFctTime >= 1.f) {
						sprintf(fps_info_buffer, "FPS : %d UPS : %d\n", renderFctCallCpt, updateFctCallCpt);
						updateFctCallCpt = 0;
						renderFctCallCpt = 0;
						generalFctTime -= 1.f;
					}

					glfwSwapBuffers(this->GameWindow->Gl_Window);
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
					FrameRenderGlobalCount++;
				}
			}
			virtual void EngineInstance::Build() override {
				PGBuildableObject::StartBuilding();



				PGBuildableObject::EndBuilding();
			}
		};
	}


}

#endif