#ifndef PLINEVAO_H
#define PLINEVAO_H

#include "pshaderprogram.h"

#include <QVector4D>
#include <QOpenGLFunctions_3_2_Core>

class PLineVAO: protected QOpenGLFunctions_3_2_Core
{
private:

    GLuint VBO;
public:
    GLuint VAO;
    PLineVAO();
    ~PLineVAO();
    void BuildVAO();

};

#endif // PLINEVAO_H
