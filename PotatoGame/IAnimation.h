#if !defined(IANIMATION_H)
#define IANIMATION_H


/*Interface Generic Animation in the engine*/
class IAnimation {
private:
protected:
public:
	IAnimation();
	virtual ~IAnimation();
	virtual void Update(double delta_time);
};



#endif 