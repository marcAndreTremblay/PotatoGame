#if !defined(PG_LIST_H)
#define PG_LIST_H



namespace PG {
	namespace Core {
		template <class T>
		class ListNode {
		private:
			T* element;
			ListNode<T>* next;
		public:
			ListNode(T* _element) {
				this->element = _element;
				this->next = nullptr;
			}
			~ListNode() {
			}
			T* ListNode::GetData() { return this->element; }
			ListNode* ListNode::GetNext() { return this->next; }
			void ListNode::SetNext(ListNode* _next) { this->next = _next; }
		};


		template <class T>
		class List {
		private:
			/* Variable */
			ListNode<T>* head;
			ListNode<T>* tail;
			bool managing_object;
		public:
			/* Variable */
			int element_count;
			/* Constructors */
			List(bool manage_obj = false) {
				this->managing_object = manage_obj;
				this->element_count = 0;
				this->head = nullptr;
				this->tail = nullptr;
			}
			~List() {
				ListNode<T>* next_node = head;
				while (next_node != nullptr) {
					ListNode<T>* current_node = next_node;
					next_node = current_node->GetNext();
					if (this->managing_object == true) {
						delete(current_node->GetData());
					}
					delete(current_node);
				}
			}
			/* Functions */
			ListNode<T>* List::GetHead() {
				return this->head;
			}
			virtual void List::Add(T* new_element) {
				ListNode<T> *new_node = new ListNode<T>(new_element);
				this->element_count++;
				if (head == nullptr) {
					this->head = new_node;
					this->tail = this->head;
				}
				else {
					this->tail->SetNext(new_node);
					this->tail = new_node;
				}
			}
			void List::Clear() {
				ListNode<T>* old_head = this->head;
				this->head = nullptr;
				this->tail = nullptr;
				this->element_count = 0;
				//Todo(Marc): Check if this is clean

				while (old_head != nullptr) {
					ListNode<T>* current_node = old_head;
					old_head = current_node->GetNext();
					if (this->managing_object == true) {
						delete(current_node->GetData());
					}
					delete(current_node);
				}
			}
			void List::Remove(T* target_element) {
				ListNode<T>* last_visited_node = this->head;
				ListNode<T>* current_node = this->head;
				while (current_node != nullptr) {
					if (current_node->GetData() == target_element) {
						last_visited_node->SetNext(current_node->GetNext());
						if (managing_object == true) {
							delete(current_node->GetData());
						}
						delete(current_node);
						element_count--;
					}
					last_visited_node = current_node;
					current_node = current_node->GetNext();
				}

			}
			T* List::GetAt(int target_index) {
				if (target_index < 0 || target_index > element_count) return nullptr;
				int cpt_index = 0;
				ListNode<T>* next_node = head;
				while (next_node != nullptr) {
					ListNode<T>* current_node = next_node;
					cpt_index++;
					if (cpt_index == target_index) {
						return current_node->GetData();
					}
					else {
						next_node = current_node->GetNext();
					}
				}
				return nullptr;
			}

		};



	}
}
#endif