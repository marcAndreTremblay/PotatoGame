#if !defined(PG_UI_BASE_ELEMENT_H)
#define PG_UI_BASE_ELEMENT_H


#include "PGUICore.h"

using namespace PG::Engine;
using namespace PG::GUI;
namespace PG {
	namespace GUI {
		class PGBaseUIElement : public BaseObject, public PGEventEmiter, public PGEventListener {
		protected:
			UIElementState State;
			PGBaseUIElement* Parent;//Un-managed resource
			ObjectList<PGBaseUIElement>* Child_list;
			bool PGBaseUIElement::IsIntersection(v3* mouse_location) {
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
			PGBaseUIElement() {

				this->Child_list = new ObjectList<PGBaseUIElement>(true);
				this->IsVisible = true;
				this->Parent = nullptr;
				this->State = UIState_Idle;
				this->Possition = v2(0.f, 0.f);
				this->Opacity = 1.f;
				this->Size = v2(1.f, 1.f);
			}
			~PGBaseUIElement() {
				delete(this->Child_list);
				this->Parent = nullptr;
			}
			virtual bool PGBaseUIElement::IsActif() {
				if (this->State == UIState_Hot) return true;
				return false;
			}
			virtual void PGBaseUIElement::SetPossition(v2 possition) {
				this->Possition = possition;
			}
			virtual void PGBaseUIElement::SetSize(v2 size) {
				this->Size = size;
			}
			virtual void PGBaseUIElement::Render(BaseRenderer *renderer) {
				if (this->IsVisible == true) {
					for (ListNode<PGBaseUIElement> *c_node = Child_list->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
						PGBaseUIElement* current_ui_element = c_node->GetData();
						current_ui_element->Render(renderer);
					}
				}
			}
			virtual bool PGBaseUIElement::Update(Controler *controler, double timeElapse, v3* mouse_ui_possition) {
				if (this->IsVisible == true) {
					bool isChildActive = false;
					for (ListNode<PGBaseUIElement> *c_node = Child_list->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
						PGBaseUIElement* current_ui_element = c_node->GetData();
						if (current_ui_element->Update(controler, timeElapse, mouse_ui_possition) == true) {
							isChildActive = true;
						}
						else {
							if (current_ui_element->IsActif() == true) {
								isChildActive = true;
							}
						}
					}
					switch (this->State) {
					case UIState_Idle:{
										  if (this->IsIntersection(mouse_ui_possition)) {
											  this->State = UIState_Hot;
										  }
										  break; }
					case UIState_Hot:{
										 if (!(this->IsIntersection(mouse_ui_possition))) {
											 this->State = UIState_Idle;
										 }
										 break; }
					}
					return isChildActive;
				}
				else {
					return false;
				}
			}
			virtual void PGBaseUIElement::AddChild(PGBaseUIElement* child_element) {
				child_element->Parent = this;
				Child_list->Add(child_element);
			}
			v2 PGBaseUIElement::GetRelativePossition() {
				if (this->Parent != nullptr) {
					return (this->Possition + this->Parent->GetRelativePossition());
				}
				return (this->Possition);
			}


		};


		class PGUILabel : public PGBaseUIElement {
		protected:
		private:
			Str* Text;
			Font* _Font; //Un-managed resource
		public:
			v3 Text_Color;
			r32 Text_Size;
			PGUILabel() {
				this->Text = nullptr;
				this->_Font = nullptr;
				this->Text_Color = v3(1.f);
				this->Text_Size = 1.f;
			}
			~PGUILabel() {
				delete(this->Text);
			}
			void PGUILabel::SetText(char* text) {
				if (this->Text != nullptr) {
					delete(this->Text);
				}
				this->Text = new Str(text);
			}
			void PGUILabel::SetFont(Font* font) {
				this->_Font = font;
			}

			virtual void PGUILabel::Render(BaseRenderer *renderer) override {
				if (this->IsVisible == true && this->Text != nullptr && this->_Font != nullptr) {
					v2 box = v2();
					_Font->GetFontBondingBox(this->Text->CharAt(), Text_Size, &box);

					renderer->RenderUIText(this->Text->CharAt(), v3(this->GetRelativePossition(), this->GetRelativeZ()), v4(this->Text_Color, this->GetRelativeOpacity()), this->Text_Size, this->_Font);
					//renderer->ui_panel_Mesh->Render(v3(this->GetRelativePossition(), this->GetRelativeZ()), box, v4(1.f, 1.f, 0.f, 1.f));
				}
			}
			virtual bool PGUILabel::Update(Controler *controler, double timeElapse, v3 *mouse_ui_possition) {
				return PGBaseUIElement::Update(controler, timeElapse, mouse_ui_possition);
			}
			virtual bool PGUILabel::IsActif() override {
				return false;
			}
		};
		class PGUIImageBox : public PGBaseUIElement {
		protected:
		private:
		public:
			Texture* Image;
			v3 Color_Channel;
			PGUIImageBox() {
				this->Color_Channel = v3(1.f);
				this->Image = nullptr;
				this->IsVisible = true;
			}
			~PGUIImageBox() {

			}
			virtual void PGUIImageBox::Render(BaseRenderer *renderer) override {
				if (this->IsVisible == true) {
					renderer->ui_image_mesh->Render(v3(this->GetRelativePossition(), this->GetRelativeZ()), this->Size, this->Image, v4(this->Color_Channel, this->GetRelativeOpacity()));
				}
			}
			virtual bool PGUIImageBox::Update(Controler *controler, double timeElapse, v3 *mouse_ui_possition) {
				bool isChildActive = PGBaseUIElement::Update(controler, timeElapse, mouse_ui_possition);

				return isChildActive;
			}
			bool PGUIImageBox::IsActif() override {
				return false;
			}
		};


