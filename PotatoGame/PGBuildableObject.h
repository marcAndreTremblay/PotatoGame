#if !defined(PG_BUILDABLE_OBJECT_H)
#define PG_BUILDABLE_OBJECT_H

namespace PGEngine {

	class PGBuildableObject {
		protected:
			bool IsObjectBuild;
			bool IsObjLock;
			//Note(Marc): Maybe we should make those method call StartAsycBuild and EndAsycBuild and only be call by the thread building the object? 
			void PGBuildableObject::StartBuilding() {
				this->IsObjLock = true;
			}
			void PGBuildableObject::EndBuilding() {
				this->IsObjectBuild = true;
				this->IsObjLock = false;
			}
		private:
		public:
			PGBuildableObject() {
				this->IsObjectBuild = false;	
				this->IsObjLock = false;
			}
			~PGBuildableObject() {

			} 
			bool PGBuildableObject::IsBuild() { return this->IsObjectBuild; }
			bool PGBuildableObject::IsLock() { return this->IsObjLock; }
			virtual void PGBuildableObject::Build() {};
	};

}
#endif