#if !defined(MODEL_MESH_V2)
#define MODEL_MESH_V2

#include "Core.h"
#include "ModelRawDataV1.h"
#include "BaseMesh.h"

using namespace PG::Core;
enum ModelMeshV1_Mode {
	None,
	Vertices_Normal,
	Vertices_Normal_Material,
	Vertices_Normal_Texture
};
class ModelMeshV1 :
	public BaseMesh {
	ModelRawDataV1* Model_Data; //<-Resource not owned
public:
	ModelMeshV1_Mode Mode;
	ModelMeshV1(ModelRawDataV1 *_data);
	virtual ~ModelMeshV1();
	void Build();
};
#endif //MODEL_MESH_V2

