#ifndef Map_Editor_SCENE_H
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

#include "GridRawDataV2.h"
#include "PGMapAtlas.h"
#include "HexaGridMapMesh.h"
#include "ModelRawDataV1.h"
#include "FileMtlRawDataV2.h"
#include "ModelMeshV1.h"


enum MapEditorMode {
	Mode_Camera_Move = 0,
	Mode_Entities_Selection = 1,
	Mode_Tiles_Selection = 2,
	Mode_Edit_Tile_Material =3,
	Mode_Edit_Tile_Height = 4,
	Mode_Edit_Tile_Model = 5
};
class MapEditorScene :
	public Scene {
private:
	GridRawDataV2* grid_data_V2;
	PGMapAtlas * test_atlas;
	PGAtlasRegion* region_display[9];
	bool region_edited[9];
	HexaGridMapMesh* region_mesh;

	FileMtlRawDataV2* material_Test;
	ModelRawDataV1* modele_test1;
	ModelRawDataV1* modele_test2;
	ModelMeshV1* test1_model_mesh;	
	ModelMeshV1* test2_model_mesh;
	
	RawModelData *test_model;
	RawModelData *test_model2;
	RawModelData *test_model3;
	
	PGLight scene_light;
	double time;
	double tempo_var;
	MapEditorMode current_mode;
public:
	MapEditorScene();
	virtual ~MapEditorScene();
	void Update(Controler *controler, double timeElapse);
	void Render(BaseRenderer *renderer);
	void Build(MousePicker* mouse_picker);
	void HandleTilePicking(Controler * controler);
	void HandleCameraMovement(Controler * controler);
	void HandleControler(Controler *controler);
};
#endif

