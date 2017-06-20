#if !defined(PG_WINDOW_MENU_H)
#define PG_WINDOW_MENU_H




#include "String.h"
using namespace PG::Core;

#include "BaseRenderer.h"
#include "Font.h"
using namespace PG::Engine;

#include "GUICore.h"
#include "Controler.h"
#include "UIElement.h"
#include "Panel.h"
#include "Button.h"

using namespace PG::Engine;
using namespace PG::GUI;

		class WindowMenu : public UIElement {
		protected:
			r32 menu_button_default_size = 16.f;
		private:
			Margin* Menu_Margin;
			Panel* Main_Panel;
			Button * Hide_Button;
			bool IsMovable;
			bool IsResizable;
		public:
			WindowMenu() {
				this->IsMovable = true;
				this->IsResizable = true;

				this->Menu_Margin = new Margin(5.f, 5.f, 32.f, 5.f);

				this->Main_Panel = new Panel();
				this->Main_Panel->SetPossition(v2(0.f, 0.f));
				this->Main_Panel->background_color = v3(0.3f, 0.3f, 0.3f);

				this->Hide_Button = new Button();
				this->Hide_Button->SetSize(v2(menu_button_default_size));
				this->Hide_Button->SetPossition(v2(0.f, 0.f));
				this->Hide_Button->AddListener(this);


				UIElement::AddChild(Main_Panel);
				UIElement::AddChild(Hide_Button);

			}
			~WindowMenu() {
				delete(Menu_Margin);
			}
			virtual void WindowMenu::Render(BaseRenderer *renderer) override {
				if (this->IsVisible == true) {

					if (this->State != UIState_Idle) {
						this->Opacity = 1.f;
					}
					else {
						this->Opacity = 0.7f;
					}
					renderer->ui_panel_Mesh->Render(v3(this->GetRelativePossition(), 0.f), this->Size, v4(v3(0.2f, 0.2f, 0.2f), this->GetRelativeOpacity()));
					UIElement::Render(renderer);
				}

			}
			virtual bool WindowMenu::Update(Controler *controler, double timeElapse, v3 *mouse_ui_possition) {
				bool isChildActive = UIElement::Update(controler, timeElapse, mouse_ui_possition);
				if (isChildActive == false) {
					switch (this->State) {
					case UIState_Hot:{
										 if (this->IsMovable == true && controler->IsPressed(PGMouse_Right) == true) {
											 this->State = UIState_Moving;
										 }
										 break; }
					case UIState_Moving:{
											this->Possition.x = this->Possition.x + controler->DeltaPossition.x;
											this->Possition.y = this->Possition.y + controler->DeltaPossition.y;
											if (controler->IsRelease(PGMouse_Right) == true || controler->GetKey(PGMouse_Right)->IsPress == false) {
												if (this->IsIntersection(mouse_ui_possition)) {
													this->State = UIState_Hot;
												}
												else {
													this->State = UIState_Idle;
												}
											}
											break; }
					}
				}
				return isChildActive;
			}
			void WindowMenu::SetSize(v2 size) override {
				UIElement::SetSize(size);

				//Align-other thing
				this->Main_Panel->SetSize(v2(size.x - this->Menu_Margin->Right - this->Menu_Margin->Left, size.y - this->Menu_Margin->Bottom - this->Menu_Margin->Top));
				this->Main_Panel->SetPossition(v2(this->Menu_Margin->Left, this->Menu_Margin->Top));

				this->Hide_Button->SetPossition(v2(size.x - menu_button_default_size - this->Menu_Margin->Right, this->Menu_Margin->Top / 2.f - menu_button_default_size / 2.f));
			}

			void WindowMenu::AddChild(UIElement* child_element) override {
				Main_Panel->AddChild(child_element);
			}
			virtual void WindowMenu::OnEvent(GUIEvent *event) {
				EventListener::OnEvent(event);
				if (event->sender == this->Hide_Button) {
					if (event->code == GUIEvent_Button_Release) {
						this->IsVisible = false;
						this->EmiteEvent(event);//Re-emit event for those 
					}
				}


			}
		};

#endif