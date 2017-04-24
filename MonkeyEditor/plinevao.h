#ifndef PLINEVAO_H
#define PLINEVAO_H

#include <QVector4D>
#include <QOpenGLFunctions_3_2_Core>

class PLineVAO: protected QOpenGLFunctions_3_2_Core
{
private:

    GLuint VBO;

    int max_size;
    int size_per_vertex;
public:
     int next;
     GLuint VAO;
    PLineVAO();
    ~PLineVAO();
    void BuildVAO(int size);
    void Add(QVector4D position1,QVector4D position2,QVector4D color);
};

#endif // PLINEVAO_H
