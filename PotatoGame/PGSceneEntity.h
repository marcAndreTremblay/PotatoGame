#if !defined(PG_GAME_ENTITY_H)
#define PG_GAME_ENTITY_H

#include "stdafx.h"

#include "PGCore.h"
#include "PGBaseObject.h"
using namespace PGCore;

namespace PGEngine{
	class PGSceneEntity : public PGBaseObject{
	protected:
		v3 Possition;
	private:
	public:
		PGSceneEntity() :
			PGBaseObject(){
			
		}
		~PGSceneEntity() {

		}

		virtual void PGSceneEntity::Render() {
		
		}
		virtual void PGSceneEntity::Update() {

		}
	};
}
#endif
