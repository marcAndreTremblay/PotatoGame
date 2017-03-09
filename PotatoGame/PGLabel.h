#if !defined(PG_UI_LABEL_H)
#define PG_UI_LABEL_H

#include "PGUICore.h"
#include "PGUIBaseElement.h"


class PGUILabel : public PGBaseUIElement {
protected:
private:
	PGString* Text;
	PGFont* Font; //Un-managed resource
public:
	v3 Text_Color;
	r32 Text_Size;
	PGUILabel() {
		this->Text = nullptr;
		this->Font = nullptr;
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
		this->Text = new PGString(text);
	}
	void PGUILabel::SetFont(PGFont* font) {
		this->Font = font;
	}

	virtual void PGUILabel::Render(PGBaseRenderer *renderer) override {
		if (this->IsVisible == true && this->Text != nullptr && this->Font != nullptr) {
			v2 box = v2();
			Font->GetFontBondingBox(this->Text->GetCharPtr(), Text_Size, &box);

			renderer->RenderUIText(this->Text->GetCharPtr(), v3(this->GetRelativePossition(), this->GetRelativeZ()), v4(this->Text_Color, this->GetRelativeOpacity()), this->Text_Size, this->Font);
			//renderer->ui_panel_Mesh->Render(v3(this->GetRelativePossition(), this->GetRelativeZ()), box, v4(1.f, 1.f, 0.f, 1.f));
		}
	}
	virtual bool PGUILabel::Update(PGControler *controler, double timeElapse, v3 *mouse_ui_possition) {
		return PGBaseUIElement::Update(controler, timeElapse, mouse_ui_possition);
	}
	virtual bool PGUILabel::IsActif() override {
		return false;
	}
};
#endif