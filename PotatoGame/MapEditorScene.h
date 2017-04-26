#if !defined(Map_Editor_SCENE_H)
#define Map_Editor_SCENE_H

#include "Core.h"
#include "BaseRenderer.h"	
#include "Scene.h"
#include "Controler.h"
#include "Entity.h"
#include "String.h"
#include "Scene.h"
#include "BuildableObject.h"
#include "PGMapGrid.h"
#include "MousePicker.h"

#include "PGBackgroundMapGridMesh.h"
#include "PGMapAtlas.h"


class MapEditorScene :
	public Scene {
private:
	PGMapAtlas * test_atlas;
	PGAtlasRegion* region_display[9];
	bool region_edited[9];

	PGLight scene_light;
	RawModelData *test_model;
	RawModelData *test_model2;
	RawModelData *test_model3;
	double time;
	double tempo_var;
public:
	MapEditorScene();
	virtual ~MapEditorScene();
	void Update(Controler *controler, double timeElapse);
	void Render(BaseRenderer *renderer);
	void Build(MousePicker* mouse_picker);
	void HandleControler(Controler *controler);
};
#endif

