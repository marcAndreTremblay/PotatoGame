#if !defined(PG_BASE_OBJ_LIST_H)
#define PG_BASE_OBJ_LIST_H

#include "PGString.h"
#include "PGList.h"
#include "PGBaseObject.h"

using namespace PGCore;

namespace PGEngine {
	template <class PGBaseObject>
	class PGBaseObjList :public PGList<PGBaseObject> {
		public:
			PGBaseObjList(bool managing = false) : PGList(managing) {

			}
			~PGBaseObjList() {
				
			}	

			void Add(PGBaseObject* element) override {
				PGList::Add(element);
			}

			PGBaseObject* PGBaseObjList::FindById(unsigned int id) {
				for (PGListNode<PGBaseObject> *c_node = this->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
					PGBaseObject* current_obj = c_node->GetData();
					if (c_node->GetData()->Compare_Id(id) == true) {
						return c_node->GetData();
					}
				}
				return nullptr;
			}
			PGBaseObject* PGBaseObjList::FindByName(char *name) {
				PGString* new_string = new PGString(name);
				for (PGListNode<PGBaseObject> *c_node = this->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {				
					if (c_node->GetData()->Compare_Name(new_string) == true) {
						delete(new_string);
						return c_node->GetData();
					}

				}
				delete(new_string);
				return nullptr;
			}
	};
}
#endif