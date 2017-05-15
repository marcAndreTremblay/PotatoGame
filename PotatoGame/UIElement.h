#if !defined(PG_UI_BASE_ELEMENT_H)
#define PG_UI_BASE_ELEMENT_H


#include "GUICore.h"


using namespace PG::Engine;
namespace PG {
	namespace GUI {
		class UIElement : public EngineObject, public EventEmiter, public EventListener {
		protected:
			ElementState State;
			UIElement* Parent;//Un-managed resource
			EngineObjectList<UIElement>* Child_list;
			bool UIElement::IsIntersection(v3* mouse_location) {
				v2 rel_possition = this->GetRelativePossition();
				if ((mouse_location->x > rel_possition.x) && //Left
					(mouse_location->x < rel_possition.x + (this->Size.x)) && //Right
					(mouse_location->y > rel_possition.y) && //Bottom
					(mouse_location->y < rel_possition.y + (this->Size.y))) { //Top
					return true;
				}
				return false;
			}

			float GetRelativeZ() {
				if (this->Parent != nullptr) {
					return this->Parent->GetRelativeZ() + 0.001f;
				}
				return 0.f;
			}
			float GetRelativeOpacity() {
				if (this->Parent != nullptr) {
					return this->Parent->GetRelativeOpacity();
				}
				return this->Opacity;
			}
			v2 Size;
			v2 Possition;
		private:
		public:
			bool IsVisible;
			r32 Opacity;
			UIElement() {

				this->Child_list = new EngineObjectList<UIElement>(true);
				this->IsVisible = true;
				this->Parent = nullptr;
				this->State = UIState_Idle;
				this->Possition = v2(0.f, 0.f);
				this->Opacity = 1.f;
				this->Size = v2(1.f, 1.f);
			}
			virtual ~UIElement() {
				delete(this->Child_list);
				this->Parent = nullptr;
			}
			virtual bool UIElement::IsActif() {
				if (this->State == UIState_Hot) return true;
				return false;
			}
			virtual void UIElement::SetPossition(v2 possition) {
				this->Possition = possition;
			}
			virtual void UIElement::SetSize(v2 size) {
				this->Size = size;
			}
			virtual void UIElement::Render(BaseRenderer *renderer) {
				if (this->IsVisible == true) {
					for (ListNode<UIElement> *c_node = Child_list->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
						UIElement* current_ui_element = c_node->GetData();
						current_ui_element->Render(renderer);
					}
				}
			}
			virtual bool UIElement::Update(Controler *controler, double timeElapse, v3* mouse_ui_possition) {
				if (this->IsVisible == true) {
					bool isChildActive = false;
					for (ListNode<UIElement> *c_node = Child_list->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
						UIElement* current_ui_element = c_node->GetData();
						if (isChildActive == false) {
							if (current_ui_element->Update(controler, timeElapse, mouse_ui_possition) == true) {
								isChildActive = true;
							}
							else {
								if (current_ui_element->IsActif() == true) {
									isChildActive = true;
								}
							}
						}
					}
					if (isChildActive == false) {
						switch (this->State) {
						case UIState_Idle: {
							if (this->IsIntersection(mouse_ui_possition)) {
								this->State = UIState_Hot;
							}
							break; }
						case UIState_Hot: {
							if (!(this->IsIntersection(mouse_ui_possition))) {
								this->State = UIState_Idle;
							}
							break; }
						}
					}
					return isChildActive;
				}
				else {
					return false;
				}
			}
			virtual void UIElement::AddChild(UIElement* child_element) {
				child_element->Parent = this;
				Child_list->Add(child_element);
			}
			v2 UIElement::GetRelativePossition() {
				if (this->Parent != nullptr) {
					return (this->Possition + this->Parent->GetRelativePossition());
				}
				return (this->Possition);
			}
		};
	}
}
#endif 