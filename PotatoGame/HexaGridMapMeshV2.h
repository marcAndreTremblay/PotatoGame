#if !defined(HEXA_GRID_MAP_MESH_V2)
#define HEXA_GRID_MAP_MESH_V2

#include "stdafx.h"


//Todo(marc): remove  this 
#include <random>
#include <time.h>  

#include "Core.h"
#include "BaseMesh.h"
#include "GridRawDataV2.h"
#include "ModelRawDataV1.h"
#include "FileMtlRawDataV2.h"

using namespace PG::Engine;
using namespace PG::Core;

class HexaGridMapMeshV2 :
	public BaseMesh {
	GridRawDataV2* Grid_Data; //<- Not owned
	FileMtlRawDataV2* Material_Data;//<- Not owned
	void PushModelToBuffer(int* buffer_cursor, ModelRawDataV1* model_data, MaterielRawData* material, m4* offset, m4* scale, m4* rotate);
	void PushModelToBuffer(int* buffer_cursor, ModelRawDataV1* model_data, m4* offset, m4* scale, m4* rotate);
	int CalculateRegionVerticesCount();
public:
	HexaGridMapMeshV2(GridRawDataV2* data);
	virtual ~HexaGridMapMeshV2();
	void Build();
	
};
#endif //HEXA_GRID_MAP_MESH_V2

