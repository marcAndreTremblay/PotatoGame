#if !defined(PG_UI_SELECT_LIST_H)
#define PG_UI_SELECT_LIST_H




#include "List.h"
using namespace PG::Core;


#include "BaseRenderer.h"
#include "Controler.h"
#include "Font.h"
using namespace PG::Engine;

#include "GUICore.h"
#include "UIElement.h"

namespace PG {
	namespace GUI {
		class GUISelectNode : public EventEmiter {
		protected:
		private:
		public:
			ElementState State;
			GUISelectNode() : EventEmiter() {
				State = UIState_Idle;
			}
			virtual ~GUISelectNode() {

			}
			bool IsIntersection(v3* mouse_location, v2 size, v2 rel_possition) {
				if ((mouse_location->x > rel_possition.x) && //Left
					(mouse_location->x < rel_possition.x + (size.x)) && //Right
					(mouse_location->y > rel_possition.y) && //Bottom
					(mouse_location->y < rel_possition.y + (size.y))) { //Top
					return true;
				}
				return false;
			}
			virtual void GUISelectNode::Render(BaseRenderer *renderer, v2 * possition, r32 layer, r32 opacity, v2 *size) {
				if (this->State == UIState_Idle) {
					renderer->ui_panel_Mesh->Render(v3(*possition, layer), *size, v4(0.3f, 0.2f, 0.5f, opacity));
				}
				if (this->State == UIState_Hot) {
					renderer->ui_panel_Mesh->Render(v3(*possition, layer), *size, v4(0.4f, 0.7f, 0.1f, opacity));
				}
			}
			virtual void GUISelectNode::Update(Controler *controler, double timeElapse, v3 *mouse_ui_possition, v2 * render_possition, v2 *size) {

				switch (this->State) {
				case UIState_Idle:
					if (IsIntersection(mouse_ui_possition, *size, *render_possition) == true) {
						this->State = UIState_Hot;
					}
					break;
				case UIState_Hot:

					ControlerKey *left_mouse_key = controler->GetKey(PGMouse_Left);
					if (left_mouse_key->WasPress == true && left_mouse_key->IsPress == false) {
						GUIEvent *evet = new GUIEvent(this, GUIEvent_Element_Select);
						this->EmiteEvent(evet);
						
					}
					if (IsIntersection(mouse_ui_possition, *size, *render_possition) == false) {
						this->State = UIState_Idle;
					}
					else {
						this->State = UIState_Hot;
					}
					break;
				}
			}
		};
		class GUIStringNode : public GUISelectNode {
		public:
			Str * Text;
			Font * Font;
			GUIStringNode() {
				Text = nullptr;
				Font = nullptr;
			}
			GUIStringNode(char *text, PG::Engine::Font * font) : GUISelectNode() {
				Text = new Str(text);
				Font = font;
			}
			~GUIStringNode() {
				delete(Text);
			}
			virtual void GUIStringNode::Render(BaseRenderer *renderer, v2 * possition, r32 layer, r32 opacity, v2 *size) override {
				GUISelectNode::Render(renderer, possition, layer, opacity, size);
				if (Font != nullptr && Text != nullptr) {
					renderer->RenderUIText(Text->CharAt(), v3(*possition, layer + 0.2f), v4(0.01f, 0.01f, 0.01f, 1.f), 0.5f, Font);
				}
			}
		};
		class DropDownMenu : public UIElement {
		protected:
		private:
			r32 element_y_offest;
			v2 element_margin;
			v2 element_size;
			Font * _Font;
			List<GUISelectNode> *Element_list;
		public:

			GUISelectNode *selected;
			DropDownMenu(Font * font = nullptr) {
				this->element_margin = v2(5.f, 5.f);
				this->element_y_offest = 0.f;
				this->Element_list = new List<GUISelectNode>(true);
				this->selected = nullptr;
				
				
				_Font = font;


			}
			~DropDownMenu() {
				delete(Element_list);
			}
			virtual void DropDownMenu::Render(BaseRenderer *renderer) override {
				if (this->IsVisible == true) {
					v2 render_possition = this->GetRelativePossition();
					r32 z_layer = this->GetRelativeZ();
					r32 rel__opa = this->GetRelativeOpacity();

					//Render size
					renderer->ui_panel_Mesh->Render(v3(render_possition, z_layer), this->Size, v4(0.3f, 0.4f, 0.3f, rel__opa));


					render_possition += element_margin;
					//Render the selected one 
					if (selected != nullptr) {
						selected->Render(renderer, &render_possition, z_layer + 0.1f, rel__opa, &this->element_size);
					}
					render_possition.y += element_size.y;
					render_possition.y += element_y_offest;
					render_possition.y += 2.f;
					if (this->State == UIState_Selecting) {
						for (ListNode<GUISelectNode> *c_node = this->Element_list->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
							GUISelectNode* current_root_element = (GUISelectNode*)c_node->GetData();
							current_root_element->Render(renderer, &render_possition, z_layer + 0.1f, rel__opa, &this->element_size);
							render_possition.y += element_size.y;
							render_possition.y += element_y_offest;
						}
					}
				}
				UIElement::Render(renderer);
			}
			virtual bool DropDownMenu::Update(Controler *controler, double timeElapse, v3 *mouse_ui_possition) {
				bool isChildActive = UIElement::Update(controler, timeElapse, mouse_ui_possition);
				if (isChildActive != true) {
					switch (this->State) {
					case UIState_Hot:{
										 ControlerKey* key1 = controler->GetKey(PGMouse_Left);
										 if (key1->IsPress == false && key1->WasPress == true) {
											 this->State = UIState_Selecting;
										 }
										 break;
					}
					case UIState_Selecting:{
											   v2 render_possition = this->GetRelativePossition();
											   render_possition += element_margin;
											   render_possition.y += element_size.y;
											   render_possition.y += element_y_offest;

											   //Update node
											   for (ListNode<GUISelectNode> *c_node = this->Element_list->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
												   GUISelectNode* current_root_element = (GUISelectNode*)c_node->GetData();
												   current_root_element->Update(controler, timeElapse, mouse_ui_possition, &render_possition, &this->element_size);
												   render_possition.y += element_size.y;
												   render_possition.y += element_y_offest;
											   }
											   ControlerKey* r_key = controler->GetKey(PGMouse_Right);
											   if (r_key->WasPress == true && r_key->IsPress == false) {
												   if (IsIntersection(mouse_ui_possition) == true) {
													   this->State = UIState_Hot;
												   }
												   else {
													   this->State = UIState_Idle;
													 
												   }

											   }

											   break;
					}
					}
				}
				return isChildActive;
			}
			virtual bool DropDownMenu::IsActif() override {
				if (this->State == UIState_Selecting) return true;
				if (this->State == UIState_Hot) return true;
				return false;
			}
			void DropDownMenu::AddElement(GUISelectNode * element) {
				element->AddListener(this);
				Element_list->Add(element);
			}
			virtual void DropDownMenu::SetSize(v2 size) override{
				UIElement::SetSize(size);
				element_size = size - element_margin - element_margin;
			}
			virtual void DropDownMenu::OnEvent(GUIEvent *event) override {
				if (event->code == GUIEvent_Element_Select) {
					selected = (GUISelectNode*)event->sender;
					delete(event);
					EmiteEvent(new GUIEvent(this, GUIEvent_Element_Select));
				}

			}
			
		};
	}
}
#endif