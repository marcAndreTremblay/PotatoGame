#if !defined(PG_BASE_OBJECT_H)
#define PG_BASE_OBJECT_H

#include "PGString.h"
using namespace PG::Core;

namespace PG {
	namespace Engine {
		class PGBaseObject {
		protected:
			unsigned int Ref_Id;
			Str *Ref_Name;
		private:
		public:
			PGBaseObject() {
				this->Ref_Id = UINT_MAX;
				this->Ref_Name = nullptr;

			}
			~PGBaseObject() {
				delete(this->Ref_Name);
			}

			void PGBaseObject::Set_Id(int id) {
				this->Ref_Id = id;
			}
			void PGBaseObject::Set_Name(char* name) {
				this->Ref_Name = new Str(name);
			}

			int PGBaseObject::Get_Id() {
				return Ref_Id;
			}
			Str* PGBaseObject::Get_Name() {
				return this->Ref_Name;
			}
			bool PGBaseObject::Compare_ptr(PGBaseObject* other) {
				return (this == (void*)other);
			}
			bool PGBaseObject::Compare_Id(PGBaseObject* other) {
				if (this->Ref_Id != UINT_MAX && other->Ref_Id != UINT_MAX) {
					return (this->Ref_Id == other->Ref_Id);
				}
				return false;
			}
			bool PGBaseObject::Compare_Id(unsigned int id) {
				if (this->Ref_Id != UINT_MAX && id != UINT_MAX) {
					return (this->Ref_Id == id);
				}
				return false;
			}
			bool PGBaseObject::Compare_Name(PGBaseObject* other) {
				if (this->Ref_Name != nullptr && other->Ref_Name != nullptr) {
					return (this->Ref_Name->Compare(other->Ref_Name));
				}
				return false;
			}
			bool PGBaseObject::Compare_Name(char* name) {
				if (this->Ref_Name != nullptr) {
					return (this->Ref_Name->Compare(new Str(name)));
				}
				return false;
			}
			bool PGBaseObject::Compare_Name(Str* name) {
				if (this->Ref_Name != nullptr) {
					return (this->Ref_Name->Compare(name));
				}
				return false;
			}
		};
	}
}
#endif 