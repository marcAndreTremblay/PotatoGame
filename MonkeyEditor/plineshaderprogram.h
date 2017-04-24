#ifndef PLINESHADERPROGRAM_H
#define PLINESHADERPROGRAM_H

#include "pshaderprogram.h"
#include "plinevao.h"
#include <QMatrix4x4>

class PLineShaderProgram : public PShaderProgram
{
private:
    GLuint Unif_Translate;
    GLuint Unif_Scale;
public:
    PLineShaderProgram();
    ~PLineShaderProgram() ;
     void Render(PLineVAO* vao);
};

#endif // PLINESHADERPROGRAM_H
