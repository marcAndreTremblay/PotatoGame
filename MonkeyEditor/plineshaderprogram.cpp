#include "plineshaderprogram.h"

PLineShaderProgram::PLineShaderProgram() :
    PShaderProgram(line_vertex_shader,FragShaderColor4fIn)
{
    glUniformBlockBinding(this->ShaderID, glGetUniformBlockIndex(this->ShaderID, "Renderer_UBO"), 1);
    this->Unif_Translate = glGetUniformLocation(this->ShaderID, "Translate");
    this->Unif_Scale = glGetUniformLocation(this->ShaderID, "Scale");

}
PLineShaderProgram::~PLineShaderProgram(){


}
void PLineShaderProgram::Render(PLineVAO* vao){
    this->Use();
    QMatrix4x4 translate = QMatrix4x4();
    translate.translate(0.f,0.f,0.f);
    QMatrix4x4 scale = QMatrix4x4();
    scale.translate(3.f,3.f,0.f);

    //glBindVertexArray(vao->VAO);
    //glDrawArrays(GL_TRIANGLES, 0, 6);
}
