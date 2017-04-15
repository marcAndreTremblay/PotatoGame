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
		class TextBox : public UIElement{
			char Text[100];
			char*cursor;
		public:
			TextBox() :  UIElement() {
				cursor = &Text[0];
				*cursor = ENDSTR;
			}
			~TextBox() {
				
			}
			void TextBox::Render(BaseRenderer *renderer) {
				renderer->ui_panel_Mesh->Render(v3(this->GetRelativePossition(),this->GetRelativeZ()), this->Size, v4(1.f));

			}
			bool TextBox::Update(Controler *controler, double timeElapse, v3* mouse_ui_possition) {
				bool isChildActive = UIElement::Update(controler, timeElapse, mouse_ui_possition);
				if (isChildActive == false) {
					switch (this->State) {
						case UIState_Hot:{
								if (controler->IsPressed(PGMouse_Right) == true) {
									this->State = UIState_Editing;	 
								}
									
								break; }
						case UIState_Editing:{
												 if (controler->IsPressed(PGMouse_Left) == true) {
													 this->State = UIState_Idle;
												 }
												 for (ListNode<ControlerKey> *c_node = controler->Keyboard_Keys->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
													 ControlerKey * current_key = c_node->GetData();
													 if (current_key->KeyCode >= 65 && current_key->KeyCode <= 90) {
														 if (current_key->IsPress == false && current_key->WasPress == true) {
															 *cursor = (char)current_key->KeyCode;
															 cursor++;
															 *cursor = ENDSTR;
															 printf("%s\n", Text);
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