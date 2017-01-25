#if !defined(PG_MOUSE_PICKER_H)
#define PG_MOUSE_PICKER_H


#include "PGGameWindow.h"
#include "PGControler.h"

using namespace PGEngine;



class PGMousePicker {
private:
	PGGameWindow* GamewWindow; //Ref 
protected:
public:
	v3 PGMousePicker::TranformWindowStoUIS(PGControler* controler, m4* projection_matrix) {
		float x = (2.0f * (float)controler->xpos) / this->GamewWindow->GetWidth() - 1.0f;
		float y = 1.0f - (2.0f * (float)controler->ypos) / this->GamewWindow->GetHeight();
		v3 ray_nds = v3(x, y, -1.f);

		v4 ray_clip = v4(ray_nds, 1.0);
		v4 ray_eye = inverse(*projection_matrix) * ray_clip;

		return v3(ray_eye.x, ray_eye.y, 0);
	}
	v3 PGMousePicker::CastRay(PGControler* controler, m4* projection_matrix, m4* view_matrix)	 {
		float x_nds ((2.0f * (float)controler->xpos) / this->GamewWindow->GetWidth() - 1.f);
		float y_nds = 1.0f - ((2.0f * (float)controler->ypos) / this->GamewWindow->GetHeight());
	
		v3 ray_nds = v3(x_nds, y_nds, -1.f);
		v4 ray_clip = v4(ray_nds, 1.0);
		
		v4 ray_eye = inverse(*projection_matrix) * ray_clip;
		ray_eye.z = -1.f;
		ray_eye.w = 0.f; //Note(marc): this need to be 0
		v3 ray_wor = glm::normalize(v3(inverse(*view_matrix) * ray_eye));
		return ray_wor;
	}
	PGMousePicker(PGGameWindow* target_game_window) {
		GamewWindow = target_game_window;
	}
	~PGMousePicker() {

	}
};
#endif