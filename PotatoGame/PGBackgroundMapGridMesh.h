#if !defined(PG_MESH_BACKGROUND_H)
#define PG_MESH_BACKGROUND_H


#include "stdafx.h"
#include "AssetManager.h"
#include "Core.h"
#include "List.h"
#include "PGShaderSources.h"
#include "Mesh.h"
#include "Font.h"

#include "PGMapGrid.h"

using namespace PG::Engine;


#if 1
	PG_SHADER(const char* map_hexa_vertex_shader = GLSL330(
		layout(location = 0) in vec4 vertex_position; //<- world space already
		layout(location = 1) in vec3 vertex_normal;
		layout(location = 2) in vec3 ambient;
		layout(location = 3) in vec3 diffuse;
		layout(location = 4) in vec3 specular;
		layout(location = 5) in vec4 shininess;

		struct PGMaterial {
			vec3 ambient;
			vec3 diffuse;
			vec3 specular;
			float shininess;
		};

		uniform mat4 Translate; //Note(Marc): will translate all the world space coord of the map

		out vec3 Normal;
		out vec3 FragPos;
		out vec4 Vertex_World_Possiton;

		out PGMaterial Matl;

		layout(std140) uniform Renderer_UBO
		{
			mat4 WorldProjection;
			mat4 WorldView;
			mat4 GUIProjection;
			vec4 CenterOfFog;
		};


		void main() {
			Vertex_World_Possiton = (Translate)* vertex_position;
			Matl.ambient = ambient;
			Matl.diffuse = diffuse;
			Matl.specular = specular;
			Matl.shininess = shininess.x;
			gl_Position = WorldProjection  * WorldView * Vertex_World_Possiton;
			FragPos = vec3(WorldView*(Translate) * vertex_position);
			Normal = mat3(transpose(inverse(WorldView /**  Translate*/ ))) * vertex_normal;
		}
	));
	PG_SHADER(const char* map_hexa_FragShader = GLSL330(
		struct PGMaterial {
			vec3 ambient;
			vec3 diffuse;
			vec3 specular;
			float shininess;
		};
		struct PGLight {
			vec4 position;
			vec4 ambient;
			vec4 diffuse;
			vec4 specular;
		};


		layout(std140) uniform Renderer_UBO
		{
			mat4 WorldProjection;
			mat4 WorldView;
			mat4 GUIProjection;
			vec4 CenterOfFog; // ->W = radius
		};
		layout(std140) uniform SceneAdvanceLightData_UBO
		{
			PGLight Light;
		};

		in vec3 Normal;
		in vec3 FragPos;
		in PGMaterial Matl;
		in vec4 Vertex_World_Possiton;

		out vec4 color;

		void main() {
			float alpha = 1.f;
			float radius_fog  = 15;
			float decay_lenght = 4;
			float dist = distance(CenterOfFog, Vertex_World_Possiton);
			if (dist > radius_fog) {
				dist -= radius_fog;
				alpha = 1 - dist / decay_lenght;
				if (dist > decay_lenght) {
					alpha = 0.0f;
				}
			}
			// Ambient
			vec3 ambient = vec3(Light.ambient) * Matl.ambient;

			// Diffuse 
			vec3 LightPos = vec3(WorldView * Light.position);
			vec3 norm = normalize(Normal);
			vec3 lightDir = normalize(LightPos - FragPos);
			float diff = max(dot(norm, lightDir), 0.0f);
			vec3 diffuse = vec3(Light.diffuse) * (diff * Matl.diffuse);

			vec3 viewDir = normalize(-FragPos); // The viewer is at(0, 0, 0) so viewDir is(0, 0, 0) - Position = > -Position
			vec3 reflectDir = reflect(-lightDir, norm);
			float spec = pow(max(dot(viewDir, reflectDir), 0.0), Matl.shininess);
			vec3 specular = vec3(Light.specular) * (spec * Matl.specular);

			//Combine each	colors
			color = vec4((ambient + diffuse + specular), 1.0f);

		}
	));
