#if !defined(ANIMATOR_MANAGER_H)
#define ANIMATOR_MANAGER_H

//Core
#include "List.h"
using namespace PG::Core;
//Engine
#include "IAnimation.h"

class AnimatorManager {
	private:
		List<IAnimation>* animation_list;
	public:
		AnimatorManager();
		~AnimatorManager();
		void Update(double);
		void AttachAnimation(IAnimation *animation);
};
#endif

