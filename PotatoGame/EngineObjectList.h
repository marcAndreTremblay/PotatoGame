#if !defined(PG_BASE_OBJ_LIST_H)
#define PG_BASE_OBJ_LIST_H

#include "String.h"
#include "List.h"
#include "EngineObject.h"

using namespace PG::Core;

namespace PG {
	namespace Engine {
		template <class EngineObject>
		class EngineObjectList :public List<EngineObject> {
		public:
			EngineObjectList(bool managing = false) : List(managing) {

			}
			~EngineObjectList() {

			}

			void Add(EngineObject* element) override {
				List::Add(element);
			}
			EngineObject* EngineObjectList::FindById(unsigned int id)  {
				for (ListNode<EngineObject> *c_node = this->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
					EngineObject* current_obj = c_node->GetData();
					if (c_node->GetData()->Compare_Id(id) == true) {
						return c_node->GetData();
					}
				}
				return nullptr;
			}
			EngineObject* EngineObjectList::FindByName(char *name) {
				Str* new_string = new Str(name);
				for (ListNode<EngineObject> *c_node = this->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
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
}

#endif