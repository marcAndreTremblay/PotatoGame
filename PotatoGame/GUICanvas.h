#if !defined(PG_UI_CANVAS_H)
#define PG_UI_CANVAS_H




#include "Core.h"
#include "List.h"
using namespace PG::Core;

#include "BaseRenderer.h"	
#include "BuildableObject.h"
#include "Controler.h"
#include "EngineObject.h"
#include "EngineObjectList.h"
#include "MousePicker.h"
#include "Texture.h"
using namespace PG::Engine;

#include "UIElement.h"
#include "DropDownMenu.h"
#include "TreeSelectorMenu.h"
#include "Label.h"
#include "Button.h"
#include "ImageBox.h"
#include "WindowMenu.h"
#include "TextBox.h"

namespace PG {
	namespace GUI {
		class GUICanvas : public BuildableObject {
		protected:
			unsigned int GUICanvas::GetNextFreeId() {
				this->NextElementId += 1;
				return NextElementId;
			}
		private:
			unsigned int NextElementId;
			MousePicker* Mouse_Picker;
			GameWindow* Game_Window;
			EngineObjectList<UIElement>* Element_list;
		public:
			GUICanvas() {
				this->NextElementId = 1;
				this->Element_list = new EngineObjectList<UIElement>(true);

			}
			~GUICanvas() {
				delete(this->Element_list);
			}
			virtual void GUICanvas::Build(GameWindow* game_window, MousePicker* _mouse_picker, AssetManager* asset_manager) {
				this->StartBuilding();
				this->Mouse_Picker = _mouse_picker;
				this->Game_Window = game_window;


				WindowMenu *menu_window = new WindowMenu();
				menu_window->SetSize(v2(300.f, 900.f));
				menu_window->SetPossition(v2(200.f, 10.f));

				ImageBox* picture_1 = new ImageBox();
				picture_1->Set_Id(this->GetNextFreeId());
				picture_1->SetSize(v2(32.f, 32.f));
				picture_1->SetPossition(v2(10.f, 10.f));
				picture_1->Image = asset_manager->SeachForTexture("UV_Template");
				menu_window->AddChild(picture_1);

				ImageBox* picture_2 = new ImageBox();
				picture_2->Set_Id(this->GetNextFreeId());
				picture_2->SetSize(v2(32.f, 32.f));
				picture_2->SetPossition(v2(10.f, 84.f));
				picture_2->Image = asset_manager->SeachForTexture("Asteroid_1");
				menu_window->AddChild(picture_2);

				ImageBox* picture_3 = new ImageBox();
				picture_3->Set_Id(this->GetNextFreeId());
				picture_3->SetSize(v2(32.f, 32.f));
				picture_3->SetPossition(v2(10.f, 148.f));
				picture_3->Image = asset_manager->SeachForTexture("SolarPanel");
				menu_window->AddChild(picture_3);

				TextBox *text_box_1 = new TextBox(asset_manager->SeachForFont("Hammersmith_Regular"));
				text_box_1->Set_Id(this->GetNextFreeId());
				text_box_1->SetSize(v2(200.f, 32.f));
				text_box_1->SetPossition(v2(5.f, 300));
				menu_window->AddChild(text_box_1);


				TextBox *text_box_2 = new TextBox(asset_manager->SeachForFont("Hammersmith_Regular"));
				text_box_2->Set_Id(this->GetNextFreeId());
				text_box_2->SetSize(v2(200.f, 32.f));
				text_box_2->SetPossition(v2(5.f, 334.f));
				menu_window->AddChild(text_box_2);

				Button *child_button_2 = new Button();
				child_button_2->Set_Name("Best Button");
				child_button_2->Set_Id(this->GetNextFreeId());
				child_button_2->SetSize(v2(200.f, 64.f));
				child_button_2->SetPossition(v2(60.f, 10.f));
				child_button_2->SetText("aHome");
				child_button_2->SetFont(asset_manager->SeachForFont("Roboto-Light"));
				menu_window->AddChild(child_button_2);

				Label *label_1 = new Label(new Str("Select level"), asset_manager->SeachForFont("Roboto_Bold"));
				label_1->Set_Id(this->GetNextFreeId());
				label_1->SetSize(v2(100.f, 64.f));
				label_1->SetPossition(v2(60.f, 150.f));
				label_1->text_scale = 0.5;
				menu_window->AddChild(label_1);



				DropDownMenu* select_view_test = new DropDownMenu(asset_manager->SeachForFont("Hammersmith_Regular"));
				select_view_test->SetSize(v2(200, 30));
				select_view_test->SetPossition(v2(0.f, 200.f));
				menu_window->AddChild(select_view_test);

				TreeSelectorMenu* tree_list_test = new TreeSelectorMenu(asset_manager->SeachForFont("Hammersmith_Regular"));
				tree_list_test->SetSize(v2(240, 300));
				tree_list_test->SetPossition(v2(0.f, 400.f));
				menu_window->AddChild(tree_list_test);

				this->Element_list->Add(menu_window);
				this->EndBuilding();
			}
			void GUICanvas::Render(BaseRenderer *renderer) {
				if (this->IsLock() == false && this->IsBuild() == true) {

					renderer->SetUIProjection(this->Game_Window->GetOrtho());

					for (ListNode<UIElement> *c_node = Element_list->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
						UIElement* current_ui_element = c_node->GetData();
						current_ui_element->Render(renderer);
					}
				}
			}
			bool GUICanvas::Update(Controler *controler, double timeElapse) {
				bool IsActif = false;
				v3 mouse_ui_space = this->Mouse_Picker->TranformWindowStoUIS(controler, this->Game_Window->GetOrtho());
				for (ListNode<UIElement> *c_node = Element_list->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {

					UIElement* current_ui_element = c_node->GetData();
					IsActif = current_ui_element->Update(controler, timeElapse, &mouse_ui_space);
					if (IsActif == false) {
						IsActif = current_ui_element->IsActif();
					}
				}
				return IsActif;
			}
		};
	}
}
#endif 