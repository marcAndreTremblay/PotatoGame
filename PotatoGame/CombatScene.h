#if !defined(COMBAT_SCENE_H)
#define COMBAT_SCENE_H


#include "Core.h"
#include "Scene.h"
#include "BaseRenderer.h"	
#include "Controler.h"
#include "Entity.h"

class CombatScene :	public Scene {
public:
	CombatScene(MousePicker* mouse_picker);
	virtual ~CombatScene();
	virtual void Update(Controler *controler, double timeElapse);
	virtual void Render(BaseRenderer *renderer);
	virtual void Build();
	void HandleControler(Controler *controler);
	
};
#endif

