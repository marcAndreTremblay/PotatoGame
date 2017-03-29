#if !defined(PG_GAME_MODEL_H)
#define PG_GAME_MODEL_H

#include "List.h"
#include "EngineObjectList.h"
#include "Font.h"
#include "Texture.h"

using namespace PG::Core;


namespace PG {
	namespace Engine {

		class RawMateriel {
		public:
			int Id;
			Str *Name;
			r32 Shininess;
			v3 Ambient;
			v3 Diffuse;
			v3 Specular;
			RawMateriel(char* name, int id) {
				Name = new Str(name);
				Id = id;
			}
			~RawMateriel() {
				delete(Name);
			}

		};
		class RawMaterielData {
			int count;
		public:
			List<RawMateriel> *RawMateriels;
			RawMateriel* RawMaterielData::FindByNameRef(char* name) {
				for (ListNode<RawMateriel> *c_node = this->RawMateriels->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
					RawMateriel* current_element = c_node->GetData();
					if (current_element->Name->Compare(new Str(name)) == true) {
						return current_element;
					}
				}
				return nullptr;
			}
			RawMateriel* RawMaterielData::FindByNameId(int target_id) {
				for (ListNode<RawMateriel> *c_node = this->RawMateriels->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
					RawMateriel* current_element = c_node->GetData();
					if (current_element->Id == target_id) {
						return current_element;
					}
				}
				return nullptr;
			}

			RawMaterielData(char * FILE_PATH) {
				RawMateriels = new List<RawMateriel>(true);
				RawMateriel *last_new_mat;
				int id = 0;
				FILE * file = fopen(FILE_PATH, "r");
				if (file != nullptr) {
					char lineHeader[128];
					while (1) {
						int res = fscanf(file, "%s", lineHeader);
						if (res == EOF) {
							break; // EOF = End Of File. Quit the loop.
						}
						else if (strcmp(lineHeader, "newmtl") == 0) {
							int match_cpt = fscanf(file, "%s", lineHeader);


							char *path = new char[254];
							sprintf(&path[0], "%s\n", lineHeader);

							last_new_mat = nullptr;
							last_new_mat = new RawMateriel(path, id);
							id = id + 1;
							RawMateriels->Add(last_new_mat);
							if (match_cpt != 1) {
								printf("Error reading mat name |\n");
							}
						}
						else if (strcmp(lineHeader, "Count:") == 0) {
							int match_cpt = fscanf_s(file, " %i\n", &count);
							if (match_cpt != 1) {
								printf("Error reading mat count |\n");
							}
						}
						else if (strcmp(lineHeader, "Ns") == 0) {
							int match_cpt = fscanf_s(file, " %f\n", &last_new_mat->Shininess);
							if (match_cpt != 1) {
								printf("Error reading alpha |\n");
							}
						}
						else if (strcmp(lineHeader, "Ke") == 0) {
							v3 *c_data = &last_new_mat->Ambient;
							int match_cpt = fscanf_s(file, " %f %f %f \n", &c_data->x, &c_data->y, &c_data->z);
							if (match_cpt != 3) {
								printf("Error reading ka |\n");
							}
						}
						else if (strcmp(lineHeader, "Kd") == 0) {
							v3 *c_data = &last_new_mat->Diffuse;
							int match_cpt = fscanf_s(file, " %f %f %f \n", &c_data->x, &c_data->y, &c_data->z);


							if (match_cpt != 3) {
								printf("Error reading kd |\n");
							}
						}
						else if (strcmp(lineHeader, "Ks") == 0) {
							v3 *c_data = &last_new_mat->Specular;
							int match_cpt = fscanf_s(file, " %f %f %f \n", &c_data->x, &c_data->y, &c_data->z);
							if (match_cpt != 3) {
								printf("Error reading k |\n");
							}
						}


					}
				}
				fclose(file);
			}
			~RawMaterielData() {

			}
		};

		class RawModelData {
		public:
			GLuint VAO;
			GLuint VBO;

			bool IsMaterialize;
			RawMaterielData *material_data;

