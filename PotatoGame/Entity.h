#if !defined(PG_GAME_ENTITY_H)
#define PG_GAME_ENTITY_H

#include "stdafx.h"

#include "Core.h"
#include "BaseObject.h"
using namespace PG::Core;

namespace PG {
	namespace Engine {
		class Entity : public BaseObject {
		protected:
			v3 World_Possition;
		private:
		public:
			Entity() :
				BaseObject() {

			}
			virtual ~Entity() {

			}

			virtual void Entity::Render() {

			}
			virtual void Entity::Update() {

			}
		};
	}
}
#endif
