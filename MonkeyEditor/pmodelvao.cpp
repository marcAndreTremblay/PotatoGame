#include "pmodelvao.h"

PModelVAO::PModelVAO(PModelSurfaceType model_surface_type = Solid)
{
    surface_type = model_surface_type;
    this->initializeOpenGLFunctions();
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
}
PModelVAO::~PModelVAO()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
void PModelVAO::Load(P3DModelData* model_data){
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    int per_vertex_data_lenght = 0;
    switch(surface_type){
        case Solid:
                per_vertex_data_lenght =
                sizeof(QVector4D)+ //LOC (0)
                sizeof(QVector3D); //LOC (1)
        break;
        case Material:
                per_vertex_data_lenght =
                sizeof(QVector4D)+ //LOC (0)
                sizeof(QVector3D)+ //LOC (1)
                sizeof(QVector3D)+ //LOC (2)
                sizeof(QVector3D)+ //LOC (3)
                sizeof(QVector3D)+ //LOC (4)
                sizeof(QVector4D); //LOC (5)
        break;
        case Texture: break;
    }

}
