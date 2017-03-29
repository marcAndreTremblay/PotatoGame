#if !defined(PG_UI_CORE_H)
#define PG_UI_CORE_H

#include "Core.h"
#include "List.h"
using namespace PG::Core;
namespace PG {
	namespace GUI {
		enum GGUIEventCode {
			GUIEvent_Nothing = 0,
			GUIEvent_Hide_Window = 1,
			GUIEvent_Show_Window = 2,
			GUIEvent_Button_Press = 3,
			GUIEvent_Button_Release = 4,
			GUIEvent_Element_Select = 5
		};
		class GUIEvent {
		public:
			void *sender;
			GGUIEventCode code;
			GUIEvent(void* sender_ptr, GGUIEventCode event_code) {
				this->code = event_code;
				this->sender = sender_ptr;
			}
			GUIEvent() {
				this->code = GUIEvent_Nothing;
				this->sender = nullptr;
			}
			~GUIEvent() {

			}

		};
		class EventListener {
		public:
			EventListener() {

			}
			~EventListener() {

			}
			virtual void EventListener::OnEvent(GUIEvent *event) {

			}
		};
		class EventEmiter {
		protected:
		private:
			List<EventListener> *listener_list;
		public:
			EventEmiter() {
				this->listener_list = new List<EventListener>(false);
			}
			~EventEmiter() {
				delete(this->listener_list);
			}
			void EventEmiter::AddListener(EventListener* new_listener) {
				if (new_listener != nullptr) {
					this->listener_list->Add(new_listener);
				}
			}
			void EventEmiter::EmiteEvent(GUIEvent* new_event) {
				for (ListNode<EventListener> *c_node = listener_list->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
					EventListener* current_ui_listener = c_node->GetData();
					current_ui_listener->OnEvent(new_event);
				}

			}
		};

		enum GUIElementState {
			UIState_Idle = 0,
			UIState_Hot = 1,
			UIState_Moving = 2,
			UIState_Left_Press = 3,
			UIState_Right_Press = 4,
			UIState_Drag = 5,
			UIState_Resizing = 6,
			UIState_Selecting = 7
		};

		class GUIMargin {
		public:
			r32 Left, Right, Top, Bottom;
			GUIMargin(r32 left, r32 right, r32 top, r32 bottom) {
				this->Left = left;
				this->Right = right;
				this->Top = top;
				this->Bottom = bottom;
			}
			GUIMargin(r32 margin) {
				this->Left = margin;
				this->Right = margin;
				this->Top = margin;
				this->Bottom = margin;
			}
			GUIMargin() {
				this->Left = 0.f;
				this->Right = 0.f;
				this->Top = 0.f;
				this->Bottom = 0.f;
			}
			~GUIMargin() {
			}
		};

	}
}

#endif