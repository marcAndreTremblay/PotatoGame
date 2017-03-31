#if !defined(PG_PANEL_H)
#define PG_PANEL_H




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

		class Panel : public UIElement {
		protected:
		private:
		public:
			v3 background_color;
			Panel() {
				this->background_color = v3(0.5f);
			}
			~Panel() {

			}
			virtual bool Panel::IsActif() override {
				return false;
			}
			virtual void Panel::Render(BaseRenderer *renderer) override {
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
				UIElement::Render(renderer);
			}
			virtual bool Panel::Update(Controler *controler, double timeElapse, v3 *mouse_ui_possition) {
				bool isChildActive = UIElement::Update(controler, timeElapse, mouse_ui_possition);
				if (isChildActive == false) {

				}
				return isChildActive;
			}
		};
	}
}
#endif