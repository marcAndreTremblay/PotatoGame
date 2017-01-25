#if !defined(PG_UI_CANVAS_H)
#define PG_UI_CANVAS_H

#include "PGCore.h"
#include "PGLinkedList.h"
using namespace PGCore;


#include "PGBaseObject.h"
#include "PGBaseObjectList.h"
#include "PGBuildableObject.h"
#include "PGControler.h"
#include "PGBaseRenderer.h"
#include "PGBaseEvent.h"
#include "PGTexture.h"
#include "PGMousePicker.h"
using namespace PGEngine;

#include "PGUIBaseElement.h"


class PGUICanvas : public PGBuildableObject {
	protected:	
		unsigned int PGUICanvas::GetNextFreeId() {
			this->NextElementId += 1;
		return NextElementId;
	}

	private:
		unsigned int NextElementId;
		m4 ortho_Projection;
		PGMousePicker* MousePicker;
		PGGameWindow* GameWindow;
		PGEventWorkGroup* work_group; //Un-managed resources
		PGBaseObjList<PGBaseUIElement>* element_list;
	public:
		PGUICanvas() {
			this->NextElementId = 1;
			this->element_list = new PGBaseObjList<PGBaseUIElement>();
			
		}
		~PGUICanvas() {
			delete(this->element_list);
		}
		virtual void PGUICanvas::Build(PGGameWindow* game_window,PGMousePicker* _mouse_picker, PGAssetManager* asset_manager) {
			this->StartBuilding();
				this->MousePicker = _mouse_picker;
				this->GameWindow = game_window;


				this->ortho_Projection = glm::ortho(0.0f, static_cast<r32>(this->GameWindow->GetWidth()), static_cast<r32>(this->GameWindow->GetHeight()), 0.0f, -1.0f, 1.0f);

				PGUIMenuWindow *menu_window = new PGUIMenuWindow();
					menu_window->SetSize(v2(300.f, 500.f));
					menu_window->SetPossition(v2(10.f, 10.f));
					menu_window->SetMenuTitle("Test title\n", asset_manager->SeachForFont("Roboto-Light\n"), v3(1.f, 0.2f, 0.5f));

						PGUIImageBox* picture_1 = new PGUIImageBox();
								picture_1->Set_Id(this->GetNextFreeId());
								picture_1->SetSize(v2(32.f, 32.f));
								picture_1->SetPossition(v2(10.f, 10.f));
								picture_1->Image = asset_manager->SeachForTexture("UV_Template\n");
							menu_window->AddChild(picture_1);

						PGUIImageBox* picture_2 = new PGUIImageBox();
								picture_2->Set_Id(this->GetNextFreeId());
								picture_2->SetSize(v2(32.f, 32.f));
								picture_2->SetPossition(v2(10.f, 84.f));
								picture_2->Image = asset_manager->SeachForTexture("Asteroid_1\n");
							menu_window->AddChild(picture_2);

						PGUIImageBox* picture_3 = new PGUIImageBox();
								picture_3->Set_Id(this->GetNextFreeId());
								picture_3->SetSize(v2(32.f, 32.f));
								picture_3->SetPossition(v2(10.f, 148.f));
								picture_3->Image = asset_manager->SeachForTexture("SolarPanel\n");
							menu_window->AddChild(picture_3);
					
						PGUIButton *child_button_1 = new PGUIButton();
								child_button_1->Set_Id(this->GetNextFreeId());
								child_button_1->SetSize(v2(200.f, 64.f));
								child_button_1->SetPossition(v2(60.f, 84));
								child_button_1->SetText("lButton 1\n");
								child_button_1->SetFont(asset_manager->SeachForFont("Hammersmith_Regular\n"));
							menu_window->AddChild(child_button_1);
					
						PGUIButton *child_button_2 = new PGUIButton();
								child_button_2->Set_Id(this->GetNextFreeId());
								child_button_2->SetSize(v2(200.f, 64.f));
								child_button_2->SetPossition(v2(60.f, 10.f));
								child_button_2->SetText("aHome\n");
								child_button_2->SetFont(asset_manager->SeachForFont("Roboto-Light\n"));
							menu_window->AddChild(child_button_2);

						PGUILabel *label_1 = new PGUILabel();
								label_1->Set_Id(this->GetNextFreeId());
								label_1->SetSize(v2(100.f, 64.f));
								label_1->SetPossition(v2(60.f, 150.f));
								label_1->SetText("Label\n");
								label_1->SetFont(asset_manager->SeachForFont("Roboto_Bold\n"));
							menu_window->AddChild(label_1);

				
				this->element_list->Add(menu_window);
			this->EndBuilding();
		}
		void PGUICanvas::Render(PGBaseRenderer *renderer) {
			if (this->IsLock() == false && this->IsBuild() == true) {

				this->ortho_Projection = glm::ortho(0.0f, static_cast<r32>(this->GameWindow->GetWidth()), static_cast<r32>(this->GameWindow->GetHeight()), 0.0f, -1.0f, 1.0f);
				renderer->SetUIProjection(&ortho_Projection);

				for (PGListNode<PGBaseUIElement> *c_node = element_list->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
					PGBaseUIElement* current_ui_element = c_node->GetData();
					current_ui_element->Render(renderer);	
				}
			}
		}
		void PGUICanvas::Update(PGControler *controler, double timeElapse) {
			v3 mouse_ui_space = this->MousePicker->TranformWindowStoUIS(controler,&this->ortho_Projection);
			for (PGListNode<PGBaseUIElement> *c_node = element_list->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
				PGBaseUIElement* current_ui_element = c_node->GetData();
					current_ui_element->Update(controler, timeElapse, &mouse_ui_space);
			}
		}
};

#endif 