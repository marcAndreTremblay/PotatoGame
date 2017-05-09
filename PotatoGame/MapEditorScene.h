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
	
	//Other Scene data
	PGLight scene_light;
	double time;
	double tempo_var;
	MapEditorMode current_mode;
	//Man is a master of his own fate, not the god. 
	//The gods are men's creation to give answer that they are to 
	//	afraid to give themself
	void RenderMapGrid(BaseRenderer * renderer);
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

