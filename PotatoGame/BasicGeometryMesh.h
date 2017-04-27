#ifndef BASE_GEOMETRY_H
#define BASE_GEOMETRY_H
#include "BaseMesh.h"
#include "Core.h"
using namespace PG::Core;
class BasicGeometryMesh :
	public BaseMesh {
public:
	BasicGeometryMesh();
	virtual ~BasicGeometryMesh();
	void Build();
};
static const GLfloat geo_square_vertex_data[] = {
	// Tex 1					//Texture Coords
	-1.0f, -1.0f, 0.0f, 1.0f,  // Bottom Left 1
	-1.0f, 1.0f, 0.0f, 1.0f,  // Top Left 2
	1.0f, 1.0f, 0.0f, 1.0f,  // Top Right 3
	-1.0f, -1.0f, 0.0f, 1.0f,   // Bottom Left 4
	1.0f, 1.0f, 0.0f, 1.0f, // Top Right 5
	1.0f, -1.0f, 0.0f, 1.0f // Bottom Right 6
};
#endif //BASE_GEOMETRY_H

