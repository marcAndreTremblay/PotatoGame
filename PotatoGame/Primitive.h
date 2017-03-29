#if !defined(PG_3D_PRIMITIVE_H)
#define PG_3D_PRIMITIVE_H

#include "Core.h"


namespace PG {
	namespace Core {
		class PGPlane {
		private:
		protected:
		public:
			v3 Point;
			v3 Normal;
			PGPlane(v3 point, v3 normal) {
				this->Normal = normal;
				this->Point = point;
			}
			~PGPlane() {

			}
		};
		class PGRay {
		private:
		protected:
		public:
			v3 Origin;
			v3 Normal;
			PGRay(v3 origin, v3 normal) {
				this->Normal = normal;
				this->Origin = origin;
			}
			~PGRay() {

			}
		};
	}
}
#endif