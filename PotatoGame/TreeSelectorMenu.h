#if !defined(PG_UI_TREE_LIST_H)
#define PG_UI_TREE_LIST_H

#include "Core.h"
#include "Tree.h"
using namespace PG::Core;


#include "BaseRenderer.h"
#include "Controler.h"
#include "Font.h"
using namespace PG::Engine;


#include "GUICore.h"
#include "UIElement.h"

namespace PG {
	namespace GUI {
		class TreeListElement : public PG::Core::TreeNode<TreeListElement> {
			public:
				bool IsSelected;
				ElementState State;
				Str* Text;
				Font * _Font;
				r32 scale;
				TreeListElement() :
					TreeNode() {
					this->State = UIState_Idle;
					this->IsSelected = false;
					this->Text = nullptr;
					this->_Font = nullptr;
					this->scale = 0.5f;
				}
				TreeListElement(char* text, Font * font) :
					TreeNode() {
					this->Text = new Str(text);
					this->_Font = font;
					this->State = UIState_Idle;
					this->IsSelected = false;
					this->scale = 0.5f;
				}
				 ~TreeListElement() {
					delete(Text);
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
				v2 TreeListElement::GetBoundingBox() {
					return v2(80, 22);
				}
				void TreeListElement::Render(BaseRenderer *renderer, v2* render_possition, r32 child_x_offset, r32 sibling_y_offset, r32 z_layer, r32 rel_opa) {


					if (_Font != nullptr && Text != nullptr) {
						v2 size = v2(0.f);
						_Font->GetFontBondingBox(Text->CharAt(), 0.5f, &size);
						if (State == UIState_Hot) {
							renderer->RenderUIText(Text->CharAt(), v3(*render_possition, z_layer + 0.1f), v4(0.95f, 0.95f, 0.95f, 1.f), scale, _Font);
						}
						else {
							renderer->RenderUIText(Text->CharAt(), v3(*render_possition, z_layer + 0.1f), v4(0.8f, 0.8f, 0.8f, 1.f), scale, _Font);
						}

						if (this->child->element_count > 0) {
							render_possition->x += size.x;
							render_possition->y += size.y / 4.f;
							if (IsSelected == true) {
								renderer->RenderUIText(" +\n", v3(*render_possition, z_layer + 0.2f), v4(0.01f, 0.01f, 0.01f, 1.f), scale, _Font);
							}
							else {
								renderer->RenderUIText(" +\n", v3(*render_possition, z_layer + 0.2f), v4(0.1f, 0.1f, 0.1f, 1.f), scale, _Font);
							}
							render_possition->y -= size.y / 4.f;
							render_possition->x -= size.x;
						}
					}



					render_possition->y += GetBoundingBox().y;
					render_possition->y += sibling_y_offset;
					if (IsSelected == true) {
						render_possition->x += child_x_offset;
						for (ListNode<TreeNode> *c_node = this->child->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
							TreeListElement* current_root_element = (TreeListElement*)c_node->GetData();
							current_root_element->Render(renderer, render_possition, child_x_offset, sibling_y_offset, z_layer, rel_opa);
						}
						render_possition->x -= child_x_offset;
					}

				}
				void TreeListElement::Update(Controler *controler, double timeElapse, v3* mouse_ui_possition, v2 * render_possition, r32 child_x_offset, r32 sibling_y_offset) {

				v2 size = v2(0.f);
				_Font->GetFontBondingBox(Text->CharAt(), scale, &size);


				switch (this->State) {
				case UIState_Idle:
					if (IsIntersection(mouse_ui_possition, size, *render_possition) == true) {
						this->State = UIState_Hot;
					}
					break;
				case UIState_Hot:
					ControlerKey *right_mouse_key = controler->GetKey(PGMouse_Right);
					if (right_mouse_key->WasPress == true && right_mouse_key->IsPress == false) {
						if (this->IsSelected == true) {
							this->IsSelected = false;
						}
						else {
							this->IsSelected = true;
						}

					}
					if (IsIntersection(mouse_ui_possition, size, *render_possition) == false) {
						this->State = UIState_Idle;
					}
					break;
				}

				render_possition->y += GetBoundingBox().y;
				render_possition->y += sibling_y_offset;
				if (IsSelected == true) {
					render_possition->x += child_x_offset;
					for (ListNode<TreeNode> *c_node = this->child->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
						TreeListElement* current_root_element = (TreeListElement*)c_node->GetData();
						current_root_element->Update(controler, timeElapse, mouse_ui_possition, render_possition, child_x_offset, sibling_y_offset);
					}
					render_possition->x -= child_x_offset;
				}
			}
		};
		class TreeSelectorMenu : public UIElement {
			protected:
			private:
			public:
				Font * text_font;
				Tree<TreeListElement> *elements;
				v2 element_margin;
				r32 child_x_offset;
				r32 sibling_y_offset;
				TreeSelectorMenu(Font * font = nullptr) {
					this->element_margin = v2(3.f, 3.f);
					this->child_x_offset = 12.f;
					this->sibling_y_offset = 3.f;
					this->text_font = font;
					this->elements = new Tree<TreeListElement>();

					TreeListElement *r1 = new TreeListElement("Races", text_font);
					TreeListElement *a1 = new TreeListElement("Humain", text_font);
					TreeListElement *a4 = new TreeListElement("Dwaft", text_font);
					a4->AddChild(new TreeListElement("Artisan", text_font));
					a4->AddChild(new TreeListElement("Scavanger", text_font));
					a1->AddChild(new TreeListElement("Priest", text_font));
					a1->AddChild(new TreeListElement("Warrior", text_font));
					a1->AddChild(new TreeListElement("Scout", text_font));
					TreeListElement *a2 = new TreeListElement("Elf", text_font);
					a2->AddChild(new TreeListElement("Wizard", text_font));
					a2->AddChild(new TreeListElement("Swordman", text_font));
					a2->AddChild(new TreeListElement("Oracle", text_font));
					TreeListElement *a3 = new TreeListElement("Orc", text_font);
					a3->AddChild(new TreeListElement("Warrior", text_font));
					a3->AddChild(new TreeListElement("Shaman", text_font));
					a3->AddChild(new TreeListElement("Destroyer", text_font));
					a3->AddChild(new TreeListElement("Hunter", text_font));
					r1->AddChild(a1);
					r1->AddChild(a2);
					r1->AddChild(a3);
					r1->AddChild(a4);
					TreeListElement *r2 = new TreeListElement("Object type\n", text_font);
					r2->AddChild(new TreeListElement("Weapon\n", text_font));
					r2->AddChild(new TreeListElement("Armor\n", text_font));
					r2->AddChild(new TreeListElement("Reagent\n", text_font));
					r2->AddChild(new TreeListElement("Consumable\n", text_font));
					r2->AddChild(new TreeListElement("Quest item\n", text_font));
					TreeListElement *r3 = new TreeListElement("Proffesion\n", text_font);
					r3->AddChild(new TreeListElement("Alchemy\n", text_font));
					r3->AddChild(new TreeListElement("Blacksmith\n", text_font));
					r3->AddChild(new TreeListElement("Miner\n", text_font));
					elements->roots->Add(r1);
					elements->roots->Add(r2);
					elements->roots->Add(r3);
				}
				~TreeSelectorMenu() {
					delete(this->elements);
				}
				virtual void TreeSelectorMenu::Render(BaseRenderer *renderer) override {
					if (this->IsVisible == true) {
						v2 render_possition = this->GetRelativePossition();
						r32 z_layer = this->GetRelativeZ();
						r32 rel__opa = this->GetRelativeOpacity();
						renderer->ui_panel_Mesh->Render(v3(render_possition, z_layer), this->Size, v4(0.1f, 0.1f, 0.1f, 0.3f));
						render_possition += element_margin;
						for (ListNode<TreeListElement> *c_node = elements->roots->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
							TreeListElement* current_root_element = c_node->GetData();
							current_root_element->Render(renderer, &render_possition, child_x_offset, sibling_y_offset, z_layer + 0.1f, rel__opa);
						}
					}
					UIElement::Render(renderer);
				}
				virtual bool TreeSelectorMenu::Update(Controler *controler, double timeElapse, v3 *mouse_ui_possition) {
					bool isChildActive = UIElement::Update(controler, timeElapse, mouse_ui_possition);

					if (isChildActive == false && this->State == UIState_Hot) {

						v2 render_possition = this->GetRelativePossition();
						render_possition += element_margin;
						for (ListNode<TreeListElement> *c_node = elements->roots->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
							TreeListElement* current_root_element = c_node->GetData();
							current_root_element->Update(controler, timeElapse, mouse_ui_possition, &render_possition, child_x_offset, sibling_y_offset);
						}

					}
					return isChildActive;
				}
				virtual bool TreeSelectorMenu::IsActif() override {
				if (this->State == UIState_Hot) return true;
				return false;
			}
		};
	}
}
#endif