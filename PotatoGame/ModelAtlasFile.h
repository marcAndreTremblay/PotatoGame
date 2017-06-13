#if !defined(MODEL_ATLAS_FILE_H)
#define MODEL_ATLAS_FILE_H

#include "Core.h"
#include "String.h"
#include "List.h"
#include "ModelRawDataV1.h"
#include "ModelMeshV1.h"
using namespace PG::Core;



/*
	Note(Marc): Refactor this with something generic like a File classs and then 
		the specific file extend the BaseFileClass also maybe this will elp with portability
*/
/*
	File Format : 
		[TILE BOTTOM]
		Count:1
		1 file_name.obj
		2 file_name.obj
		...
		n file_name.obj

		[TILE TOP]
		Count:2
		1 file_name.obj
		...
		n file_name.obj
		
		[NOT FOUND]
		1 file_name.obj

		[TILE MODEL]
		Count:1
		1 file_name.obj
		...
		n file_name.obj
*/
class AtlasModelData {
public:
	int id;
	ModelRawDataV1* data;
	ModelMeshV1 * mesh;
	Str* file_name;
	Str* folder_path;
	AtlasModelData() {
		data = nullptr;
		mesh = nullptr;
		file_name = nullptr;
		folder_path = nullptr;
		id = -1;
	}
	AtlasModelData(int _id,char *_file,char* _folder) {
		data = nullptr;
		mesh = nullptr;
		this->file_name = new Str(_file);
		this->folder_path = new Str(_folder);
		this->id = _id;
	}
	~AtlasModelData() {
		delete(this->file_name);
		delete(this->folder_path);
		delete(this->data);
		delete(this->mesh);
	}
};
enum AtlasCategorie{
	Tile_Model=0,
	Tile_Top = 1,
	Tile_Bottom = 2 
};
class ModelAtlasFile {
private:
	Str* Model_Folder_Path;
	Str* Atlas_File_Path;
	List<AtlasModelData>* tile_model_file_path;
	List<AtlasModelData>* bottom_tile_file_path;
	List<AtlasModelData>* top_tile_file_path;
	AtlasModelData* not_found_path;
public:
	ModelAtlasFile(char *file_path);
	virtual ~ModelAtlasFile();
	void LoadFromFile();
	void LoadRawData();
	void LoadMesh();
	AtlasModelData* FetchTileModelFilePath(AtlasCategorie categorie,int id);
};
#endif

