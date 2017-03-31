#if !defined(PG_MESH_INSTANCE_H)
#define PG_MESH_INSTANCE_H


#include "stdafx.h"
#include "AssetManager.h"
#include "Core.h"
#include "List.h"
#include "PGShaderSources.h"
#include "Mesh.h"
#include "Font.h"
#include "Texture.h"


using namespace PG::Engine;



	class PGLineMesh : public Mesh {
	private:
		GLuint Unif_P1;
		GLuint Unif_P2;
		GLuint Unif_Frag_Color;
	public:
		PGLineMesh() : 
			Mesh(new PGShader(axis_vertex_shader, FragShaderColor4fIn)){
			
		}
		~PGLineMesh() {

		}
		void PGLineMesh::Render(v3 p1,v3 p2, v4 color) {

		}
		void PGLineMesh::Build() {

		}
	};

	class PGSquareMesh :public Mesh {
		private:
			GLuint Unif_Translate;
			GLuint Unif_Scale;
			GLuint Unif_Frag_Color;
		public:	
			PGSquareMesh() :
				Mesh(new PGShader(simple_vertex_shader, FragShaderColor4fUnif)) {
				this->Unif_Scale = 0;
				this->Unif_Translate = 0;
			}
			~PGSquareMesh() {

			}
			void PGSquareMesh::Render(v3 possition, v2 size, v4 color) {
				this->Shader->Use();
				glUniformMatrix4fv(this->Unif_Translate, 1, GL_FALSE, &glm::translate(m4(1.f), possition)[0][0]);
				glUniformMatrix4fv(this->Unif_Scale, 1, GL_FALSE, &glm::scale(m4(1.f), v3(size, 1.0f))[0][0]);
				glUniform4fv(this->Unif_Frag_Color, 1, &color[0]);
				glBindVertexArray(this->VAO);
				glDrawArrays(GL_TRIANGLES, 0, 6);

			}
			void PGSquareMesh::Build() {

			Shader->Use();
			// .:: Bind UBO ::. 
			glUniformBlockBinding(
				this->Shader->ShaderID,
				glGetUniformBlockIndex(this->Shader->ShaderID, "Renderer_UBO"),
				1
				);
			// .:: Get Uniform reference ::.
			this->Unif_Translate = glGetUniformLocation(this->Shader->ShaderID, "Translate");
			this->Unif_Scale = glGetUniformLocation(this->Shader->ShaderID, "Scale");
			this->Unif_Frag_Color = glGetUniformLocation(this->Shader->ShaderID, "FragColor");
			glBindVertexArray(this->VAO);
			// 2. Copy our vertices array in a vertex buffer for OpenGL to use
			glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
			glBufferData(
				GL_ARRAY_BUFFER,
				sizeof(square_vertex_data),
				square_vertex_data,
				GL_STATIC_DRAW
				);
			// 3.  Vertex possition attributes pointers
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(v4), (GLvoid*)0);
			glEnableVertexAttribArray(0);
			glBindVertexArray(0);
		}
	};
	class PGCubeMesh :public Mesh {
		private:
			GLuint Unif_Translate;
			GLuint Unif_Scale;
			GLuint Unif_Frag_Color;
		public:
			PGCubeMesh() :
				Mesh(new PGShader(simple_vertex_shader, FragShaderColor4fUnif)) {
				this->Unif_Scale = 0;
				this->Unif_Translate = 0;
			}
			~PGCubeMesh() {

			}
			void PGCubeMesh::Render(v3 possition, v3 size, v4 color) {
				this->Shader->Use();
				glUniformMatrix4fv(this->Unif_Translate, 1, GL_FALSE, &glm::translate(m4(1.f), possition)[0][0]);
				glUniformMatrix4fv(this->Unif_Scale, 1, GL_FALSE, &glm::scale(m4(1.f), size)[0][0]);
				glUniform4fv(this->Unif_Frag_Color, 1, &color[0]);
				glBindVertexArray(this->VAO);
				glDrawArrays(GL_TRIANGLES, 0, 36);

			}
			void PGCubeMesh::Build() {


				// .:: Bind UBO ::. 
				glUniformBlockBinding(
					this->Shader->ShaderID,
					glGetUniformBlockIndex(this->Shader->ShaderID, "Renderer_UBO"),
					1
					);
				// .:: Get Uniform reference ::.
				this->Unif_Translate = glGetUniformLocation(this->Shader->ShaderID, "Translate");
				this->Unif_Scale = glGetUniformLocation(this->Shader->ShaderID, "Scale");
				this->Unif_Frag_Color = glGetUniformLocation(this->Shader->ShaderID, "FragColor");
				glBindVertexArray(this->VAO);
				// 2. Copy our vertices array in a vertex buffer for OpenGL to use
				glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
				glBufferData(
					GL_ARRAY_BUFFER,
					sizeof(cube_vertex_data2),
					cube_vertex_data2,
					GL_STATIC_DRAW
					);
				// 3.  Vertex possition attributes pointers
				glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(v4), (GLvoid*)0);
				glEnableVertexAttribArray(0);
				glBindVertexArray(0);
			}
		};

	class PGLightedCubeMesh :public Mesh {
		private:
			GLuint Unif_Translate;
			GLuint Unif_Scale;
			GLuint Unif_Object_Color;
		public:
			PGLightedCubeMesh() :
				Mesh(new PGShader(light_vertex_shader, FragShaderBasicLight)) {


			}
			~PGLightedCubeMesh() {

			}
			void PGLightedCubeMesh::Render(v3 possition, v3 size, v4 color) {
				this->Shader->Use();
				glUniformMatrix4fv(this->Unif_Translate, 1, GL_FALSE, &glm::translate(m4(1.f), possition)[0][0]);
				glUniformMatrix4fv(this->Unif_Scale, 1, GL_FALSE, &glm::scale(m4(1.f), size)[0][0]);
				glUniform4fv(this->Unif_Object_Color, 1, &color[0]);
				glBindVertexArray(this->VAO);
				glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

			}
			void PGLightedCubeMesh::Build() {
				BuildableObject::StartBuilding();

					glUniformBlockBinding(this->Shader->ShaderID, glGetUniformBlockIndex(this->Shader->ShaderID, "Renderer_UBO"), 1);
					glUniformBlockBinding(this->Shader->ShaderID, glGetUniformBlockIndex(this->Shader->ShaderID, "SceneLightData_UBO"), 2);

					this->Unif_Translate = glGetUniformLocation(this->Shader->ShaderID, "Translate");
					this->Unif_Scale = glGetUniformLocation(this->Shader->ShaderID, "Scale");
					this->Unif_Object_Color = glGetUniformLocation(this->Shader->ShaderID, "ObjectColor");
				

					glBindVertexArray(this->VAO);
					glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
					glBufferData(GL_ARRAY_BUFFER,sizeof(cube_vertex_normal),cube_vertex_normal,	GL_STATIC_DRAW);
					

					glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(v4)+sizeof(v3), (GLvoid*)0);
					glEnableVertexAttribArray(0);
					glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(v4)+sizeof(v3), (GLvoid*)(sizeof(v4)));
					glEnableVertexAttribArray(1);
					glBindVertexArray(0);

				BuildableObject::EndBuilding();
			}
		};
	class PGLightedHexagoneMesh :public Mesh {
		private:
			GLuint Unif_Translate;
			GLuint Unif_Scale;
			GLuint Unif_Object_Color;

		public:
			v3 ReadVector3(const GLfloat* target) {
				v3 vec = {};
				vec.x = *target;
				target++;
				vec.y = *target;
				target++; 
				vec.z = *target;
				target++;
				return vec;
			}
			PGLightedHexagoneMesh() :
				Mesh(new PGShader(light_vertex_shader, FragShaderBasicLight)) {
			}
			~PGLightedHexagoneMesh() {
			}
			void PGLightedHexagoneMesh::Render(v3 possition, v3 size, v4 color) {
				this->Shader->Use();
					glUniformMatrix4fv(this->Unif_Translate, 1, GL_FALSE, &glm::translate(m4(1.f), possition)[0][0]);
					glUniformMatrix4fv(this->Unif_Scale, 1, GL_FALSE, &glm::scale(m4(1.f), size)[0][0]);
					glUniform4fv(this->Unif_Object_Color, 1, &color[0]);
		
				glBindVertexArray(this->VAO);
			
				glDrawArrays(GL_TRIANGLES, 0, 60);
			}
			void PGLightedHexagoneMesh::Build() {
			BuildableObject::StartBuilding();
			int face_count = 20;
			int vertex_per_face = 3;

			glUniformBlockBinding(this->Shader->ShaderID, glGetUniformBlockIndex(this->Shader->ShaderID, "Renderer_UBO"), 1);
			glUniformBlockBinding(this->Shader->ShaderID, glGetUniformBlockIndex(this->Shader->ShaderID, "SceneLightData_UBO"), 2);

			this->Unif_Translate = glGetUniformLocation(this->Shader->ShaderID, "Translate");
			this->Unif_Scale = glGetUniformLocation(this->Shader->ShaderID, "Scale");
			this->Unif_Object_Color = glGetUniformLocation(this->Shader->ShaderID, "ObjectColor");
		

			glBindVertexArray(this->VAO);
			
			glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
				glBufferData(GL_ARRAY_BUFFER, (sizeof(v4)+sizeof(v3))*60, nullptr, GL_DYNAMIC_DRAW);
				
				glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
				
				int buffer_offet = 0;
				int EBO_index = 0;
				for (int i = 0; i < face_count; i++) {
					//Retrive the 3 surface's point
					v3 point[3] = {}; 
					point[0] = this->ReadVector3(&hexagone_vertex_data_v3[hexagone_indice_data[EBO_index] * 3]);
					point[1] = this->ReadVector3(&hexagone_vertex_data_v3[hexagone_indice_data[EBO_index + 1] * 3]);
					point[2] = this->ReadVector3(&hexagone_vertex_data_v3[hexagone_indice_data[EBO_index + 2] * 3]); 
					v3 vec_U = point[0] - point[1];
					v3 vec_V = point[2] - point[1];
					v3 face_normal = glm::normalize(glm::cross(vec_V, vec_U));
					//v3 face_normal = glm::cross(vec_V, vec_U);
					for (int c = 0; c < vertex_per_face; c++) {
						glBufferSubData(GL_ARRAY_BUFFER, buffer_offet, sizeof(v4), &v4(point[c],1.f));
						buffer_offet += sizeof(v4);
						glBufferSubData(GL_ARRAY_BUFFER, buffer_offet,sizeof(v3),&face_normal);
						buffer_offet += sizeof(v3);
						EBO_index += 1;
					}
				}
				

			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(v4)+sizeof(v3), (GLvoid*)0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(v4)+sizeof(v3), (GLvoid*)(sizeof(v4)));
			glEnableVertexAttribArray(1);
			glBindVertexArray(0);

			BuildableObject::EndBuilding();
		}
	};
	class PGSolidHexagoneMesh :public Mesh {
		private:
			GLuint EBO;
			GLuint Unif_Translate;
			GLuint Unif_Scale;
			GLuint Unif_Color;
		public:
			PGSolidHexagoneMesh() :
				Mesh(new PGShader(hexagone_vertex_shader, FragShaderColor4fUnif)) {
				glGenBuffers(1, &this->EBO);
			}
			~PGSolidHexagoneMesh() {
				glDeleteBuffers(1, &this->EBO);
			}
		void PGSolidHexagoneMesh::Render(v3 possition, v3 size, v4 color) {
			if (this->Mesh::IsBuild() == true) {
				this->Shader->Use();
				glBindVertexArray(this->VAO);

				glUniformMatrix4fv(this->Unif_Translate, 1, GL_FALSE, &glm::translate(m4(1.f), possition)[0][0]);
				glUniformMatrix4fv(this->Unif_Scale, 1, GL_FALSE, &glm::scale(m4(1.f), size)[0][0]);
				glUniform4fv(this->Unif_Color, 1, &color[0]);

				glDrawElements(GL_TRIANGLES, 60 , GL_UNSIGNED_INT, 0);
			}
		}
		void PGSolidHexagoneMesh::Build() {
			BuildableObject::StartBuilding();

			glUniformBlockBinding(this->Shader->ShaderID, glGetUniformBlockIndex(this->Shader->ShaderID, "Renderer_UBO"), 1);

			this->Unif_Translate = glGetUniformLocation(this->Shader->ShaderID, "Translate");
			this->Unif_Scale = glGetUniformLocation(this->Shader->ShaderID, "Scale");
			this->Unif_Color = glGetUniformLocation(this->Shader->ShaderID, "FragColor");

			glBindVertexArray(this->VAO);
			
			glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(hexagone_vertex_data_v3), hexagone_vertex_data_v3, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(hexagone_indice_data), hexagone_indice_data, GL_STATIC_DRAW);


			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(v3), (GLvoid*)0);
			glEnableVertexAttribArray(0);
			glBindVertexArray(0);

			BuildableObject::EndBuilding();
		}
	};
	class PGMaterielHexagoneMesh :public Mesh {
		private:
			GLuint EBO;
			GLuint Unif_Translate;
			GLuint Unif_Scale;

			GLuint Unif_Mat_Ambient;
			GLuint Unif_Mat_Diffuse;
			GLuint Unif_Mat_Specular;
			GLuint Unif_Mat_Shinniness;
		public:
			PGMaterielHexagoneMesh() :
				Mesh(new PGShader(light_vertex_shader, FragShaderMaterializeLight)) {
				glGenBuffers(1, &this->EBO);
			}
			~PGMaterielHexagoneMesh() {
			//	glDeleteBuffers(1, &this->EBO);
			}
			v3 ReadVector3(const GLfloat* target) {
				v3 vec = {};
				vec.x = *target;
				target++;
				vec.y = *target;
				target++;
				vec.z = *target;
				target++;
				return vec;
			}
			void PGMaterielHexagoneMesh::Render(v3 possition, v3 size, const PGMaterial* material) {
				if (this->Mesh::IsBuild() == true) {
					this->Shader->Use();
					glBindVertexArray(this->VAO);

					//Vertex shader uniform variable
					glUniformMatrix4fv(this->Unif_Translate, 1, GL_FALSE, &glm::translate(m4(1.f), possition)[0][0]);
					glUniformMatrix4fv(this->Unif_Scale, 1, GL_FALSE, &glm::scale(m4(1.f), size)[0][0]);
				
					// Set material properties
					glUniform3fv(Unif_Mat_Ambient, 1, &material->ambient[0]);
					glUniform3fv(Unif_Mat_Diffuse, 1, &material->diffuse[0]);
					glUniform3fv(Unif_Mat_Specular, 1, &material->specular[0]); 
					glUniform1f(Unif_Mat_Shinniness, material->shininess);

					glDrawArrays(GL_TRIANGLES, 0, 60);
				}
			}
			void PGMaterielHexagoneMesh::Build() {
				BuildableObject::StartBuilding();
					int face_count = 20;
					int vertex_per_face = 3;

					glUniformBlockBinding(this->Shader->ShaderID, glGetUniformBlockIndex(this->Shader->ShaderID, "Renderer_UBO"), 1);
					glUniformBlockBinding(this->Shader->ShaderID, glGetUniformBlockIndex(this->Shader->ShaderID, "SceneAdvanceLightData_UBO"), 3);


					this->Unif_Translate = glGetUniformLocation(this->Shader->ShaderID, "Translate");
					this->Unif_Scale = glGetUniformLocation(this->Shader->ShaderID, "Scale");
					
					this->Unif_Mat_Ambient = glGetUniformLocation(this->Shader->ShaderID, "Material.ambient");
					this->Unif_Mat_Diffuse = glGetUniformLocation(this->Shader->ShaderID, "Material.diffuse");
					this->Unif_Mat_Specular = glGetUniformLocation(this->Shader->ShaderID, "Material.specular");
					this->Unif_Mat_Shinniness = glGetUniformLocation(this->Shader->ShaderID, "Material.shininess");

					glBindVertexArray(this->VAO);

					glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
					glBufferData(GL_ARRAY_BUFFER, (sizeof(v4)+sizeof(v3)) * 60, nullptr, GL_DYNAMIC_DRAW);

					
					int buffer_offet = 0;
					int EBO_index = 0;
					for (int i = 0; i < face_count; i++) {
						//Retrive the 3 surface's point
						v3 point[3] = {};
						point[0] = this->ReadVector3(&hexagone_vertex_data_v3[hexagone_indice_data[EBO_index] * 3]);
						point[1] = this->ReadVector3(&hexagone_vertex_data_v3[hexagone_indice_data[EBO_index + 1] * 3]);
						point[2] = this->ReadVector3(&hexagone_vertex_data_v3[hexagone_indice_data[EBO_index + 2] * 3]);
						v3 vec_U = point[0] - point[1];
						v3 vec_V = point[2] - point[1];
						v3 face_normal = glm::normalize(glm::cross(vec_V, vec_U));
						//v3 face_normal = glm::cross(vec_V, vec_U);
						for (int c = 0; c < vertex_per_face; c++) {
							glBufferSubData(GL_ARRAY_BUFFER, buffer_offet, sizeof(v4), &v4(point[c], 1.f));
							buffer_offet += sizeof(v4);
							glBufferSubData(GL_ARRAY_BUFFER, buffer_offet, sizeof(v3), &face_normal);
							buffer_offet += sizeof(v3);
							EBO_index += 1;
						}
					}


					glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(v4)+sizeof(v3), (GLvoid*)0);
					glEnableVertexAttribArray(0);
					glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(v4)+sizeof(v3), (GLvoid*)(sizeof(v4)));
					glEnableVertexAttribArray(1);
					glBindVertexArray(0);

				BuildableObject::EndBuilding();
		}
	};
	class PGUIPanelMesh :public Mesh {
		private:
			GLuint EBO;
			GLuint Unif_Translate;
			GLuint Unif_Scale;
			GLuint Unif_Color;
		public:
			PGUIPanelMesh() :
				Mesh(new PGShader(ui_panel_vertex_shader, FragShaderColor4fUnif)) {
				glGenBuffers(1, &this->EBO);
			
			}
			~PGUIPanelMesh() {
				glDeleteBuffers(1, &this->EBO);
			}
			void PGUIPanelMesh::Render(v3 possition,v2 size,v4 color) {
				if (this->Mesh::IsBuild() == true) {
					this->Shader->Use();
					glBindVertexArray(this->VAO);

					glUniformMatrix4fv(this->Unif_Translate, 1, GL_FALSE, &glm::translate(m4(1.f), possition)[0][0]);
					glUniformMatrix4fv(this->Unif_Scale, 1, GL_FALSE, &glm::scale(m4(1.f), v3(size,0.f))[0][0]);
					glUniform4fv(this->Unif_Color, 1, &color[0]);

					glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
				}
			}
			void PGUIPanelMesh::Build() {
				BuildableObject::StartBuilding();
				// .:: Bind UBO ::. 
				glUniformBlockBinding(this->Shader->ShaderID, glGetUniformBlockIndex(this->Shader->ShaderID, "Renderer_UBO"), 1);

				this->Unif_Translate = glGetUniformLocation(this->Shader->ShaderID, "Translate");
				this->Unif_Scale = glGetUniformLocation(this->Shader->ShaderID, "Scale");
				this->Unif_Color = glGetUniformLocation(this->Shader->ShaderID, "FragColor");

				glBindVertexArray(this->VAO);
					glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
					glBufferData(GL_ARRAY_BUFFER, sizeof(panel_vertices), panel_vertices, GL_STATIC_DRAW);

					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(panel_indices), panel_indices, GL_STATIC_DRAW);
			

				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(v3), (GLvoid*)0);
				glEnableVertexAttribArray(0);
				glBindVertexArray(0);

				BuildableObject::EndBuilding();
			}
	};
	class PGUIImageMesh :public Mesh {
		private:
			GLuint EBO;
			GLuint Unif_Translate;
			GLuint Unif_Scale;
			GLuint Unif_Rotate;
			GLuint Unif_Color_Channel;
		public:
			PGUIImageMesh() :
				Mesh(new PGShader(texture_vertex_shader, texture_fragment_shader)) {
				glGenBuffers(1, &this->EBO);
			}
			~PGUIImageMesh() {
				glDeleteBuffers(1, &this->EBO);
			}
			void PGUIImageMesh::Render(v3 possition, v2 size, Texture* texture = nullptr,v4 color_chanel = v4(1.f),r32 orientation = 0.f) {
					this->Shader->Use();
					glBindVertexArray(this->VAO);
					glBindTexture(GL_TEXTURE_2D, texture->OpenGL_Id);
						glUniformMatrix4fv(this->Unif_Translate, 1, GL_FALSE, &glm::translate(m4(1.f), possition)[0][0]);
						glUniformMatrix4fv(this->Unif_Scale, 1, GL_FALSE, &glm::scale(m4(1.f), v3(size, 1.0f))[0][0]);
						glUniformMatrix4fv(this->Unif_Rotate, 1, GL_FALSE, &glm::rotate(m4(1.f), glm::radians(orientation), v3(0.0f, 0.0f, 1.0f))[0][0]);
						glUniform4fv(this->Unif_Color_Channel, 1, &color_chanel[0]);
					glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			}
			void PGUIImageMesh::Build() {

			Shader->Use();
			glUniformBlockBinding(this->Shader->ShaderID,	glGetUniformBlockIndex(this->Shader->ShaderID, "Renderer_UBO"),	1);
			
			this->Unif_Translate = glGetUniformLocation(this->Shader->ShaderID, "Translate");
			this->Unif_Scale = glGetUniformLocation(this->Shader->ShaderID, "Scale");
			this->Unif_Rotate = glGetUniformLocation(this->Shader->ShaderID, "Rotate");
			this->Unif_Color_Channel = glGetUniformLocation(this->Shader->ShaderID, "Color_Channel");

			glBindVertexArray(this->VAO);
			
				glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(top_left_align_texture_vertices), top_left_align_texture_vertices, GL_STATIC_DRAW);

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(texture_indices), texture_indices, GL_STATIC_DRAW);
			
				glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(v4)+sizeof(v2), (GLvoid*)0);
					glEnableVertexAttribArray(0);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(v4)+sizeof(v2), (GLvoid*)sizeof(v4));
					glEnableVertexAttribArray(1);
			
			glBindVertexArray(0);
		}
	};
	class PGTileMesh : public Mesh {
	private:
	public:
		PGTileMesh(): 
			Mesh(new PGShader(tile_vertex_shader, tile_fragment_shader)) {
		}
		~PGTileMesh() {
		}
		void PGTileMesh::Render() {

		}
		void PGTileMesh::Build() {

		}
	};




		class PGMModelMesh :public Mesh {
		private:
			GLuint Unif_Translate;
			GLuint Unif_Scale;

		public:
			PGMModelMesh() :
				Mesh(new PGShader(model_vertex_shader, Model_FragShader)) {
			}
			~PGMModelMesh() {
				
			}
			void PGMModelMesh::Render(RawModelData* model, v3 possition, v3 size/*, const PGMaterial* material*/) {
				if (this->Mesh::IsBuild() == true) {
					this->Shader->Use();
					glBindVertexArray(model->VAO);

					//Vertex shader uniform variable
					glUniformMatrix4fv(this->Unif_Translate, 1, GL_FALSE, &glm::translate(m4(1.f), possition)[0][0]);
					glUniformMatrix4fv(this->Unif_Scale, 1, GL_FALSE, &glm::scale(m4(1.f), size)[0][0]);

					//// Set material properties
					//glUniform3fv(Unif_Mat_Ambient, 1, &material->ambient[0]);
					//glUniform3fv(Unif_Mat_Diffuse, 1, &material->diffuse[0]);
					//glUniform3fv(Unif_Mat_Specular, 1, &material->specular[0]);
					//glUniform1f(Unif_Mat_Shinniness, material->shininess);

					glDrawArrays(GL_TRIANGLES, 0, model->face_count*3);
				}
			}
			void PGMModelMesh::Build() {
				BuildableObject::StartBuilding();
				glUniformBlockBinding(this->Shader->ShaderID, glGetUniformBlockIndex(this->Shader->ShaderID, "Renderer_UBO"), 1);
				glUniformBlockBinding(this->Shader->ShaderID, glGetUniformBlockIndex(this->Shader->ShaderID, "SceneAdvanceLightData_UBO"), 3);


				this->Unif_Translate = glGetUniformLocation(this->Shader->ShaderID, "Translate");
				this->Unif_Scale = glGetUniformLocation(this->Shader->ShaderID, "Scale");


				BuildableObject::EndBuilding();
			}
		};

#endif