#if !defined(PG_AXIS_MESH_H)	
#define PG_AXIS_MESH_H

#include "stdafx.h"

#include "Core.h"

#include "List.h"
#include "String.h"
#include "Mesh.h"
#include "Font.h"
#include "PGShaderSources.h"

namespace PG {
	namespace Engine {
		class AxisMesh :public Mesh {
		private:
			GLuint Unif_Translate;
			GLuint Unif_Frag_Color;
		public:
			AxisMesh() :
				Mesh(new PGShader(axis_vertex_shader, FragShaderColor4fIn)) {
			}
			~AxisMesh() {

			}
			void AxisMesh::Render(v3 possition, v4 color, int axe = 6) {
				this->Shader->Use();
				glUniformMatrix4fv(this->Unif_Translate, 1, GL_FALSE, &glm::translate(m4(1.f), possition)[0][0]);
				glBindVertexArray(this->VAO);
				glDrawArrays(GL_LINES, 0, axe);
			}
			void AxisMesh::Build() {

				Shader->Use();
				// .:: Bind UBO ::. 
				glUniformBlockBinding(
					this->Shader->ShaderID,
					glGetUniformBlockIndex(this->Shader->ShaderID, "Renderer_UBO"),
					1
					);
				// .:: Get Uniform reference ::.
				this->Unif_Translate = glGetUniformLocation(this->Shader->ShaderID, "Translate");
				glBindVertexArray(this->VAO);
				// 2. Copy our vertices array in a vertex buffer for OpenGL to use
				glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
				glBufferData(
					GL_ARRAY_BUFFER,
					sizeof(axes_vertex_data),
					axes_vertex_data,
					GL_STATIC_DRAW
					);
				// 3.  Vertex possition attributes pointers
				glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 2 * sizeof(v4), (GLvoid*)0);
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 2 * sizeof(v4), (GLvoid*)(4 * sizeof(GLfloat)));
				glEnableVertexAttribArray(1);

				glBindVertexArray(0);
			}
		};
	}
}
#endif