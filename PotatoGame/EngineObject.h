#if !defined(PG_BASE_OBJECT_H)
#define PG_BASE_OBJECT_H

#include "String.h"
using namespace PG::Core;

namespace PG {
	namespace Engine {
		class EngineObject {
		protected:
			unsigned int Ref_Id;
			Str *Ref_Name;
		private:
		public:
			EngineObject() {
				this->Ref_Id = UINT_MAX;
				this->Ref_Name = nullptr;

			}
			virtual ~EngineObject() {
				delete(this->Ref_Name);
			}

			void EngineObject::Set_Id(int id) {
				this->Ref_Id = id;
			}
			void EngineObject::Set_Name(char* name) {
				this->Ref_Name = new Str(name);
			}

			int EngineObject::Get_Id() {
				return Ref_Id;
			}
			Str* EngineObject::Get_Name() {
				return this->Ref_Name;
			}
			bool EngineObject::Compare_ptr(EngineObject* other) {
				return (this == (void*)other);
			}
			bool EngineObject::Compare_Id(EngineObject* other) {
				if (this->Ref_Id != UINT_MAX && other->Ref_Id != UINT_MAX) {
					return (this->Ref_Id == other->Ref_Id);
				}
				return false;
			}
			bool EngineObject::Compare_Id(unsigned int id) {
				if (this->Ref_Id != UINT_MAX && id != UINT_MAX) {
					return (this->Ref_Id == id);
				}
				return false;
			}
			bool EngineObject::Compare_Name(EngineObject* other) {
				if (this->Ref_Name != nullptr && other->Ref_Name != nullptr) {
					return (this->Ref_Name->Compare(other->Ref_Name));
				}
				return false;
			}
			bool EngineObject::Compare_Name(char* name) {
				if (this->Ref_Name != nullptr) {
					return (this->Ref_Name->Compare(new Str(name)));
				}
				return false;
			}
			bool EngineObject::Compare_Name(Str* name) {
				if (this->Ref_Name != nullptr) {
					return (this->Ref_Name->Compare(name));
				}
				return false;
			}
		};
	}
}
#endif 