			int v_count;
			int vn_count;
			int vt_count;
			int face_count;
			//Data arrays
			v3* vertices_array;
			v2* uvs_array;
			v3* normal_array;
			unsigned int* faces_array;
			~RawModelData() {
				glDeleteVertexArrays(1, &this->VAO);
				glDeleteBuffers(1, &this->VBO);
				delete(vertices_array);
				delete(uvs_array);
				delete(normal_array);
				delete(faces_array);
			}
			//Todo(Marc): Make this load from file function into a fct and it more solidify it
			RawModelData(char * FILE_PATH) {
				v_count = 0;
				vn_count = 0;
				vt_count = 0;
				face_count = 0;
				vertices_array = nullptr;
				uvs_array = nullptr;
				normal_array = nullptr;
				faces_array = nullptr;

				IsMaterialize = false;



				Str * file_path = new Str(FILE_PATH);
				Str * forlder_path = Str::ExtractFolderPath(file_path);

				FILE * file1 = fopen(FILE_PATH, "r");
				printf("Loading | Model | :\n");
				printf("\tFile path %s \n", file_path->CharAt());
				printf("\tFolder path %s \n", forlder_path->CharAt());

				if (file1 != nullptr) {
					char lineHeader[128]; //Note(Marc): We assume that a word wont be longer than 128 char, this is a silly assumtion
					while (1) {
						int res = fscanf(file1, "%s", lineHeader);
						if (res == EOF) {
							break; // EOF = End Of File. Quit the loop.
						}
						if (strcmp(lineHeader, "v") == 0) {
							v_count++;
						}
						else if (strcmp(lineHeader, "vn") == 0) {
							vn_count++;
						}
						else if (strcmp(lineHeader, "vt") == 0) {
							vt_count++;
						}
						else if (strcmp(lineHeader, "f") == 0) {
							face_count++;
						}
						else if (strcmp(lineHeader, "mtllib") == 0) {
							IsMaterialize = true;
							int res = fscanf(file1, "%s", lineHeader);
							int name_l = strlen(lineHeader);
							char *path = new char[254];

							sprintf(&path[0], "%s%s", forlder_path->CharAt(), lineHeader);
							material_data = new RawMaterielData(path);

						}
						else if (strcmp(lineHeader, "usemtl") == 0) {
							int res = fscanf(file1, "%s", lineHeader);
						}
						else if (strcmp(lineHeader, "s") == 0) {

						}

					}
				}
				fclose(file1);


				vertices_array = new v3[v_count];
				uvs_array = new v2[vt_count];
				normal_array = new v3[vn_count];
				if (IsMaterialize == true) {
					faces_array = new unsigned int[face_count * 9];
				}
				else {
					faces_array = new unsigned int[face_count * 6];
				}



				int v_c_index = 0;
				int vn_c_index = 0;
				int vt_c_index = 0;
				int f_c_index = 0;


				RawMateriel *current_material_data;
				FILE * file = fopen(FILE_PATH, "r");
				if (file != nullptr) {
					char lineHeader[128]; //Note(Marc): We assume that a word wont be longer than 128 char, this is a silly assumtion
					while (1) {
						int res = fscanf(file, "%s", lineHeader);
						if (res == EOF) {
							break; // EOF = End Of File. Quit the loop.
						}
						if (strcmp(lineHeader, "v") == 0) {
							v3 *c_v_data = &vertices_array[v_c_index];
							int match_cpt = fscanf_s(file, " %f %f %f \n", &c_v_data->x, &c_v_data->y, &c_v_data->z);
							if (match_cpt != 3) {
								printf("Error reading vertices Num:|%i|\n", v_c_index);
							}
							v_c_index++;
						}
						else if (strcmp(lineHeader, "vn") == 0) {
							v3 *c_vn_data = &normal_array[vn_c_index];
							int match_cpt = fscanf_s(file, " %f %f %f \n", &c_vn_data->x, &c_vn_data->y, &c_vn_data->z);
							if (match_cpt != 3) {
								printf("Error reading vertices normal #:|%i|:\n", vn_c_index);
							}
							//printf("- Normal  #:|%i|: %f %f %f\n", vn_c_index, c_vn_data->x, c_vn_data->y, c_vn_data->z);
							vn_c_index++;
						}
						else if (strcmp(lineHeader, "vt") == 0) {
							v2 *c_vt_data = &uvs_array[vt_c_index];
							int match_cpt = fscanf_s(file, "%f %f\n", &c_vt_data->x, &c_vt_data->y);
							if (match_cpt != 2) {
								printf("Error reading Tex coords Num:|%i|\n", vt_c_index);
							}
							vt_c_index++;
						}
						else if (strcmp(lineHeader, "f") == 0) {
							unsigned int *face_data = &faces_array[f_c_index];

							if (IsMaterialize == true) {
								int match_cpt = fscanf(file, "%d//%d %d//%d %d//%d\n", &face_data[0], &face_data[1], &face_data[3],
									&face_data[4], &face_data[6], &face_data[7]);
								if (match_cpt != 6) {
									printf("Error reading face data\n");
								}
								if (current_material_data != nullptr) {
									face_data[2] = current_material_data->Id;
									face_data[5] = current_material_data->Id;
									face_data[8] = current_material_data->Id;
								}
								else {
									printf("Error reading mat index\n");
								}
								f_c_index = f_c_index + 9;
							}
							if (IsMaterialize == false) {
								int match_cpt = fscanf(file, "%d//%d %d//%d %d//%d\n", &face_data[0], &face_data[1], &face_data[2],
									&face_data[3], &face_data[4], &face_data[5]);
								if (match_cpt != 6) {
									printf("Error reading face data\n");
								}
								f_c_index = f_c_index + 6;
							}

						}
						else if (strcmp(lineHeader, "usemtl") == 0) {
							int res = fscanf(file, "%s", lineHeader);
							char ref_name[128];
							sprintf(&ref_name[0], "%s\n", lineHeader);
							current_material_data = material_data->FindByNameRef(ref_name);
						}
						else if (strcmp(lineHeader, "s") == 0) {

						}

					}
				}
				fclose(file);
			}

