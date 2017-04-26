#if !defined(PG_USER_CONTROLER_H)
#define PG_USER_CONTROLER_H

#include "stdafx.h"

#include "Core.h"
#include "GameWindow.h"
#include "String.h"
#include "List.h"		

using namespace PG::Core;
namespace PG {
	namespace Engine {
		class ControlerKey {
		public:
			int  KeyCode;
			bool IsPress;
			bool WasPress;
			Str *Ref_Name;

			ControlerKey(int _KeyCode, char* _Ref_Name = nullptr) {
				this->WasPress = false;
				this->IsPress = false;
				this->KeyCode = _KeyCode;
				if (_Ref_Name != nullptr) {
					this->Ref_Name = new Str(_Ref_Name);
				}

			}
			~ControlerKey() {
				delete(this->Ref_Name);
			}
		};
		enum PGMouseKey {
			PGMouse_Left = GLFW_MOUSE_BUTTON_LEFT,
			PGMouse_Center = GLFW_MOUSE_BUTTON_MIDDLE,
			PGMouse_Right = GLFW_MOUSE_BUTTON_RIGHT
		};
		enum PGKey {
			PGKey_1 = GLFW_KEY_1,
			PGKey_2 = GLFW_KEY_2,
			PGKey_3 = GLFW_KEY_3,
			PGKey_4 = GLFW_KEY_4,
			PGKey_5 = GLFW_KEY_5,
			PGKey_6 = GLFW_KEY_6,
			PGKey_7 = GLFW_KEY_7,
			PGKey_Space = GLFW_KEY_SPACE,
			PGKey_Up = GLFW_KEY_UP,
			PGKey_Down = GLFW_KEY_DOWN,
			PGKey_Left = GLFW_KEY_LEFT,
			PGKey_Right = GLFW_KEY_RIGHT,
			PGKey_A = GLFW_KEY_A,
			PGKey_D = GLFW_KEY_D,
			PGKey_W = GLFW_KEY_W,
			PGKey_S = GLFW_KEY_S,
			PGKey_Q = GLFW_KEY_Q,
			PGKey_E = GLFW_KEY_E,
			PGKey_F = GLFW_KEY_F,
			PGKey_R = GLFW_KEY_R,
			PGKey_F1 = GLFW_KEY_F1,
			PGKey_F2 = GLFW_KEY_F2,
			PGKey_F3 = GLFW_KEY_F3,
			PGKey_F4 = GLFW_KEY_F4,
			PGKey_Z = GLFW_KEY_Z,
			PGKey_C = GLFW_KEY_C,
			PGSpace = GLFW_KEY_SPACE,
			PGBackSpace = GLFW_KEY_BACKSPACE,
			PGKey_Page_Down = GLFW_KEY_PAGE_DOWN,
			PGKey_Page_Up = GLFW_KEY_PAGE_UP,
			PGKey_Left_Ctrl = GLFW_KEY_LEFT_CONTROL,
			PGKey_Right_Ctrl = GLFW_KEY_RIGHT_CONTROL
		};

