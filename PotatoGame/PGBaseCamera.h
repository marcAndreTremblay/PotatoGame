#if !defined(PG_BASE_CAMERA_H)
#define PG_BASE_CAMERA_H


#include "stdafx.h"

#include "PGCore.h"
using namespace PGCore;

namespace PGEngine {
	class PGBaseCamera {
	protected:
	private:
	public:
		v3 Possition;
		v3 LookAt;
		v3 Up;
		PGBaseCamera(v3 possition, v3 look_at, v3 up) {
			this->Possition = possition;
			this->LookAt = look_at;
			this->Up = up;
		}
		~PGBaseCamera() {

		}
		m4 PGBaseCamera::GetViewMatrice() {
			return glm::lookAt(
				this->Possition, // Camera is at
				this->LookAt, // and looks at
				this->Up  // Head is up 
				);
		}
		void PGBaseCamera::RotateZAxis(r32 rad_angle, v3 origin) {
			r32 tempoX = this->Possition.x;
			r32 tempoY = this->Possition.y;
			this->Possition.x = ((tempoX - origin.x) * cosf(rad_angle) - (tempoY - origin.y)* sinf(rad_angle)) + origin.x;
			this->Possition.y = ((tempoY - origin.y) * cosf(rad_angle) + (tempoX - origin.x) * sinf(rad_angle)) + origin.y;
		}
		void PGBaseCamera::RotateXAxis(r32 rad_angle, v3 origin) {
			r32 tempoZ = this->Possition.z;
			r32 tempoY = this->Possition.y;
			this->Possition.z = ((tempoZ - origin.z) * cosf(rad_angle) - (tempoY - origin.y)* sinf(rad_angle)) + origin.z;
			this->Possition.y = ((tempoY - origin.y) * cosf(rad_angle) + (tempoZ - origin.z) * sinf(rad_angle)) + origin.y;
		}
		void PGBaseCamera::RotateYAxis(r32 rad_angle, v3 origin) {
			r32 tempoZ = this->Possition.z;
			r32 tempoX = this->Possition.x;
			this->Possition.z = ((tempoZ - origin.z) * cosf(rad_angle) - (tempoX - origin.y)* sinf(rad_angle)) + origin.z;
			this->Possition.x = ((tempoX - origin.x) * cosf(rad_angle) - (tempoX - origin.y)* sinf(rad_angle)) + origin.x;
		}

	};

}
#endif