#if !defined(PG_BASE_OBJ_LIST_H)
#define PG_BASE_OBJ_LIST_H

#include "String.h"
#include "List.h"
#include "BaseObject.h"

using namespace PG::Core;

namespace PG {
	namespace Engine {
		template <class BaseObject>
		class ObjectList :public List<BaseObject> {
		public:
			ObjectList(bool managing = false) : List(managing) {

			}
			~ObjectList() {

			}

			void Add(BaseObject* element) override {
				List::Add(element);
			}

			BaseObject* ObjectList::FindById(unsigned int id) {
				for (ListNode<BaseObject> *c_node = this->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
					BaseObject* current_obj = c_node->GetData();
					if (c_node->GetData()->Compare_Id(id) == true) {
						return c_node->GetData();
					}
				}
				return nullptr;
			}
			BaseObject* ObjectList::FindByName(char *name) {
				Str* new_string = new Str(name);
				for (ListNode<BaseObject> *c_node = this->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
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