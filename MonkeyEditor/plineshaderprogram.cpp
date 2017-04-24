#include "plineshaderprogram.h"

PLineShaderProgram::PLineShaderProgram() :
    PShaderProgram(line_vertex_shader,FragShaderColor4fIn)
{
    glUniformBlockBinding(this->ShaderID, glGetUniformBlockIndex(this->ShaderID, "Renderer_UBO"), 1);

}
PLineShaderProgram::~PLineShaderProgram(){


}
void PLineShaderProgram::Render(PLineVAO* vao){
    //Note(Marc) : will entualy recive the model
    this->Use();
    glBindVertexArray(vao->VAO);

    glDrawArrays(GL_LINES, 0, vao->next);
}
