#if !defined(IANIMATION_H)
#define IANIMATION_H

#include "Entity.h"

/*Interface Generic Animation in the engine*/
class IAnimation {
private:
	IAnimation();
public:
	virtual ~IAnimation();
	virtual void Update(double delta_time);

	
};



#endif 