		class PGUIPanel : public PGBaseUIElement {
		protected:
		private:
		public:
			v3 background_color;
			PGUIPanel() {
				this->background_color = v3(0.5f);
			}
			~PGUIPanel() {

			}
			virtual bool PGUIPanel::IsActif() override {
				return false;
			}
			virtual void PGUIPanel::Render(BaseRenderer *renderer) override {
				if (this->IsVisible == true) {
					if (this->State == UIState_Idle) {
						this->Opacity = 0.4f;
					}
					if (this->State == UIState_Hot) {
						this->Opacity = 1.f;
					}
					if (this->State == UIState_Moving) {
						this->Opacity = 1.f;
					}
					renderer->ui_panel_Mesh->Render(v3(this->GetRelativePossition(), this->GetRelativeZ()), this->Size, v4(this->background_color, this->GetRelativeOpacity()));
				}
				PGBaseUIElement::Render(renderer);
			}
			virtual bool PGUIPanel::Update(Controler *controler, double timeElapse, v3 *mouse_ui_possition) {
				bool isChildActive = PGBaseUIElement::Update(controler, timeElapse, mouse_ui_possition);
				if (isChildActive == false) {

				}
				return isChildActive;
			}
		};

		//Entity A , Entity B
		class PGUIButton : public PGBaseUIElement {
		protected:
		private:
			Str* Text;
			Font* Font; //Un-managed resource
		public:
			v3 Text_color;
			r32 Text_size;
			void PGUIButton::SetText(char* text) {
				if (this->Text != nullptr) {
					delete(this->Text);
				}
				this->Text = new Str(text);
			}
			void PGUIButton::SetFont(PG::Engine::Font* font) {
				this->Font = font;
			}

			PGUIButton() {

				this->Text_color = v3(0.f);
				this->Text_size = 1.f;
				this->Text = nullptr;
				this->Font = nullptr;
			}
			~PGUIButton() {

			}
			virtual bool PGUIButton::IsActif() override {
				if (this->State != UIState_Idle) return true;
				return false;
			}
			virtual void PGUIButton::Render(BaseRenderer *renderer) override {
				if (this->IsVisible == true) {
					if (this->State == UIState_Idle) {
						renderer->ui_panel_Mesh->Render(v3(this->GetRelativePossition(), this->GetRelativeZ()), this->Size, v4(1.f, 0.4f, 0.2f, this->GetRelativeOpacity()));
					}
					if (this->State == UIState_Hot) {
						renderer->ui_panel_Mesh->Render(v3(this->GetRelativePossition(), this->GetRelativeZ()), this->Size, v4(0.1f, 1.f, 0.3f, 1.0f));
					}
					if (this->State == UIState_Left_Press) {
						renderer->ui_panel_Mesh->Render(v3(this->GetRelativePossition(), this->GetRelativeZ()), this->Size, v4(1.f, 0.f, 1.f, 1.0f));
					}
					if (this->State == UIState_Right_Press) {
						renderer->ui_panel_Mesh->Render(v3(this->GetRelativePossition(), this->GetRelativeZ()), this->Size, v4(1.f, 1.f, 0.f, 1.f));
					}
					if (Text != nullptr && Font != nullptr) {
						renderer->RenderUIText(this->Text->CharAt(), v3(this->GetRelativePossition(), this->GetRelativeZ()) + v3(0.f, 0.f, 0.1f), v4(Text_color, this->GetRelativeOpacity()), this->Text_size, this->Font);
					}
				}
				PGBaseUIElement::Render(renderer);
			}
			virtual bool PGUIButton::Update(Controler *controler, double timeElapse, v3* mouse_ui_possition) {
				bool isChildActive = PGBaseUIElement::Update(controler, timeElapse, mouse_ui_possition);
				if (isChildActive == false) {
					switch (this->State) {
					case UIState_Hot:{
										 if (controler->IsPressed(PGMouse_Left) == true) {
											 this->State = UIState_Left_Press;
											 this->EmiteEvent(new PGUIEvent(this, UIEvent_Button_Press));
										 }
										 if (controler->IsPressed(PGMouse_Right) == true) {
											 this->State = UIState_Right_Press;
											 this->EmiteEvent(new PGUIEvent(this, UIEvent_Button_Press));
										 }
										 break; }
					case UIState_Left_Press:{
												if (controler->IsRelease(PGMouse_Left) == true) {
													if (this->IsIntersection(mouse_ui_possition) == true) {
														this->State = UIState_Hot;
													}
													else {
														this->State = UIState_Idle;
													}
													this->EmiteEvent(new PGUIEvent(this, UIEvent_Button_Release));
												}
												break; }
					case UIState_Right_Press:{
												 if (controler->IsRelease(PGMouse_Right) == true) {
													 if (this->IsIntersection(mouse_ui_possition) == true) {
														 this->State = UIState_Hot;
													 }
													 else {
														 this->State = UIState_Idle;
													 }
													 this->EmiteEvent(new PGUIEvent(this, UIEvent_Button_Release));
												 }
												 break; }

					}

				}
				return isChildActive;
			}
		};


