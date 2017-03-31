#if !defined(PG_BUTTON_H)
#define PG_BUTTON_H

#include "String.h"
using namespace PG::Core;

#include "BaseRenderer.h"
#include "Font.h"
using namespace PG::Engine;

#include "GUICore.h"
#include "Controler.h"
#include "UIElement.h"

using namespace PG::Engine;
namespace PG {
	namespace GUI {
		class Button :public UIElement {
		protected:
		private:
			Str* Text;
			Font* Font; //Un-managed resource
		public:
			v3 Text_color;
			r32 Text_size;
			void Button::SetText(char* text) {
				if (this->Text != nullptr) {
					delete(this->Text);
				}
				this->Text = new Str(text);
			}
			void Button::SetFont(PG::Engine::Font* font) {
				this->Font = font;
			}

			Button() {

				this->Text_color = v3(0.f);
				this->Text_size = 1.f;
				this->Text = nullptr;
				this->Font = nullptr;
			}
			~Button() {

			}
			virtual bool Button::IsActif() override {
				if (this->State != UIState_Idle) return true;
				return false;
			}
			virtual void Button::Render(BaseRenderer *renderer) {
				if (this->IsVisible == true) {
					if (this->State == UIState_Idle) {
						renderer->ui_panel_Mesh->Render(v3(this->GetRelativePossition(), this->GetRelativeZ()), this->Size, v4(1.f, 0.4f, 0.2f, this->GetRelativeOpacity()));
					}
					if (this->State == UIState_Hot) {
						renderer->ui_panel_Mesh->Render(v3(this->GetRelativePossition(), this->GetRelativeZ()), this->Size, v4(0.1f, 1.f, 0.3f, 1.0f));
					}
					if (this->State == UIState_Left_Press) {
						renderer->ui_panel_Mesh->Render(v3(this->GetRelativePossition(), this->GetRelativeZ()), this->Size, v4(1.f, 0.f, 1.f, 1.0f));
					}
					if (this->State == UIState_Right_Press) {
						renderer->ui_panel_Mesh->Render(v3(this->GetRelativePossition(), this->GetRelativeZ()), this->Size, v4(1.f, 1.f, 0.f, 1.f));
					}
					if (Text != nullptr && Font != nullptr) {
						renderer->RenderUIText(this->Text->CharAt(), v3(this->GetRelativePossition(), this->GetRelativeZ()) + v3(0.f, 0.f, 0.1f), v4(Text_color, this->GetRelativeOpacity()), this->Text_size, this->Font);
					}
				}
				UIElement::Render(renderer);
			}
			virtual bool Button::Update(Controler *controler, double timeElapse, v3* mouse_ui_possition) {
				bool isChildActive = UIElement::Update(controler, timeElapse, mouse_ui_possition);
				if (isChildActive == false) {
					switch (this->State) {
					case UIState_Hot:{
										 if (controler->IsPressed(PGMouse_Left) == true) {
											 this->State = UIState_Left_Press;
											 this->EmiteEvent(new GUIEvent(this, GUIEvent_Button_Press));
										 }
										 if (controler->IsPressed(PGMouse_Right) == true) {
											 this->State = UIState_Right_Press;
											 this->EmiteEvent(new GUIEvent(this, GUIEvent_Button_Press));
										 }
										 break; }
					case UIState_Left_Press:{
												if (controler->IsRelease(PGMouse_Left) == true) {
													if (this->IsIntersection(mouse_ui_possition) == true) {
														this->State = UIState_Hot;
													}
													else {
														this->State = UIState_Idle;
													}
													this->EmiteEvent(new GUIEvent(this, GUIEvent_Button_Release));
												}
												break; }
					case UIState_Right_Press:{
												 if (controler->IsRelease(PGMouse_Right) == true) {
													 if (this->IsIntersection(mouse_ui_possition) == true) {
														 this->State = UIState_Hot;
													 }
													 else {
														 this->State = UIState_Idle;
													 }
													 this->EmiteEvent(new GUIEvent(this, GUIEvent_Button_Release));
												 }
												 break; }

					}

				}
				return isChildActive;
			}
		};
	}
}
#endif