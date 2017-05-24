#if !defined(PG_GAME_ENTITY_H)
#define PG_GAME_ENTITY_H

#include "stdafx.h"

#include "IAnimation.h"

#include "Core.h"
#include "List.h"
#include "EngineObject.h"
using namespace PG::Core;



namespace PG {
	namespace Engine {
		class Entity : public EngineObject {
		protected:
			IAnimation* Animation_Component; //Owned
		private:
		public:
			v3 World_Possition;
			Entity() :
				EngineObject() {
				Animation_Component = nullptr;
			}
			virtual ~Entity() {
				delete(Animation_Component);
			}
			void SetAnimation(IAnimation* animation) {
				Animation_Component = animation;
			}
			virtual void Entity::Render() {

			}
			virtual void Entity::Update() {

			}
		};
	}
}
#endif
