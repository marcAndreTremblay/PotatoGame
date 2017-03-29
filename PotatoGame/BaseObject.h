#if !defined(PG_BASE_OBJECT_H)
#define PG_BASE_OBJECT_H

#include "String.h"
using namespace PG::Core;

namespace PG {
	namespace Engine {
		class BaseObject {
		protected:
			unsigned int Ref_Id;
			Str *Ref_Name;
		private:
		public:
			BaseObject() {
				this->Ref_Id = UINT_MAX;
				this->Ref_Name = nullptr;

			}
			~BaseObject() {
				delete(this->Ref_Name);
			}

			void BaseObject::Set_Id(int id) {
				this->Ref_Id = id;
			}
			void BaseObject::Set_Name(char* name) {
				this->Ref_Name = new Str(name);
			}

			int BaseObject::Get_Id() {
				return Ref_Id;
			}
			Str* BaseObject::Get_Name() {
				return this->Ref_Name;
			}
			bool BaseObject::Compare_ptr(BaseObject* other) {
				return (this == (void*)other);
			}
			bool BaseObject::Compare_Id(BaseObject* other) {
				if (this->Ref_Id != UINT_MAX && other->Ref_Id != UINT_MAX) {
					return (this->Ref_Id == other->Ref_Id);
				}
				return false;
			}
			bool BaseObject::Compare_Id(unsigned int id) {
				if (this->Ref_Id != UINT_MAX && id != UINT_MAX) {
					return (this->Ref_Id == id);
				}
				return false;
			}
			bool BaseObject::Compare_Name(BaseObject* other) {
				if (this->Ref_Name != nullptr && other->Ref_Name != nullptr) {
					return (this->Ref_Name->Compare(other->Ref_Name));
				}
				return false;
			}
			bool BaseObject::Compare_Name(char* name) {
				if (this->Ref_Name != nullptr) {
					return (this->Ref_Name->Compare(new Str(name)));
				}
				return false;
			}
			bool BaseObject::Compare_Name(Str* name) {
				if (this->Ref_Name != nullptr) {
					return (this->Ref_Name->Compare(name));
				}
				return false;
			}
		};
	}
}
#endif 