#if !defined(MODEL_ATLAS_FILE_H)
#define MODEL_ATLAS_FILE_H

#include "Core.h"
#include "String.h"
#include "List.h"
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
struct AtlasModelData {
	int id;
	Str* path;
	AtlasModelData() {
		path = nullptr;
		id = -1;
	}
	AtlasModelData(int id,char *file) {
		path = new Str(file);
		id = id;
	}
	~AtlasModelData() {
		delete(path);
	}
};
enum AtlasCategorie{
	Tile_Model=0,
	Tile_Top = 1,
	Tile_Bottom = 2
};
class ModelAtlasFile {
private:
	Str* Atlas_File_Path;
	List<AtlasModelData>* tile_model_file_path;
	List<AtlasModelData>* bottom_tile_file_path;
	List<AtlasModelData>* top_tile_file_path;
	AtlasModelData* not_found_path;
public:
	ModelAtlasFile(char *file_path);
	virtual ~ModelAtlasFile();
	void LoadFromFile();

	AtlasModelData* FetchTileModelFilePath(AtlasCategorie categorie,int id);
};
#endif

