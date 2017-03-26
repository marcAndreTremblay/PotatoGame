#if !defined(PG_USER_CONTROLER_H)
#define PG_USER_CONTROLER_H

#include "stdafx.h"

#include "PGCore.h"
#include "PGGameWindow.h"
#include "PGString.h"
#include "PGList.h"		

using namespace PGCore;

class PGControlerKey
{
public:
	int  KeyCode;
	bool IsPress;
	bool WasPress;
	PGString *Ref_Name;

	PGControlerKey(int _KeyCode, char* _Ref_Name = nullptr)
	{
		this->WasPress = false;
		this->IsPress = false;
		this->KeyCode = _KeyCode;
		if (_Ref_Name != nullptr)
		{
			this->Ref_Name = new PGString(_Ref_Name);
		}
		
	}	
	~PGControlerKey()
	{
		delete(this->Ref_Name);
	}
};
enum PGMouseKey {
	PGMouse_Left = GLFW_MOUSE_BUTTON_LEFT,
	PGMouse_Center = GLFW_MOUSE_BUTTON_MIDDLE,
	PGMouse_Right = GLFW_MOUSE_BUTTON_RIGHT
};
enum PGKey
{ 
	PGKey_1 = GLFW_KEY_1,
	PGKey_2 = GLFW_KEY_2,
	PGKey_3 = GLFW_KEY_3,
	PGKey_4 = GLFW_KEY_4,
	PGKey_5 = GLFW_KEY_5,
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
	PGKey_F1 = GLFW_KEY_F1,
	PGKey_F2 = GLFW_KEY_F2,
	PGKey_F3 = GLFW_KEY_F3,
	PGKey_F4 = GLFW_KEY_F4,
	PGKey_Z = GLFW_KEY_Z,
	PGKey_C = GLFW_KEY_C,
	PGKey_Page_Down = GLFW_KEY_PAGE_DOWN,
	PGKey_Page_Up = GLFW_KEY_PAGE_UP,
	PGKey_Left_Ctrl = GLFW_KEY_LEFT_CONTROL,
	PGKey_Right_Ctrl = GLFW_KEY_RIGHT_CONTROL
};