		class PGUISelectBox : public PGBaseUIElement {
		protected:
		private:
			List<BaseObject> *element_list;
			int selected_index = 1; //Note(Marc): -1 for no selection
			int hot_index = -1;


			//Fix property
			Font *font;
			v2 element_size;
			r32 element_offset = 2.0f;
			float font_size = 0.7f;
			v4 back_color = v4(0.3f, 0.5f, 0.3f, 1.f);
			v4 text_color = v4(0.8f, 0.8f, 0.8f, 1.f);
		public:
			PGUISelectBox() {
				element_list = new List<BaseObject>(false);
			}
			~PGUISelectBox() {
				delete(element_list);
			}
			void PGUISelectBox::SetFont(Font *_font) {
				this->font = _font;
			}
			void PGUISelectBox::SetSize(v2 size) {
				element_size.x = size.x - 10;
				element_size.y = size.y;
				PGBaseUIElement::SetSize(size);
			}
			void PGUISelectBox::AddListElement(BaseObject *new_obj) {
				element_list->Add(new_obj);
			}
			virtual bool PGUISelectBox::IsActif() override {
				if (this->State == UIState_Selecting) return true;
				if (this->State == UIState_Hot) return true;
				return false;
			}
			virtual void PGUISelectBox::Render(BaseRenderer *renderer) override {
				if (this->IsVisible == true) {

					v3 pos_offset = v3(this->GetRelativePossition(), this->GetRelativeZ());
					r32 rel_alpha = this->GetRelativeOpacity();


					back_color.a = rel_alpha;
					text_color.a = rel_alpha;

					char *selected_string = nullptr;
					renderer->ui_panel_Mesh->Render(pos_offset, this->Size, back_color);

					if (selected_index > -1) {
						selected_string = element_list->GetAt(selected_index)->Get_Name()->CharAt();
						renderer->RenderUIText(selected_string, pos_offset + v3(0.f, 0.f, 0.1f), text_color, font_size, font);
					}
					if (this->State == UIState_Selecting) {
						pos_offset.y += this->element_size.y + element_offset;

						int cpt = 0;
						for (ListNode<BaseObject> *c_node = element_list->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
							BaseObject* current_ui_element = c_node->GetData();

							if (selected_index == cpt) {
								renderer->ui_panel_Mesh->Render(pos_offset, this->Size, v4(0.1f, 0.4f, 0.0f, rel_alpha));
								renderer->RenderUIText(current_ui_element->Get_Name()->CharAt(), pos_offset + v3(0.f, 0.f, 0.1f), text_color, font_size, font);
							}
							else {
								renderer->ui_panel_Mesh->Render(pos_offset, this->Size, back_color);
								renderer->RenderUIText(current_ui_element->Get_Name()->CharAt(), pos_offset + v3(0.f, 0.f, 0.1f), text_color, font_size, font);
							}

							pos_offset.y += this->element_size.y + element_offset;
							cpt++;
						}

					}
				}
			}
			virtual bool PGUISelectBox::Update(Controler *controler, double timeElapse, v3* mouse_ui_possition) {
				bool isChildActive = PGBaseUIElement::Update(controler, timeElapse, mouse_ui_possition);
				if (isChildActive == false) {
					switch (this->State) {
					case UIState_Hot:{
										 if (controler->IsPressed(PGMouse_Right) == true) {
											 this->State = UIState_Selecting;
										 }
										 break;
					}
					case UIState_Selecting:{
											   if (controler->IsPressed(PGMouse_Left) == true) {
												   if (this->IsIntersection(mouse_ui_possition)) {
													   this->State = UIState_Hot;
												   }
												   else {
													   this->State = UIState_Idle;
												   }
												   this->EmiteEvent(new PGUIEvent(this, UIEvent_Button_Press));
											   }
											   break;
					}
					}
				}
				return isChildActive;
			}
		};





