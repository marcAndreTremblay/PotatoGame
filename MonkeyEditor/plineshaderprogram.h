#ifndef PLINESHADERPROGRAM_H
#define PLINESHADERPROGRAM_H

#include "pshaderprogram.h"
#include "plinevao.h"

class PLineShaderProgram : public PShaderProgram
{
private:
    GLuint Unif_Translate;
public:
    PLineShaderProgram();
    ~PLineShaderProgram() ;
     void Render(PLineVAO* vao);
};

#endif // PLINESHADERPROGRAM_H