		class Controler {
		protected:
		private:
			List<ControlerKey>* Mouse_Keys;
			void Controler::AddMouseKey(PGMouseKey new_key_id, char* _Ref_Name = nullptr) {
				Mouse_Keys->Add(new ControlerKey(new_key_id, _Ref_Name));
			}
			void Controler::AddKeyboardKey(PGKey new_key_id, char* _Ref_Name = nullptr) {
				Keyboard_Keys->Add(new ControlerKey(new_key_id, _Ref_Name));
			}
		public:
			List<ControlerKey>* Keyboard_Keys;
			double xpos, ypos;
			v2 DeltaPossition;
			Controler() {

				this->Mouse_Keys = new List<ControlerKey>();
				this->AddMouseKey(PGMouse_Left, "Space bar");
				this->AddMouseKey(PGMouse_Center, "Space bar");
				this->AddMouseKey(PGMouse_Right, "Space bar");

				this->Keyboard_Keys = new List<ControlerKey>();
				DeltaPossition = {};
				this->AddKeyboardKey(PGKey_Space, "Space bar");
				this->AddKeyboardKey(PGKey_Up, "Up_Key");
				this->AddKeyboardKey(PGKey_Down, "Down_Key");
				this->AddKeyboardKey(PGKey_Left, "Left_Key");
				this->AddKeyboardKey(PGKey_Right, "Right_Key");


				//Add all letter
				for (int i = 65; i <= 90; i++) {
					this->AddKeyboardKey((PGKey)i);
				}
				this->AddKeyboardKey(PGBackSpace);
				this->AddKeyboardKey(PGSpace);
				this->AddKeyboardKey(PGKey_1, "1_Key");
				this->AddKeyboardKey(PGKey_2, "2_Key");
				this->AddKeyboardKey(PGKey_3, "3_Key");
				this->AddKeyboardKey(PGKey_4, "4_Key");
				this->AddKeyboardKey(PGKey_5, "5_Key");
				this->AddKeyboardKey(PGKey_6, "6_Key");
				this->AddKeyboardKey(PGKey_7, "7_Key");

				this->AddKeyboardKey(PGKey_F1, "F1_Key");
				this->AddKeyboardKey(PGKey_F2, "F2_Key");
				this->AddKeyboardKey(PGKey_F3, "F3_Key");
				this->AddKeyboardKey(PGKey_F4, "F4_Key");
				this->AddKeyboardKey(PGKey_Page_Down, "Down_Key");
				this->AddKeyboardKey(PGKey_Page_Up, "Up_Key");
				this->AddKeyboardKey(PGKey_Left_Ctrl, "Ctrl_Left");
				this->AddKeyboardKey(PGKey_Right_Ctrl, "Ctrl_Right");


			}
			~Controler() {
				delete(this->Keyboard_Keys);
			}
			ControlerKey* Controler::GetKey(PGKey key) {
				for (ListNode<ControlerKey> *c_node = Keyboard_Keys->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
					ControlerKey * current_key = c_node->GetData();
					if (current_key->KeyCode == key) {
						return current_key;
					}
				}
				return nullptr;
			}
			ControlerKey* Controler::GetKey(PGMouseKey key) {
				for (ListNode<ControlerKey> *c_node = Mouse_Keys->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
					ControlerKey * current_key = c_node->GetData();
					if (current_key->KeyCode == key) {
						return current_key;
					}
				}
				return nullptr;
			}

			//Note(Marc) : This function must be call every game update
			void Controler::Update(GameWindow* _GameWindow) {


				v2 last_possition = v2(this->xpos, this->ypos);
				glfwGetCursorPos(_GameWindow->Gl_Window, &this->xpos, &this->ypos);
				v2 current_possition = v2(this->xpos, this->ypos);
				DeltaPossition = (current_possition - last_possition);

				for (ListNode<ControlerKey> *c_node = Mouse_Keys->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
					ControlerKey* current_key = c_node->GetData();
					current_key->WasPress = current_key->IsPress;
					if (glfwGetMouseButton(_GameWindow->Gl_Window, current_key->KeyCode) == GLFW_PRESS) {
						current_key->IsPress = true;
					}
					else {
						current_key->IsPress = false;
					}
				}

				for (ListNode<ControlerKey> *c_node = Keyboard_Keys->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
					ControlerKey* current_key = c_node->GetData();
					current_key->WasPress = current_key->IsPress;
					if (glfwGetKey(_GameWindow->Gl_Window, current_key->KeyCode) == GLFW_PRESS) {
						current_key->IsPress = true;
					}
					else {
						current_key->IsPress = false;
					}
				}



			}
			bool Controler::IsRelease(PGKey key) {
				for (ListNode<ControlerKey> *c_node = Keyboard_Keys->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
					ControlerKey * current_key = c_node->GetData();
					if (current_key->KeyCode == key) {
						if (current_key->IsPress == false && current_key->WasPress == true) {
							return true;
						}
						else {
							return false;
						}
					}
				}
				return  false;
			}
			bool Controler::IsRelease(PGMouseKey key) {
				for (ListNode<ControlerKey> *c_node = Mouse_Keys->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
					ControlerKey * current_key = c_node->GetData();
					if (current_key->KeyCode == key) {
						if (current_key->IsPress == false && current_key->WasPress == true) {
							return true;
						}
						else {
							return false;
						}
					}
				}
				return  false;
			}
			bool Controler::IsPressed(PGKey key) {
				for (ListNode<ControlerKey> *c_node = Keyboard_Keys->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
					ControlerKey * current_key = c_node->GetData();
					if (current_key->KeyCode == key) {
						if (current_key->IsPress == true && current_key->WasPress == false) {
							return true;
						}
						else {
							return false;
						}
					}
				}
				return  false;
			}
			bool Controler::IsPressed(PGMouseKey key) {
				for (ListNode<ControlerKey> *c_node = Mouse_Keys->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
					ControlerKey * current_key = c_node->GetData();
					if (current_key->KeyCode == key) {
						if (current_key->IsPress == true && current_key->WasPress == false) {
							return true;
						}
						else {
							return false;
						}
					}
				}
				return  false;
			}


		};


	}
}
#endif