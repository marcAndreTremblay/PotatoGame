#ifndef P3DMODELDATA_H
#define P3DMODELDATA_H

#include <QOpenGLFunctions_3_2_Core>


class P3DModelData :
        protected QOpenGLFunctions_3_2_Core
{
private:

public:
    P3DModelData();
    ~P3DModelData();
    GLuint LoadToVAO();
};

#endif // P3DMODELDATA_H
