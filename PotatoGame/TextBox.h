#if !defined(PG_TEXTBOX_H)
#define PG_TEXTBOX_H




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
		class TextBox : public UIElement {
			char Text[100];
			char*cursor;
			Font* _font;
			r32 text_scale;
			v3 text_color;
		public:
			TextBox(Font* font = nullptr) : UIElement() {
				_font = font;
				cursor = &Text[0];
				*cursor = ENDSTR;
				text_scale = 1.f;
				text_color = v3(0.f);
			}
			~TextBox() {

			}
			virtual bool TextBox::IsActif() override {
				if (this->State == UIState_Hot) return true;
				if (this->State == UIState_Editing) return true;
				return false;
			}
			void TextBox::Render(BaseRenderer *renderer) {
				if (this->State == UIState_Hot) {
					renderer->ui_panel_Mesh->Render(v3(this->GetRelativePossition(), this->GetRelativeZ()), this->Size, v4(0.3f, 0.3f, 0.9f, this->GetRelativeOpacity()));
				}
				if (this->State == UIState_Editing) {
					renderer->ui_panel_Mesh->Render(v3(this->GetRelativePossition(), this->GetRelativeZ()), this->Size, v4(0.3f, 0.6f, 0.3f, this->GetRelativeOpacity()));
				}
				if (this->State == UIState_Idle) {
					renderer->ui_panel_Mesh->Render(v3(this->GetRelativePossition(), this->GetRelativeZ()), this->Size, v4(0.7f, 0.3f, 0.1f, this->GetRelativeOpacity()));
				}

				if (this->IsVisible == true && this->_font != nullptr) {
					v2 box = v2();
					_font->GetFontBondingBox(&Text[0], text_scale, &box);
					renderer->RenderUIText(&Text[0], v3(this->GetRelativePossition(), this->GetRelativeZ() + 0.1f), v4(this->text_color, this->GetRelativeOpacity()), this->text_scale, this->_font);
				}
			}
			bool TextBox::Update(Controler *controler, double timeElapse, v3* mouse_ui_possition) {
				bool isChildActive = UIElement::Update(controler, timeElapse, mouse_ui_possition);
				if (isChildActive == false) {
					switch (this->State) {
					case UIState_Hot: {
						if (controler->IsPressed(PGMouse_Right) == true) {
							this->State = UIState_Editing;
						}

						break; }
					case UIState_Editing: {
						if (controler->IsPressed(PGMouse_Left) == true) {
							this->State = UIState_Idle;
							break;
						}
						if (controler->IsRelease(PGBackSpace) == true) {
							cursor--;
							*cursor = ENDSTR;

							break;
						}
						else if (controler->IsRelease(PGSpace) == true) {
							*cursor = (char)PGSpace;
							cursor++;
							*cursor = ENDSTR;

							break;
						}
						for (ListNode<ControlerKey> *c_node = controler->Keyboard_Keys->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
							ControlerKey * current_key = c_node->GetData();
							if (current_key->KeyCode >= 65 && current_key->KeyCode <= 90) {
								if (current_key->IsPress == false && current_key->WasPress == true) {
									*cursor = (char)current_key->KeyCode;
									cursor++;
									*cursor = ENDSTR;

								}
							}
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