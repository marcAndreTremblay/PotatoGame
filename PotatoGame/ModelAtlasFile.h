#if !defined(MODEL_ATLAS_FILE_H)
#define MODEL_ATLAS_FILE_H

#include "Core.h"
#include "String.h"
using namespace PG::Core;



/*
	Note(Marc): Refactor this with something generic like a File classs and then 
		the specific file extend the BaseFileClass also maybe this will elp with portability
*/
/*
	File Format : 
		
*/
class ModelAtlasFile {
private:
	Str* mtl_file_path;
public:
	ModelAtlasFile();
	virtual ~ModelAtlasFile();
};
#endif

