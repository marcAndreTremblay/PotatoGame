#if !defined(PG_UI_SELECT_LIST_H)
#define PG_UI_SELECT_LIST_H



#include "PGUICore.h"


#include "PGBaseRenderer.h"
#include "PGControler.h"
#include "PGFont.h"

#include "PGList.h"

using namespace PG::GUI;
namespace PG {
	namespace GUI {
		class PGUISelectNode : public PGEventEmiter {
		protected:
		private:
		public:
			UIElementState State;
			PGUISelectNode() : PGEventEmiter() {
				State = UIState_Idle;
			}
			virtual ~PGUISelectNode() {

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
			virtual void PGUISelectNode::Render(PGBaseRenderer *renderer, v2 * possition, r32 layer, r32 opacity, v2 *size) {
				if (this->State == UIState_Idle) {
					renderer->ui_panel_Mesh->Render(v3(*possition, layer), *size, v4(0.3f, 0.2f, 0.5f, opacity));
				}
				if (this->State == UIState_Hot) {
					renderer->ui_panel_Mesh->Render(v3(*possition, layer), *size, v4(0.4f, 0.7f, 0.1f, opacity));
				}
			}
			virtual void PGUISelectNode::Update(PGControler *controler, double timeElapse, v3 *mouse_ui_possition, v2 * render_possition, v2 *size) {

				switch (this->State) {
				case UIState_Idle:
					if (IsIntersection(mouse_ui_possition, *size, *render_possition) == true) {
						this->State = UIState_Hot;
					}
					break;
				case UIState_Hot:

					PGControlerKey *left_mouse_key = controler->GetKey(PGMouse_Left);
					if (left_mouse_key->WasPress == true && left_mouse_key->IsPress == false) {
						PGUIEvent *evet = new PGUIEvent(this, UIEvent_Element_Select);
						this->EmiteEvent(evet);
						delete(evet);
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
		class PGUIStringNode : public PGUISelectNode {
		public:
			Str * Text;
			PGFont * Font;
			PGUIStringNode() {
				Text = nullptr;
				Font = nullptr;
			}
			PGUIStringNode(char *text, PGFont * font) : PGUISelectNode() {
				Text = new Str(text);
				Font = font;
			}
			~PGUIStringNode() {
				delete(Text);
			}
			virtual void PGUIStringNode::Render(PGBaseRenderer *renderer, v2 * possition, r32 layer, r32 opacity, v2 *size) override {
				PGUISelectNode::Render(renderer, possition, layer, opacity, size);
				if (Font != nullptr && Text != nullptr) {
					renderer->RenderUIText(Text->CharAt(), v3(*possition, layer + 0.2f), v4(0.01f, 0.01f, 0.01f, 1.f), 0.5f, Font);
				}
			}
		};
		class PGUISelectView : public PGBaseUIElement {
		protected:
		private:
			r32 element_y_offest;
			v2 element_margin;
			v2 element_size;
			PGFont * Font;
			PGList<PGUISelectNode> *element_list;
		public:

			PGUISelectNode *selected;
			PGUISelectView(PGFont * font = nullptr) {
				this->element_margin = v2(5.f, 5.f);
				this->element_y_offest = 0.f;
				this->element_list = new PGList<PGUISelectNode>(true);
				this->selected = nullptr;
				element_size = v2(190, 20);
				PGUISelectNode *element_1 = new PGUISelectNode();
				selected = element_1;
				Font = font;

				this->AddElement(element_1);
				this->AddElement(new PGUIStringNode("Test 1\n", font));
				this->AddElement(new PGUIStringNode("Test 2\n", font));
				this->AddElement(new PGUIStringNode("Test 3\n", font));
				this->AddElement(new PGUIStringNode("Test 4\n", font));
			}
			~PGUISelectView() {
				delete(element_list);
			}
			virtual void PGUISelectView::Render(PGBaseRenderer *renderer) override {
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
						for (PGListNode<PGUISelectNode> *c_node = this->element_list->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
							PGUISelectNode* current_root_element = (PGUISelectNode*)c_node->GetData();
							current_root_element->Render(renderer, &render_possition, z_layer + 0.1f, rel__opa, &this->element_size);
							render_possition.y += element_size.y;
							render_possition.y += element_y_offest;
						}
					}
				}
				PGBaseUIElement::Render(renderer);
			}
			virtual bool PGUISelectView::Update(PGControler *controler, double timeElapse, v3 *mouse_ui_possition) {
				bool isChildActive = PGBaseUIElement::Update(controler, timeElapse, mouse_ui_possition);
				if (isChildActive != true) {
					switch (this->State) {
					case UIState_Hot:{
										 PGControlerKey* key1 = controler->GetKey(PGMouse_Left);
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
											   for (PGListNode<PGUISelectNode> *c_node = this->element_list->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
												   PGUISelectNode* current_root_element = (PGUISelectNode*)c_node->GetData();
												   current_root_element->Update(controler, timeElapse, mouse_ui_possition, &render_possition, &this->element_size);
												   render_possition.y += element_size.y;
												   render_possition.y += element_y_offest;
											   }
											   PGControlerKey* r_key = controler->GetKey(PGMouse_Right);
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
			virtual bool PGUISelectView::IsActif() override {
				if (this->State == UIState_Selecting) return true;
				if (this->State == UIState_Hot) return true;
				return false;
			}
			void PGUISelectView::AddElement(PGUISelectNode * element) {
				element->AddListener(this);
				element_list->Add(element);
			}

			virtual void PGUISelectView::OnEvent(PGUIEvent *event) override {
				if (event->code == UIEvent_Element_Select) {
					selected = (PGUISelectNode*)event->sender;
					EmiteEvent(event);
				}

			}
		};
	}
}
#endif