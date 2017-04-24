#ifndef PMODELVAO_H
#define PMODELVAO_H

#include "p3dmodeldata.h"

#include <QVector4D>
#include <QVector3D>
#include <QOpenGLFunctions_3_2_Core>

enum PModelSurfaceType{
    Solid = 1,
    Material= 2,
    Texture= 3,
};
class PModelVAO : protected QOpenGLFunctions_3_2_Core
{
protected:
    GLuint VAO;
    GLuint VBO;
    PModelSurfaceType surface_type;
public:
    int face_count;
    PModelVAO(PModelSurfaceType model_surface_type);
    ~PModelVAO();
    virtual void Load(P3DModelData* model_data);
};

#endif // PMODELVAO_H