			GLuint RawModelData::LoadIntoVAO() {

				glGenVertexArrays(1, &VAO);
				glGenBuffers(1, &VBO);

				glBindVertexArray(VAO);
				glBindBuffer(GL_ARRAY_BUFFER, VBO);
				int per_vertex_data_lenght = 0;
				if (this->IsMaterialize == true) {
					per_vertex_data_lenght =
						sizeof(v4)+ //LOC (0)
						sizeof(v3)+ //LOC (1)
						sizeof(v3)+ //LOC (2)
						sizeof(v3)+ //LOC (3)
						sizeof(v3)+ //LOC (4)
						sizeof(v4); //LOC (5)
				}
				else {
					per_vertex_data_lenght =
						sizeof(v4)+ //LOC (0)
						sizeof(v3); //LOC (0)

				}
				glBufferData(GL_ARRAY_BUFFER, per_vertex_data_lenght * face_count * 3, nullptr, GL_DYNAMIC_DRAW);

				int buffer_offet = 0;
				unsigned int *faces_array_ptr = &faces_array[0];
				for (int i = 0; i < face_count * 3; i++) {
					//Add v4
					if (this->IsMaterialize == true) {
						glBufferSubData(GL_ARRAY_BUFFER, buffer_offet, sizeof(v4), &v4(vertices_array[*faces_array_ptr - 1], 1.f));
						faces_array_ptr++;
						buffer_offet += sizeof(v4);


						glBufferSubData(GL_ARRAY_BUFFER, buffer_offet, sizeof(v3), &v4(normal_array[*faces_array_ptr - 1], 1.f));
						faces_array_ptr++;
						buffer_offet += sizeof(v3);

						//Material data added here	

						RawMateriel* current_mat = material_data->FindByNameId(*faces_array_ptr);

						glBufferSubData(GL_ARRAY_BUFFER, buffer_offet, sizeof(v3), &current_mat->Ambient); //Note dont know bender
						buffer_offet += sizeof(v3);
						glBufferSubData(GL_ARRAY_BUFFER, buffer_offet, sizeof(v3), &current_mat->Diffuse);
						buffer_offet += sizeof(v3);
						glBufferSubData(GL_ARRAY_BUFFER, buffer_offet, sizeof(v3), &current_mat->Specular);
						buffer_offet += sizeof(v3);
						glBufferSubData(GL_ARRAY_BUFFER, buffer_offet, sizeof(v4), &v4(current_mat->Shininess, 1.f, 1.f, 1.f));
						buffer_offet += sizeof(v4);


						faces_array_ptr++;
					}
					if (this->IsMaterialize == false) {
						glBufferSubData(GL_ARRAY_BUFFER, buffer_offet, sizeof(v4), &v4(vertices_array[*faces_array_ptr - 1], 1.f));
						faces_array_ptr++;
						buffer_offet += sizeof(v4);
						//Add v3

						glBufferSubData(GL_ARRAY_BUFFER, buffer_offet, sizeof(v3), &v4(normal_array[*faces_array_ptr - 1], 1.f));
						faces_array_ptr++;
						buffer_offet += sizeof(v3);
					}


				}
				if (this->IsMaterialize == true) {
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
				}
				if (this->IsMaterialize == false) {
					glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, per_vertex_data_lenght, (GLvoid*)0);
					glEnableVertexAttribArray(0);
					glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, per_vertex_data_lenght, (GLvoid*)(sizeof(v4)));
					glEnableVertexAttribArray(1);
					glBindVertexArray(0);
				}



				return VAO;
			}
		};
	}
}
#endif