		class PGUIMenuWindow : public PGBaseUIElement {
		protected:
			r32 menu_button_default_size = 16.f;
		private:
			PGUIMargin* Menu_Margin;
			PGUIPanel* Main_Panel;
			PGUIButton * Hide_Button;
			PGUILabel * Title_Label;
			bool IsMovable;
			bool IsResizable;
		public:
			PGUIMenuWindow() {
				this->IsMovable = true;
				this->IsResizable = true;

				this->Menu_Margin = new PGUIMargin(5.f, 5.f, 32.f, 5.f);

				this->Main_Panel = new PGUIPanel();
				this->Main_Panel->SetPossition(v2(0.f, 0.f));
				this->Main_Panel->background_color = v3(0.3f, 0.3f, 0.3f);

				this->Hide_Button = new PGUIButton();
				this->Hide_Button->SetSize(v2(menu_button_default_size));
				this->Hide_Button->SetPossition(v2(0.f, 0.f));
				this->Hide_Button->AddListener(this);

				this->Title_Label = new PGUILabel();
				this->Title_Label->SetPossition(v2(3.f, 3.f));
				this->Title_Label->Text_Size = 0.5f;

				PGBaseUIElement::AddChild(Main_Panel);
				PGBaseUIElement::AddChild(Hide_Button);
				PGBaseUIElement::AddChild(Title_Label);
			}
			~PGUIMenuWindow() {
				delete(Main_Panel);
				delete(Hide_Button);
				delete(Title_Label);
				delete(Menu_Margin);
			}
			virtual void PGUIMenuWindow::Render(BaseRenderer *renderer) override {
				if (this->IsVisible == true) {

					if (this->State != UIState_Idle) {
						this->Opacity = 1.f;
					}
					else {
						this->Opacity = 0.7f;
					}
					renderer->ui_panel_Mesh->Render(v3(this->GetRelativePossition(), 0.f), this->Size, v4(v3(0.2f, 0.2f, 0.2f), this->GetRelativeOpacity()));
					PGBaseUIElement::Render(renderer);
				}

			}
			virtual bool PGUIMenuWindow::Update(Controler *controler, double timeElapse, v3 *mouse_ui_possition) {
				bool isChildActive = false;
				if (this->State != UIState_Moving) {
					isChildActive = PGBaseUIElement::Update(controler, timeElapse, mouse_ui_possition);
				}
				if (isChildActive == false) {
					switch (this->State) {
					case UIState_Hot:{
										 if (this->IsMovable == true && controler->IsPressed(PGMouse_Right) == true) {
											 this->State = UIState_Moving;
										 }
										 break; }
					case UIState_Moving:{
											this->Possition.x = this->Possition.x + controler->DeltaPossition.x;
											this->Possition.y = this->Possition.y + controler->DeltaPossition.y;
											if (controler->IsRelease(PGMouse_Right) == true || controler->GetKey(PGMouse_Right)->IsPress == false) {
												if (this->IsIntersection(mouse_ui_possition)) {
													this->State = UIState_Hot;
												}
												else {
													this->State = UIState_Idle;
												}
											}
											break; }
					}
				}
				return isChildActive;
			}
			void PGUIMenuWindow::SetSize(v2 size) override {
				PGBaseUIElement::SetSize(size);

				//Align-other thing
				this->Main_Panel->SetSize(v2(size.x - this->Menu_Margin->Right - this->Menu_Margin->Left, size.y - this->Menu_Margin->Bottom - this->Menu_Margin->Top));
				this->Main_Panel->SetPossition(v2(this->Menu_Margin->Left, this->Menu_Margin->Top));

				this->Hide_Button->SetPossition(v2(size.x - menu_button_default_size - this->Menu_Margin->Right, this->Menu_Margin->Top / 2.f - menu_button_default_size / 2.f));
			}
			void PGUIMenuWindow::SetMenuTitle(char* title, Font* title_font, v3 title_color) {
				this->Title_Label->SetText(title);
				this->Title_Label->SetFont(title_font);
				this->Title_Label->Text_Color = title_color;
			}
			void PGUIMenuWindow::AddChild(PGBaseUIElement* child_element) override {
				Main_Panel->AddChild(child_element);
			}
			virtual void PGUIMenuWindow::OnEvent(PGUIEvent *event) {
				PGEventListener::OnEvent(event);
				if (event->sender == this->Hide_Button) {
					if (event->code == UIEvent_Button_Release) {
						this->IsVisible = false;
					}
				}


			}
		};
	}
}
#endif 