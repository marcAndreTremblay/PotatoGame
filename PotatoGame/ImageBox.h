#if !defined(PG_IMAGE_BOX_H)
#define PG_IMAGE_BOX_H

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
		class ImageBox : public UIElement {
		protected:
		private:
		public:
			Texture* Image;
			v3 Color_Channel;
			ImageBox() {
				this->Color_Channel = v3(1.f);
				this->Image = nullptr;
				this->IsVisible = true;
			}
			~ImageBox() {

			}
			virtual void ImageBox::Render(BaseRenderer *renderer) override {
				if (this->IsVisible == true) {
					renderer->ui_image_mesh->Render(v3(this->GetRelativePossition(), this->GetRelativeZ()), this->Size, this->Image, v4(this->Color_Channel, this->GetRelativeOpacity()));
				}
			}
			virtual bool ImageBox::Update(Controler *controler, double timeElapse, v3 *mouse_ui_possition) {
				bool isChildActive = UIElement::Update(controler, timeElapse, mouse_ui_possition);

				return isChildActive;
			}
			bool ImageBox::IsActif() override {
				return false;
			}
		};
	}
}
#endif