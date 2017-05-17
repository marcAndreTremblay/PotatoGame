#if !defined(IANIMATION_H)
#define IANIMATION_H

/*	Interface 
	Generic Animation in the engine*/
class IAnimation {
	IAnimation();
	~IAnimation();
	void Update(double delta_time);
};

#endif 