class PGControler
{
protected:
private:
	PGList<PGControlerKey>* Keyboard_Keys;
	PGList<PGControlerKey>* Mouse_Keys;
	void PGControler::AddMouseKey(PGMouseKey new_key_id, char* _Ref_Name = nullptr) {
		Mouse_Keys->Add(new PGControlerKey(new_key_id, _Ref_Name));
	}
	void PGControler::AddKeyboardKey(PGKey new_key_id, char* _Ref_Name = nullptr){
		Keyboard_Keys->Add(new PGControlerKey(new_key_id, _Ref_Name));
	}
public:
	double xpos, ypos;
	v2 DeltaPossition;
	PGControler()
	{
		this->Mouse_Keys = new PGList<PGControlerKey>();
			this->AddMouseKey(PGMouse_Left, "Space bar\n");
			this->AddMouseKey(PGMouse_Center, "Space bar\n");
			this->AddMouseKey(PGMouse_Right, "Space bar\n");
		
		this->Keyboard_Keys = new PGList<PGControlerKey>();
		DeltaPossition = {};
			this->AddKeyboardKey(PGKey_Space, "Space bar\n");
			this->AddKeyboardKey(PGKey_Up, "Up_Key\n");
			this->AddKeyboardKey(PGKey_Down, "Down_Key\n");
			this->AddKeyboardKey(PGKey_Left, "Left_Key\n");
			this->AddKeyboardKey(PGKey_Right, "Right_Key\n");
			this->AddKeyboardKey(PGKey_1, "1_Key\n");
			this->AddKeyboardKey(PGKey_2, "2_Key\n");
			this->AddKeyboardKey(PGKey_3, "3_Key\n");
			this->AddKeyboardKey(PGKey_4, "4_Key\n");
			this->AddKeyboardKey(PGKey_5, "4_Key\n");
			this->AddKeyboardKey(PGKey_A, "A_Key\n");
			this->AddKeyboardKey(PGKey_D, "D_Key\n");
			this->AddKeyboardKey(PGKey_W, "W_Key\n");
			this->AddKeyboardKey(PGKey_S, "S_Key\n");
			this->AddKeyboardKey(PGKey_Q, "Q_Key\n");
			this->AddKeyboardKey(PGKey_E, "E_Key\n");
			this->AddKeyboardKey(PGKey_C, "C_Key\n");
			this->AddKeyboardKey(PGKey_Z, "Z_Key\n");
			this->AddKeyboardKey(PGKey_F1, "F1_Key\n");
			this->AddKeyboardKey(PGKey_F2, "F2_Key\n");
			this->AddKeyboardKey(PGKey_F3, "F3_Key\n");
			this->AddKeyboardKey(PGKey_F4, "F4_Key\n");
			this->AddKeyboardKey(PGKey_Page_Down, "Down_Key\n");
			this->AddKeyboardKey(PGKey_Page_Up, "Up_Key\n");
			this->AddKeyboardKey(PGKey_Left_Ctrl, "Ctrl_Left\n");
			this->AddKeyboardKey(PGKey_Right_Ctrl, "Ctrl_Right\n");


	}
	~PGControler()
	{
		delete(this->Keyboard_Keys);
	}
	PGControlerKey* PGControler::GetKey(PGKey key) {
		for (PGListNode<PGControlerKey> *c_node = Keyboard_Keys->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
			PGControlerKey * current_key = c_node->GetData();
			if (current_key->KeyCode == key) {
				return current_key;
			}
		}
		return nullptr;
}
	PGControlerKey* PGControler::GetKey(PGMouseKey key) {
		for (PGListNode<PGControlerKey> *c_node = Mouse_Keys->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
			PGControlerKey * current_key = c_node->GetData();
			if (current_key->KeyCode == key) {
				return current_key;
			}
		}
		return nullptr;
	}
	void PGControler::Update(PGGameWindow* _GameWindow)
	{
		v2 last_possition = v2(this->xpos, this->ypos);
		glfwGetCursorPos(_GameWindow->Gl_Window, &this->xpos, &this->ypos);
		v2 current_possition = v2(this->xpos, this->ypos);
		DeltaPossition = (current_possition - last_possition);

		for (PGListNode<PGControlerKey> *c_node = Mouse_Keys->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
			PGControlerKey* current_key = c_node->GetData();
				current_key->WasPress = current_key->IsPress;
				if (glfwGetMouseButton(_GameWindow->Gl_Window, current_key->KeyCode) == GLFW_PRESS) {
					current_key->IsPress = true;
				}
				else {
					current_key->IsPress = false;
				}
		}

		for (PGListNode<PGControlerKey> *c_node = Keyboard_Keys->GetHead(); c_node != nullptr; c_node = c_node->GetNext())	{
			PGControlerKey* current_key = c_node->GetData();
			current_key->WasPress = current_key->IsPress;
			if (glfwGetKey(_GameWindow->Gl_Window, current_key->KeyCode) == GLFW_PRESS) {
				current_key->IsPress = true;
			}
			else
			{
				current_key->IsPress = false;
			}
		}

	}
	bool PGControler::IsRelease(PGKey key){
		for (PGListNode<PGControlerKey> *c_node = Keyboard_Keys->GetHead(); c_node != nullptr; c_node = c_node->GetNext()){
			PGControlerKey * current_key = c_node->GetData();
			if (current_key->KeyCode == key){
				if (current_key->IsPress == false && current_key->WasPress == true)	{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
		return  false;
	}
	bool PGControler::IsRelease(PGMouseKey key) {
		for (PGListNode<PGControlerKey> *c_node = Mouse_Keys->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
			PGControlerKey * current_key = c_node->GetData();
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
	bool PGControler::IsPressed(PGKey key)
	{
		for (PGListNode<PGControlerKey> *c_node = Keyboard_Keys->GetHead(); c_node != nullptr; c_node = c_node->GetNext())
		{
			PGControlerKey * current_key = c_node->GetData();
			if (current_key->KeyCode == key){
				if (current_key->IsPress == true && current_key->WasPress == false)	{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
		return  false;
	}
	bool PGControler::IsPressed(PGMouseKey key) {
		for (PGListNode<PGControlerKey> *c_node = Mouse_Keys->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
			PGControlerKey * current_key = c_node->GetData();
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



#endif