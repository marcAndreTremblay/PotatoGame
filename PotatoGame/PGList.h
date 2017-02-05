#if !defined(PG_LIST_H)
#define PG_LIST_H



namespace PGCore {
	template <class T>
	class PGListNode {
	private:
		T* element;
		PGListNode<T>* next;
	public:
		PGListNode(T* _element) {
			this->element = _element;
			this->next = nullptr;
		}
		~PGListNode() {
		}
		T* PGListNode::GetData() { return this->element; }
		PGListNode* PGListNode::GetNext() { return this->next; }
		void PGListNode::SetNext(PGListNode* _next) { this->next = _next; }
	};


	template <class T>
	class PGLList {
	private:
		/* Variable */
		PGListNode<T>* head;
		PGListNode<T>* tail;
		int element_count;
		bool managing_object;
	public:
		/* Variable */
		/* Constructors */
		PGLList(bool manage_obj = false) {
			this->managing_object = manage_obj;
			this->element_count = 0;
			this->head = nullptr;
			this->tail = nullptr;
		}
		~PGLList() {
			PGListNode<T>* next_node = head;
			while (next_node != nullptr) {
				PGListNode<T>* current_node = next_node;
				next_node = current_node->GetNext();
				if (this->managing_object == true) {
					delete(current_node->GetData());
				}
				delete(current_node);
			}
		}
		/* Functions */
		PGListNode<T>* PGLList::GetHead() {
			return this->head;
		}
		virtual void PGLList::Add(T* new_element) {
			PGListNode<T> *new_node = new PGListNode<T>(new_element);
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
		void PGLList::Clear() {
			PGListNode<T>* old_head = this->head;
			this->head = nullptr;
			this->tail = nullptr;
			this->element_count = 0;
			//Todo(Marc): Check if this is clean
			
			while (old_head != nullptr) {
				PGListNode<T>* current_node = old_head;
				old_head = current_node->GetNext();
				if (this->managing_object == true) {
					delete(current_node->GetData());
				}
				delete(current_node);
			}
		}
		void PGLList::Remove(T* target_element) {
			PGListNode<T>* last_visited_node = this->head;
			PGListNode<T>* current_node = this->head;
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

	};



}
#endif