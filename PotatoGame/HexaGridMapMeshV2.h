#if !defined(HEXA_GRID_MAP_MESH_V2)
#define HEXA_GRID_MAP_MESH_V2

#include "stdafx.h"

#include "Core.h"
#include "BaseMesh.h"
#include "GridRawDataV2.h"


using namespace PG::Engine;
using namespace PG::Core;

class HexaGridMapMeshV2 :
	public BaseMesh {
	GridRawDataV2* Data; //<- Not owned
public:
	HexaGridMapMeshV2(GridRawDataV2* data);
	virtual ~HexaGridMapMeshV2();
	void Build();
};
#endif //HEXA_GRID_MAP_MESH_V2

