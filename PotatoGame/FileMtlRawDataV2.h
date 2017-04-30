#if !defined(FILE_MTL_RAW_DATA_V2_H)
#define FILE_MTL_RAW_DATA_V2_H

#include "stdafx.h"
#include "Core.h"
#include "String.h"
#include "List.h"
using namespace PG::Core;

class MaterielRawData {
public:
	int Id;
	Str *Name;
	r32 Shininess;
	v3 Ambient;
	v3 Diffuse;
	v3 Specular;
	MaterielRawData(char* name, int id) {
		Name = new Str(name);
		Id = id;
		Ambient = v3(1.f);
		Diffuse = v3(1.f);
		Specular = v3(1.f);
		Shininess = 32.f;
	}
	~MaterielRawData() {
		delete(Name);
	}

};

class FileMtlRawDataV2 {
	Str *File_Path;
	List<MaterielRawData> *RawMateriels;
	int Material_Count;
public:
	FileMtlRawDataV2();
	virtual ~FileMtlRawDataV2();
	void LoadFromFile(char* _file_path);
	MaterielRawData* FileMtlRawDataV2::FindByNameRef(char* name);
	MaterielRawData* FileMtlRawDataV2::FindByNameId(int target_id);
};
#endif //FILE_MTL_RAW_DATA_V2_H

