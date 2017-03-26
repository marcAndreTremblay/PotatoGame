#if !defined(PG_UI_SELECT_LIST_H)
#define PG_UI_SELECT_LIST_H



#include "PGUICore.h"


#include "PGBaseRenderer.h"
#include "PGControler.h"
#include "PGFont.h"

#include "PGList.h"


class PGUISelectNode {
protected:
private:
public:
	UIElementState State;
	v2 size;
	v2 PGUISelectNode::GetBoundingBox() {
		return size;
	}
	PGUISelectNode() {
		size = v2(130, 20);		
	}
	~PGUISelectNode() {

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
	virtual void PGUISelectNode::Render(PGBaseRenderer *renderer, v2 * possition, r32 layer,r32 opacity) {
		renderer->ui_panel_Mesh->Render(v3(*possition, layer), GetBoundingBox(), v4(0.3f, 0.2f, 0.5f, opacity));
		possition->y += GetBoundingBox().y;
	}
	virtual void PGUISelectNode::Update(PGControler *controler, double timeElapse, v3 *mouse_ui_possition, v2 * render_possition) {
		
		switch (this->State) {
		case UIState_Idle:
			if (IsIntersection(mouse_ui_possition, size, *render_possition) == true) {
				this->State = UIState_Hot;
			}
			break;
		case UIState_Hot:
			PGControlerKey *right_mouse_key = controler->GetKey(PGMouse_Right);
			if (right_mouse_key->WasPress == true && right_mouse_key->IsPress == false) {
				
			}
			if (IsIntersection(mouse_ui_possition, size, *render_possition) == false) {
				this->State = UIState_Idle;
			}
			break;
		}

		render_possition->y += GetBoundingBox().y;
	}
};

class PGUISelectView : public PGBaseUIElement {
	protected:
	private:
		r32 element_y_offest;
		v2 element_margin;
	public:
		PGList<PGUISelectNode> *element_list;
		PGUISelectNode *selected;
		PGUISelectView() {
			this->element_margin = v2(3.f, 3.f);
			this->element_y_offest = 4.f;
			this->element_list = new PGList<PGUISelectNode>(true);
			this->selected = nullptr;

			PGUISelectNode *element_1 = new PGUISelectNode();
			selected = element_1;

			element_list->Add(element_1);
			element_list->Add(new PGUISelectNode());
			element_list->Add(new PGUISelectNode());
			element_list->Add(new PGUISelectNode());
			element_list->Add(new PGUISelectNode());
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
				if (this->State == UIState_Hot) {
					renderer->ui_panel_Mesh->Render(v3(render_possition, z_layer), this->Size, v4(0.1f, 0.1f, 0.1f, rel__opa));
				}
				if (this->State == UIState_Idle) {
					renderer->ui_panel_Mesh->Render(v3(render_possition, z_layer), this->Size, v4(0.3f, 0.4f, 0.3f, rel__opa));
				}
				if (this->State == UIState_Selecting) {
					renderer->ui_panel_Mesh->Render(v3(render_possition, z_layer), this->Size, v4(0.1f, 0.6f, 0.8f, rel__opa));
				}
				render_possition += element_margin;
				//Render the selected one 
				if (selected != nullptr) {
					selected->Render(renderer, &render_possition, z_layer + 0.1f, rel__opa);
					render_possition.y += element_y_offest;
				}
				if (this->State == UIState_Selecting) {
					for (PGListNode<PGUISelectNode> *c_node = this->element_list->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
						PGUISelectNode* current_root_element = (PGUISelectNode*)c_node->GetData();
							current_root_element->Render(renderer, &render_possition, z_layer + 0.1f, rel__opa);
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
					case UIState_Hot:
						PGControlerKey* key1 = controler->GetKey(PGMouse_Left);
						if (key1->IsPress == false && key1->WasPress == true) {
							this->State = UIState_Selecting;
						}	
						break;
				}
			}
			return isChildActive;
		}
		virtual bool PGUISelectView::IsActif() override {
			if (this->State == UIState_Selecting) return true;
			if (this->State == UIState_Hot) return true;
			return false;
		}
};

#endif