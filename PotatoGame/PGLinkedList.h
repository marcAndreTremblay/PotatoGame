#if !defined(PG_LINKED_LIST_H)
#define PG_LINKED_LIST_H



namespace PGCore {

	template <class T>
	class PGList2Node {
	private:
		T element;
		PGList2Node<T>* next;
	public:
		PGList2Node(T _element) {
			this->element = _element;
			this->next = nullptr;
		}
		~PGList2Node() {
		}
		void PGList2Node::Clean() {
			delete(element);
		}
		T* PGList2Node::GetData() { return &this->element; }
		PGList2Node* PGList2Node::GetNext() { return this->next; }
		void PGList2Node::SetNext(PGList2Node* _next) { this->next = _next; }
	};
	template <class T>
	class PGLinked2List {
	private:
		/* Variable */
		PGList2Node<T>* head;
		PGList2Node<T>* tail;
		int element_count;
	public:
		/* Variable */
		/* Constructors */
		PGLinked2List(bool manage_obj = true) {
			this->element_count = 0;
			this->head = nullptr;
			this->tail = nullptr;
		}
		~PGLinked2List() {
			PGList2Node<T>* next_node = head;
			while (next_node != nullptr) {
				PGList2Node<T>* current_node = next_node;
				next_node = current_node->GetNext();
				delete(current_node);
			}
		}
		/* Functions */
		PGList2Node<T>* PGLinked2List::GetHead() {
			return this->head;
		}
		virtual void PGLinked2List::Add(T new_element) {
			PGList2Node<T> *new_node = new PGList2Node<T>(new_element);
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
		void PGLinked2List::Clean() {
			PGListNode<T>* old_head = this->head;
			this->head = nullptr;
			this->tail = nullptr;
			this->element_count = 0;

			while (old_head != nullptr) {
				PGListNode<T>* current_node = next_node;
				old_head = current_node->GetNext();
				delete(current_node);
			}
		}
		void PGLinked2List::Remove(T* target_element) {
			PGListNode<T>* last_visited_node = this->head;
			PGListNode<T>* current_node = this->head;
			while (current_node != nullptr) {
				if (current_node->GetData() == target_element) {
					last_visited_node->SetNext(current_node->GetNext());
					delete(current_node);
				}
				last_visited_node = current_node;
				current_node = current_node->GetNext();
			}
		}
	};





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
			delete(element);
		}
		T* PGListNode::GetData() { return this->element; }
		PGListNode* PGListNode::GetNext() { return this->next; }
		void PGListNode::SetNext(PGListNode* _next) { this->next = _next; }
	};


	template <class T>
	class PGLinkedList {
	private:
		/* Variable */
		PGListNode<T>* head;
		PGListNode<T>* tail;
		int element_count;
	public:
		/* Variable */
		/* Constructors */
		PGLinkedList(bool manage_obj = true) {
			this->element_count = 0;
			this->head = nullptr;
			this->tail = nullptr;
		}
		~PGLinkedList() {
			PGListNode<T>* next_node = head;
			while (next_node != nullptr) {
				PGListNode<T>* current_node = next_node;
				next_node = current_node->GetNext();
				delete(current_node);
			}
		}
		/* Functions */
		PGListNode<T>* PGLinkedList::GetHead() {
			return this->head;
		}
		virtual void PGLinkedList::Add(T* new_element) {
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
		void PGLinkedList::Clear() {
			PGListNode<T>* old_head = this->head;
			this->head = nullptr;
			this->tail = nullptr;
			this->element_count = 0;

			while (old_head != nullptr) {
				PGListNode<T>* current_node = next_node;
				old_head = current_node->GetNext();
				delete(current_node);
			}
		}
		void PGLinkedList::Remove(T* target_element) {
			PGListNode<T>* last_visited_node = this->head;
			PGListNode<T>* current_node = this->head;
			while (current_node != nullptr) {
				if (current_node->GetData() == target_element) {
					last_visited_node->SetNext(current_node->GetNext());
					delete(current_node);
				}
				last_visited_node = current_node;
				current_node = current_node->GetNext();
			}
		}
	};

}
#endif