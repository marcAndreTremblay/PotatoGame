#if !defined(PG_LABEL_H)
#define PG_LABEL_H




#include "String.h"
using namespace PG::Core;

#include "BaseRenderer.h"
#include "Font.h"
using namespace PG::Engine;

#include "GUICore.h"
#include "Controler.h"
#include "UIElement.h"

using namespace PG::Engine;
namespace PG {
	namespace GUI {
		class Label : public UIElement {
		public:
			Str* text;
			Font* font;
			v3 text_color;
			r32 text_scale;
			//Note(Marc): Eventualy add the possibility of a null font , when we render with no font we will use the renderer default font value 
			Label(Str* _text, Font* _font)  {
				text = _text;
				font = _font;
				this->text_color = v3(0.f);
				this->text_scale = 1.f;
			}
			Label()  {
				text = nullptr;
				font = nullptr;
				this->text_color = v3(0.f);
				this->text_scale = 1.f;
			}
			~Label() { delete(this->text); }
			virtual void Label::Render(BaseRenderer *renderer) {
				if (this->IsVisible == true && this->text != nullptr && this->font != nullptr) {
					v2 box = v2();
					font->GetFontBondingBox(this->text->CharAt(), text_scale, &box);
					renderer->RenderUIText(this->text->CharAt(), v3(this->GetRelativePossition(), this->GetRelativeZ()), v4(this->text_color, this->GetRelativeOpacity()), this->text_scale, this->font);
				}
			}
		};

	}
}

#endif