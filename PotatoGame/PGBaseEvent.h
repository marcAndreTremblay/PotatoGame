#if !defined(PG_EVENT_H)
#define PG_EVENT_H

#include "PGCore.h"
#include "PGLinkedList.h"
#include "PGString.h"

using namespace PGCore;

namespace PGEngine{
	enum PGEventType {
		GameEvent_ExitGame
	};

	class PGBaseEvent {
		protected:
		private:
			bool IsUnique; //True if the event should be unique in the WorkGroup
			bool UniqueHandle;//True if the event should be handle only once then remove 
			bool IsHandle; //Is the event been handle at least once	
		public:
			PGEventType type;
			double LifeTime;//Max time the event will be alive in the WorkGroup remove when < 0
			PGBaseEvent(bool isUnique, bool uniqueHandle, bool lifeTime = 0) {
				this->IsHandle = false;
				this->IsUnique = isUnique;
				this->LifeTime = lifeTime;
				this->UniqueHandle = uniqueHandle;
			}
			~PGBaseEvent() {

			}
			bool PGBaseEvent::ShouldBeRemove() {
				if (this->IsUnique == true && this->IsHandle == true) return true;
				if (this->LifeTime < 0) return true;
			return false;
		}
	};


	class PGEventWorkGroup {
		protected:
		private:

			PGLinkedList<PGBaseEvent>* EventList;
		public:
			PGString* Ref_Name;
			PGEventWorkGroup(char *ref_name = nullptr) {
				if (ref_name != nullptr) {
					this->Ref_Name = new PGString(ref_name);
				}
				this->EventList = new PGLinkedList<PGBaseEvent>();
			}
			~PGEventWorkGroup() {
				delete(Ref_Name);
				delete(EventList);
			}
			void PGEventWorkGroup::UpdateAndRecycle(double deltatime) {
				for (PGListNode<PGBaseEvent> *c_node = EventList->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
					PGBaseEvent* current_event = c_node->GetData();
					if (current_event->LifeTime > 0) {
						current_event->LifeTime -= deltatime;
					}
					if (current_event->ShouldBeRemove() == true) {
						EventList->Remove(current_event);
					}
				}
			}
			void PGEventWorkGroup::Push(PGBaseEvent *new_event) {
				if (new_event != nullptr) {
					EventList->Add(new_event);
				}
			}
			PGBaseEvent* PGEventWorkGroup::Pool(PGEventType type_to_pool) {
			for (PGListNode<PGBaseEvent> *c_node = EventList->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
				PGBaseEvent* current_event = c_node->GetData();
				if (current_event->type == type_to_pool) {
					return current_event;
				}
			}
			return nullptr;
		}
	};


	class PGEventManager {
		protected:
		private:
			PGLinkedList<PGEventWorkGroup>* WorkGroups;
		public:
			PGEventManager() {
				WorkGroups = new PGLinkedList<PGEventWorkGroup>();
			}
			~PGEventManager() {
				delete(WorkGroups);
			}
			PGEventWorkGroup* PGEventManager::AddWorkGroup(char *Ref_Name) {
				WorkGroups->Add(new PGEventWorkGroup(Ref_Name));
				return this->FindWorkGroup(Ref_Name);
			}
			void PGEventManager::UpdateAndRecycle(double deltatime) {
				for (PGListNode<PGEventWorkGroup> *c_node = WorkGroups->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
					c_node->GetData()->UpdateAndRecycle(deltatime);
				}
			}
			PGEventWorkGroup* PGEventManager::FindWorkGroup(char *Ref_Name) {
			PGString* Ref_Name_ptr = new PGString(Ref_Name);
			for (PGListNode<PGEventWorkGroup> *c_node = WorkGroups->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
				PGEventWorkGroup* current = c_node->GetData();
				if (current->Ref_Name->Compare(Ref_Name_ptr) == true) {
					return current;
				}
			}
			return nullptr;
		}
	};

}
#endif