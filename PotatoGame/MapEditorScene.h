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
#include "MapAtlasRawDataV1.h"
#include "HexaGridMapMesh.h"
#include "HexaGridMapMeshV2.h"

#include "ModelRawDataV1.h"
#include "FileMtlRawDataV2.h"
#include "ModelMeshV1.h"

#include "ModelAtlasFile.h"
#include "AnimatorManager.h"
#include "SolarSystemEntities.h"

enum MapEditorMode {
	Mode_Camera_Move = 0,
	Mode_Edit_Tile_Top_Style = 1,
	Mode_Tiles_Selection = 2,
	Mode_Edit_Tile_Top_Material =3,
	Mode_Edit_Tile_Height = 4,
	Mode_Edit_Tile_Model = 5,
	Mode_Edit_Tile_Bottom_Material = 6,
};
class MapEditorScene :
	public Scene {
private:
	MapAtlasRawDataV1* map_atlas;



	//Display information
	MapAtlasRegion* map_atlas_region_display[9];
	bool map_atlas_region_edited[9];
	//Note(Marc): Maybe we should keep the selected_indexes_array here array[i][x*y]
	
	//Todo(marc): move this into the atlas file
	FileMtlRawDataV2* material_file;
	ModelRawDataV1* bottom_tile_raw_data;
	ModelRawDataV1* top_tile_raw_data;

	MaterielRawData* test_mat;
	MaterielRawData* selected_mat;

	//only create the requirement mesh for the edited map
	ModelMeshV1* bottom_tile_mesh;
	ModelMeshV1* top_tile_mesh;
	ModelMeshV1* sphere_mesh;
	ModelMeshV1* test_forest;
	ModelMeshV1* test_floor_tile;

	//Other Scene data
	PGLight scene_light;
	double time;
	double tempo_var;
	MapEditorMode current_mode;

	ModelAtlasFile* Model_Atlas_File;
	SolorSystemEntities* solar_data;
/*
	I don't believe in the gods' existence.\n
	Man is the master of his own fate, not the gods.\n
	The gods are man's creation, to give answers that they are too afraid to give themselves."
*/
	void RenderSolarSystem(BaseRenderer * renderer);
	void RenderMapGrid(BaseRenderer * renderer);
public:
	MapEditorScene(MousePicker* mouse_picker);
	virtual ~MapEditorScene();
	void Update(Controler *controler, double timeElapse);
	
	void Render(BaseRenderer *renderer);
	void Build(AnimatorManager* anmation_manager);
	void HandleTilePicking(Controler * controler);
	void HandleCameraMovement(Controler * controler);
	void HandleControler(Controler *controler);
};
#endif

