#ifndef PBASEMESH_H
#define PBASEMESH_H

#include <QOpenGLFunctions_3_2_Core>

class PBaseMesh: protected QOpenGLFunctions_3_2_Core
{
public:
    PBaseMesh();
    ~PBaseMesh();
};

#endif // PBASEMESH_H
