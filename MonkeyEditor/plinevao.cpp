#include "plinevao.h"

PLineVAO::PLineVAO()
{
    this->initializeOpenGLFunctions();
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);

}
PLineVAO::~PLineVAO()
{
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
}


void PLineVAO::BuildVAO(){
    glBindVertexArray(this->VAO);
         glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
         glBufferData(GL_ARRAY_BUFFER,sizeof(square_vertex_data),square_vertex_data,GL_STATIC_DRAW);

        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 1 * sizeof(QVector4D), (GLvoid*)0);
        glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}
