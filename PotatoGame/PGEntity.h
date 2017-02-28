#if !defined(PG_GAME_ENTITY_H)
#define PG_GAME_ENTITY_H

#include "stdafx.h"

#include "PGCore.h"
#include "PGBaseObject.h"
using namespace PGCore;

namespace PGEngine{
	class PGEntity : public PGBaseObject{
	protected:
		v3 World_Possition;
	private:
	public:
		PGEntity() :
			PGBaseObject(){
			
		}
		~PGEntity() {

		}

		virtual void PGEntity::Render() {
		
		}
		virtual void PGEntity::Update() {

		}
	};
}
#endif
