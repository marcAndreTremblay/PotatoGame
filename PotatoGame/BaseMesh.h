#if !defined(BASE_MESH_H)	
#define BASE_MESH_H

#include "stdafx.h"

#include "Core.h"
#include "List.h"
#include "String.h"
#include "BuildableObject.h"

using namespace PG::Engine;

class BaseMesh : public BuildableObject {
protected:
	GLuint VAO;
	GLuint VBO;
	int Vertices_Count;
	int Data_Size_Per_vertex;
public:
	BaseMesh();
	virtual ~BaseMesh();
	virtual void Build();
	void BindVAO();

	virtual int GetVeticesCount();
	
};
#endif //BASE_MESH_H

