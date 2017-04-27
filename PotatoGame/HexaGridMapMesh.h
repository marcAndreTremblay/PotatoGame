#if !defined(HEXA_GRID_MAP_MESH_H)
#define HEXA_GRID_MAP_MESH_H

#include "stdafx.h"
#include "Core.h"
#include "PGMapGrid.h"
#include "BaseMesh.h"

using namespace PG::Engine;
using namespace PG::Core;

class HexaGridMapMesh :
	public BaseMesh {
private:	
	PGGridRawData *grid_data;
	v3 ReadVector3(const GLfloat* target);
public:
	HexaGridMapMesh(PGGridRawData *_grid_data);
	virtual ~HexaGridMapMesh();
	void Build();

};
static const GLfloat hexagone_vertex_data_v3_2[] = {
	0.0f, -1.0f, 1.0f,
	-1.0f, -0.4226497308f, 1.0f,
	-1.0f, 0.4226497308f, 1.0f,
	0.0f, 1.0f, 1.0f,
	1.0f, 0.4226497308f, 1.0f,
	1.0f, -0.4226497308f, 1.0f,

	0.0f, -1.0f, 0.0f,
	-1.0f, -0.4226497308f,0.0f,
	-1.0f, 0.4226497308f, 0.0f,
	0.0f, 1.0f, 0.0f,
	1.0f, 0.4226497308f, 0.0f,
	1.0f, -0.4226497308f, 0.0f
};

static const GLuint hexagone_indice_data_2[] = {
	//Top hexagone
	0, 5, 1,
	1, 3, 2,
	3, 5, 4,
	1, 5, 3,
	//Square side 1
	0, 1, 6, //Upper
	1, 7 ,6,
	//Square side 2
	1, 2, 7,
	2, 8, 7,
	//Square side 3
	2, 3, 8,
	3, 9 ,8,
	//Square side 4
	3, 4, 9,
	4, 10, 9,
	//Square side 5
	4, 5, 10,
	5, 11, 10,
	//Square side 6
	5, 0, 11,
	0, 6, 11,
	//Lower hexagone 
	7, 11, 6,
	8, 9, 7,
	10, 11, 9,
	9, 11, 7,
};
#endif //HEXA_GRID_MAP_MESH_H

