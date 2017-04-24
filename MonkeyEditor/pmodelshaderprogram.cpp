#include "pmodelshaderprogram.h"

PModelShaderProgram::PModelShaderProgram() :
    PShaderProgram(model_vertex_shader,Model_FragShader)
{
            glUniformBlockBinding(this->ShaderID, glGetUniformBlockIndex(this->ShaderID, "Renderer_UBO"), 1);
            glUniformBlockBinding(this->ShaderID, glGetUniformBlockIndex(this->ShaderID, "SceneAdvanceLightData_UBO"), 3);

            this->Unif_Translate = glGetUniformLocation(this->ShaderID, "Translate");
            this->Unif_Scale = glGetUniformLocation(this->ShaderID, "Scale");
}
PModelShaderProgram::~PModelShaderProgram()
{

}
void PModelShaderProgram::Render(QVector3D possition, QVector3D size){
    //Note(Marc) : will entualy recive the model
    this->Use();
   // glBindVertexArray(model->VAO);

    QMatrix4x4 translate_m =  QMatrix4x4();
    QMatrix4x4 scale_m =  QMatrix4x4();
        translate_m.translate(possition);
        scale_m.scale(size);
    glUniformMatrix4fv(this->Unif_Translate, 1, GL_FALSE, (float*)&translate_m);
    glUniformMatrix4fv(this->Unif_Scale, 1, GL_FALSE, (float*)&scale_m);

   // glDrawArrays(GL_TRIANGLES, 0, model->face_count*3);
}
