#if !defined(PG_TEXT_MESH_H)	
#define PG_TEXT_MESH_H

#include "stdafx.h"

#include "Core.h"

#include "List.h"
#include "String.h"
#include "Mesh.h"
#include "Font.h"
#include "PGShaderSources.h"

namespace PG {
	namespace Engine {

		class PGTextMesh :public Mesh {
		private:
			GLuint EBO;
			GLuint Unif_Translate;
			GLuint Unif_Scale;
			GLuint Unif_Text_Color; 
			v3 PGTextMesh::CalculateOrignFromPossition(v3* possition, PGCharacter* target_char, r32 scale) {
				v3 result = *possition;
				result.x -= target_char->Bearing.x* scale;
				result.y += target_char->Bearing.y* scale;
				return result;
			}
			v3 PGTextMesh::CalculatePossitionFromOrigne(v3*orign, PGCharacter* target_char, r32 scale) {
				v3 result = *orign;
				result.x += target_char->Bearing.x* scale;
				result.y -= target_char->Bearing.y* scale;
				return result;
			}
		public:
			PGTextMesh() :
				Mesh(new PGShader(text_vertex_shader, text_fragment_shader)) {
				glGenBuffers(1, &this->EBO);
			}
			~PGTextMesh() {
				glDeleteBuffers(1, &this->EBO);
			}
			v2 PGTextMesh::Render(char *text_string, v3 possition, v4 color, r32 scale, Font *font) {
				v2 text_bounding_box = v2(0.f);
				if (this->Mesh::IsBuild() == true) {
					this->Shader->Use();
					glBindVertexArray(this->VAO);
					glUniform4fv(this->Unif_Text_Color, 1, &color[0]);


					r32 y_top_offset = 0.f;
					r32 y_bot_offset = 0.f;
					char* first_passs_ptr = text_string;
					while (*first_passs_ptr != ENDSTR) {
						PGCharacter * ch = &font->CharacterCollection[*first_passs_ptr];
						if ((ch->Bearing.y*scale) > y_top_offset) {
							y_top_offset = (float)ch->Bearing.y*scale;
						}
						text_bounding_box.x += ((ch->Advance >> 6) * scale);
						first_passs_ptr++;
					}
					text_bounding_box.y += y_top_offset + y_bot_offset;


					v3 current_possition = possition;
					v3 current_origin = current_possition + v3(0.f, y_top_offset, 0.f);

					for (char *current_char = text_string; *current_char != ENDSTR; current_char++) {
						PGCharacter * ch = &font->CharacterCollection[*current_char];
						glBindTexture(GL_TEXTURE_2D, ch->TextureID);

						current_possition = CalculatePossitionFromOrigne(&current_origin, ch, scale);


						GLfloat w = ch->Size.x * scale;
						GLfloat h = ch->Size.y * scale;

						//Push uniform
						glUniformMatrix4fv(this->Unif_Translate, 1, GL_FALSE, &glm::translate(m4(1.f), v3(current_possition.x, current_possition.y, current_possition.z))[0][0]);
						glUniformMatrix4fv(this->Unif_Scale, 1, GL_FALSE, &glm::scale(m4(1.f), v3(w, h, 1.0f))[0][0]);

						glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

						current_origin.x += ((ch->Advance >> 6) * scale);
					}

					glBindVertexArray(0);
					glBindTexture(GL_TEXTURE_2D, 0);
				}
				return text_bounding_box;
			}

			void  PGTextMesh::Build() override {
				BuildableObject::StartBuilding();


				glUniformBlockBinding(this->Shader->ShaderID, glGetUniformBlockIndex(this->Shader->ShaderID, "Renderer_UBO"), 1);


				this->Unif_Translate = glGetUniformLocation(this->Shader->ShaderID, "Translate");
				this->Unif_Scale = glGetUniformLocation(this->Shader->ShaderID, "Scale");
				this->Unif_Text_Color = glGetUniformLocation(this->Shader->ShaderID, "TextColor");


				glBindVertexArray(this->VAO);
				glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(text_vertices_rev), text_vertices_rev, GL_STATIC_DRAW);

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(text_quad_indices), text_quad_indices, GL_STATIC_DRAW);

				glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
				glEnableVertexAttribArray(0);

				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(4 * sizeof(GLfloat)));
				glEnableVertexAttribArray(1);

				BuildableObject::EndBuilding();
			}
		};
	}
}
#endif