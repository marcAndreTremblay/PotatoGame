#include "plinevao.h"

PLineVAO::PLineVAO()
{
    this->initializeOpenGLFunctions();
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);



    next = 0;
    max_size = -1;
}
PLineVAO::~PLineVAO()
{
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
}
void PLineVAO::Add(QVector4D position1,QVector4D position2,QVector4D color){
    if(next != -1 && next<=max_size){
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, (next*size_per_vertex), sizeof(QVector4D), &position1);
        glBufferSubData(GL_ARRAY_BUFFER, (next*size_per_vertex) + sizeof(QVector4D), sizeof(QVector4D), &color);

        glBufferSubData(GL_ARRAY_BUFFER, (next*size_per_vertex)+ 2*sizeof(QVector4D), sizeof(QVector4D), &position2);
        glBufferSubData(GL_ARRAY_BUFFER, (next*size_per_vertex) + 3*sizeof(QVector4D), sizeof(QVector4D), &color);
        next++;
    }
}

void PLineVAO::BuildVAO(int buff_size){
    max_size = buff_size-1;
    size_per_vertex = 2*(sizeof(QVector4D)+sizeof(QVector4D));

    glBindVertexArray(this->VAO);
         glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
         glBufferData(GL_ARRAY_BUFFER,buff_size*size_per_vertex,nullptr,GL_DYNAMIC_DRAW);

        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 2 * sizeof(QVector4D), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 2 * sizeof(QVector4D), (GLvoid*)(4 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
    glBindVertexArray(0);
}
