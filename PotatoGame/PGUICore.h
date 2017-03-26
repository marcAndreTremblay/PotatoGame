#if !defined(PG_UI_CORE_H)
#define PG_UI_CORE_H

enum UIEventCode {
	UIEvent_Nothing = 0,
	UIEvent_Hide_Window = 1,
	UIEvent_Show_Window = 2,
	UIEvent_Button_Press = 3,
	UIEvent_Button_Release = 4
};
class PGUIEvent {
public:
	void *sender;
	UIEventCode code;
	PGUIEvent(void* sender_ptr, UIEventCode event_code) {
		this->code = event_code;
		this->sender = sender_ptr;
	}
	PGUIEvent() {
		this->code = UIEvent_Nothing;
		this->sender = nullptr;
	}
	~PGUIEvent() {

	}
};
class PGEventListener {
public:
	PGEventListener() {

	}
	~PGEventListener() {

	}
	virtual void PGEventListener::OnEvent(PGUIEvent *event) {

	}
};
class PGEventEmiter {
protected:
private:
	PGList<PGEventListener> *listener_list;
public:
	PGEventEmiter() {
		this->listener_list = new PGList<PGEventListener>(false);
	}
	~PGEventEmiter() {
		delete(this->listener_list);
	}
	void PGEventEmiter::AddListener(PGEventListener* new_listener) {
		if (new_listener != nullptr) {
			this->listener_list->Add(new_listener);
		}
	}
	void PGEventEmiter::EmiteEvent(PGUIEvent* new_event) {
		for (PGListNode<PGEventListener> *c_node = listener_list->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
			PGEventListener* current_ui_listener = c_node->GetData();
			current_ui_listener->OnEvent(new_event);
		}
		delete(new_event);
	}
};

enum UIElementState {
	UIState_Idle = 0,
	UIState_Hot = 1,
	UIState_Moving = 2,
	UIState_Left_Press = 3,
	UIState_Right_Press = 4,
	UIState_Drag = 5,
	UIState_Resizing = 6,
	UIState_Selecting = 7
};

class PGUIMargin {
public:
	r32 Left, Right, Top, Bottom;
	PGUIMargin(r32 left, r32 right, r32 top, r32 bottom) {
		this->Left = left;
		this->Right = right;
		this->Top = top;
		this->Bottom = bottom;
	}
	PGUIMargin(r32 margin) {
		this->Left = margin;
		this->Right = margin;
		this->Top = margin;
		this->Bottom = margin;
	}
	PGUIMargin() {
		this->Left = 0.f;
		this->Right = 0.f;
		this->Top = 0.f;
		this->Bottom = 0.f;
	}
	~PGUIMargin() {
	}
};



#endif