#endif
	class PGMapMesh : public Mesh {
	private:
	public:
		int vertix_count;
		GLuint Unif_Translate;
		PGGridRawData *grid_data;
		PGMapMesh(PGGridRawData *_grid_data) :
			Mesh(new PGShader(map_hexa_vertex_shader, map_hexa_FragShader)) {
			grid_data = _grid_data;
			Unif_Translate = 0;
		}
		~PGMapMesh() {

		}
		virtual void PGMapMesh::Render(v3 possition)  {
			if (this->Mesh::IsBuild() == true) {
				this->Shader->Use();
				glBindVertexArray(this->VAO);
				//Vertex shader uniform variable
				glUniformMatrix4fv(this->Unif_Translate, 1, GL_FALSE, &glm::translate(m4(1.f), possition)[0][0]);

				glDrawArrays(GL_TRIANGLES, 0, vertix_count);
			}
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
		virtual void PGMapMesh::Build()  {
			BuildableObject::StartBuilding();

			glUniformBlockBinding(this->Shader->ShaderID, glGetUniformBlockIndex(this->Shader->ShaderID, "Renderer_UBO"), 1);
			glUniformBlockBinding(this->Shader->ShaderID, glGetUniformBlockIndex(this->Shader->ShaderID, "SceneAdvanceLightData_UBO"), 3);


			this->Unif_Translate = glGetUniformLocation(this->Shader->ShaderID, "Translate");

			//Build the Vao buffer
			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);


			//Note(Marc):	This is a solution for rendering bottleneck for back ground with
			//					this we could easily add environment vertex
			int face_count = 17;
			int vertex_per_face = 3;
			int per_model_vertex = face_count*vertex_per_face; //Hexagone mesh , maybe we should centralize mesh data like ths
			v2 grid_size = grid_data->Grid_size;
			int element_count = grid_size.x*grid_size.y;
			int  per_vertex_data_lenght =
				sizeof(v4)+ //LOC (0)
				sizeof(v3)+ //LOC (1)
				sizeof(v3)+ //LOC (2)
				sizeof(v3)+ //LOC (3)
				sizeof(v3)+ //LOC (4)
				sizeof(v4); //LOC (5)

			vertix_count = per_vertex_data_lenght *per_model_vertex*element_count;
			glBufferData(GL_ARRAY_BUFFER, per_vertex_data_lenght *per_model_vertex*element_count, nullptr, GL_DYNAMIC_DRAW);
			int data_buffer_cursor = 0;
			
			m4 scale_matrix = m4(1.f);
			m4 translate_matrix = m4(1.f);
			for (int grid_index = 0; grid_index< element_count; grid_index++) {
				PGMaterial* current_mat = &grid_data->grid_material_data[grid_index];
				translate_matrix = glm::translate(m4(1.f), v3(grid_data->grid_pos_data[grid_index].x, grid_data->grid_pos_data[grid_index].y,0.f));
				scale_matrix = glm::scale(m4(1.f), v3(1.f,1.f, grid_data->grid_height_data[grid_index])); //Z = tile height
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
					for (int c = 0; c < vertex_per_face; c++) {
						v4 posstion_world_space = translate_matrix*scale_matrix*v4(point[c], 1.f);
						//Possition world space
						glBufferSubData(GL_ARRAY_BUFFER, data_buffer_cursor, sizeof(v4), &posstion_world_space);
						data_buffer_cursor += sizeof(v4);
						//Normal
						glBufferSubData(GL_ARRAY_BUFFER, data_buffer_cursor, sizeof(v3), &face_normal);
						data_buffer_cursor += sizeof(v3);
						//Material info
						glBufferSubData(GL_ARRAY_BUFFER, data_buffer_cursor, sizeof(v3), &current_mat->ambient); //Note dont know bender
						data_buffer_cursor += sizeof(v3);
						glBufferSubData(GL_ARRAY_BUFFER, data_buffer_cursor, sizeof(v3), &current_mat->diffuse);
						data_buffer_cursor += sizeof(v3);
						glBufferSubData(GL_ARRAY_BUFFER, data_buffer_cursor, sizeof(v3), &current_mat->specular);
						data_buffer_cursor += sizeof(v3);
						glBufferSubData(GL_ARRAY_BUFFER, data_buffer_cursor, sizeof(v4), &v4(current_mat->shininess, 1.f, 1.f, 1.f));
						data_buffer_cursor += sizeof(v4);
						
					}
					EBO_index += vertex_per_face;
				}
			}

			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, per_vertex_data_lenght, (GLvoid*)0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, per_vertex_data_lenght, (GLvoid*)(sizeof(v4)));
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, per_vertex_data_lenght, (GLvoid*)(sizeof(v4)+sizeof(v3)));
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, per_vertex_data_lenght, (GLvoid*)(sizeof(v4)+2 * sizeof(v3)));
			glEnableVertexAttribArray(3);
			glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, per_vertex_data_lenght, (GLvoid*)(sizeof(v4)+3 * sizeof(v3)));
			glEnableVertexAttribArray(4);
			glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, per_vertex_data_lenght, (GLvoid*)(sizeof(v4)+4 * sizeof(v3)));
			glEnableVertexAttribArray(5);
			glBindVertexArray(0);
			BuildableObject::EndBuilding();
		}
	};

#endif