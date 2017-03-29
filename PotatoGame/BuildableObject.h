#if !defined(PG_BUILDABLE_OBJECT_H)
#define PG_BUILDABLE_OBJECT_H

namespace PG {
	namespace Engine {

		class BuildableObject {
		protected:
			bool IsObjectBuild;
			bool IsObjLock;
			//Note(Marc): Maybe we should make those method call StartAsycBuild and EndAsycBuild and only be call by the thread building the object? 
			void BuildableObject::StartBuilding() {
				this->IsObjLock = true;
			}
			void BuildableObject::EndBuilding() {
				this->IsObjectBuild = true;
				this->IsObjLock = false;
			}
		private:
		public:
			BuildableObject() {
				this->IsObjectBuild = false;
				this->IsObjLock = false;
			}
			~BuildableObject() {

			}
			bool BuildableObject::IsBuild() { return this->IsObjectBuild; }
			bool BuildableObject::IsLock() { return this->IsObjLock; }
			virtual void BuildableObject::Build() {};
		};

	}
}

#endif