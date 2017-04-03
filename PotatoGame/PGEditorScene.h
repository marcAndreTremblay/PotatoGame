	#if !defined(PG_EDITOR_SCENE_H)
#define PG_EDITOR_SCENE_H

#include "stdafx.h"

#include "Core.h"
#include "BaseRenderer.h"	
#include "Scene.h"
#include "Controler.h"
#include "Entity.h"
#include "String.h"
#include "Scene.h"
#include "BuildableObject.h"
#include "PGMapGrid.h"
#include "MousePicker.h"

#include "PGBackgroundMapGridMesh.h"
#include "PGMapAtlas.h"

using namespace PG::Core;
using namespace PG::Engine;

class PGTerrainEditorScene : public Scene {
	protected:
	private:
		PGMapAtlas * test_atlas;
		PGAtlasRegion* region_display[9];
		bool region_edited[9];
		
		PGLight scene_light;
		RawModelData *test_model;
		RawModelData *test_model2;
		RawModelData *test_model3;
		double time;
		double tempo_var;
	public:
		PGTerrainEditorScene()	: Scene() {
			this->time = 0.1f;
			this->tempo_var = 0.1f;
			this->scene_light = PGLight();
			this->scene_light.position = v4(15.f, 15.f, 14.f, 1.f);
			
			this->scene_light.diffuse = v4(1.f, 1.f, 1.f, 1.f);
			this->scene_light.ambient = v4(0.6f, 0.6f, 0.6f, 1.f);
			this->scene_light.specular = v4(0.6f, 0.6f, 0.6f, 1.f);
			for (int i = 0; i <= 9; i++) {
				region_display[i] = nullptr;
				region_edited[i] = false;
			}
			
		}
		~PGTerrainEditorScene() {
			
			
			delete(test_atlas);
		}
		void PGTerrainEditorScene::Update(Controler *controler, double timeElapse) override {
			Scene::Update(controler, timeElapse);
		}
		void PGTerrainEditorScene::Render(BaseRenderer *renderer) override {
			Scene::Render(renderer);
	
			renderer->PushLightPossition(&scene_light.position);;
			renderer->PushLightData(&scene_light);

			renderer->axisMesh->Render(v3(0.f, 0.f, 0.f), v4(0.f, 0.f, 1.f, 1.f));
			renderer->cubeMesh->Render(v3(scene_light.position.x, scene_light.position.y, scene_light.position.z), v3(0.1f, 0.1f, 0.1f), scene_light.diffuse);
			

			if (test_model2 != nullptr) {
				renderer->model_renderer->Render(test_model2, v3(10.f, 10.f, 17.f), v3(3.f, 3.f, 3.f));
			}
			if (test_model3 != nullptr) {
				renderer->model_renderer->Render(test_model3, v3(17.f, 17.f, 17.f), v3(1.2f, 1.2f, 1.2f));
			}
			

				PGGridRawData *grid_data = region_display[4]->grid;
				v3 possition_offset = v3(grid_data->CalculateNextMapOffetPossition(1), grid_data->CalculateNextMapOffetPossition(2), 0.f);
				v3 possition_cursor = v3(0.f) - possition_offset;
				for (int grid_index = 0;grid_index < 9;	grid_index++) {
					if (grid_index % 3 == 0 && grid_index != 0) {
						possition_cursor.y += possition_offset.y;
						possition_cursor.x -= possition_offset.x*3;
					}
					if (region_edited[grid_index] == true) {
							PGGridRawData *grid = region_display[grid_index]->grid;
							v3 possition;
							v3 scale;
							for (int grid_index = 0;
								grid_index < grid->Grid_size.x*grid->Grid_size.y;
								grid_index++) {
								possition = possition_cursor + v3(grid->grid_pos_data[grid_index]);
								scale = v3(grid->Tile_size, grid->Tile_size, grid->grid_height_data[grid_index]);
								if (grid->selected_indexes[grid_index] == true) {
									renderer->materialHexagoneMesh->Render(possition, scale, &Material_Copper);
								}
								else {
									renderer->materialHexagoneMesh->Render(possition, scale, &grid->grid_material_data[grid_index]);
								}
								if (grid->tile_type[grid_index] == 1) {
									renderer->model_renderer->Render(test_model3, v3(possition.x, possition.y, scale.z), v3(1.f, 1.f, 1.f));
								}
								if (grid->tile_type[grid_index] == 2) {
									renderer->model_renderer->Render(test_model, v3(possition.x, possition.y, scale.z), v3(1.f, 1.f, 1.f));
								}
							}
						}
					
					else {
						if(region_display[grid_index] != nullptr){
							region_display[grid_index]->region_mesh->Render(possition_cursor);
						}
					}
					
					possition_cursor.x += possition_offset.x;
					
				}
			
		}

		void PGTerrainEditorScene::Build(MousePicker* mouse_picker) {
			Scene::Build(mouse_picker);

			this->Set_Name("GridEditorScene");			
			
			this->scene_camera = new Camera(
					v3(-15, -15, 15), //Possition
					v3(0, 0, 0), //look at
					v3(0, 0, 1)	 //up
					);
			this->Projection_Matrice = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 150.0f);
			
			test_model = new RawModelData("Asset/RawOBJ/city_1_0.obj");
			test_model->LoadIntoVAO();

			test_model3 = new RawModelData("Asset/RawOBJ/tree_2_0.obj");
			test_model3->LoadIntoVAO();

			test_model2 = new RawModelData("Asset/RawOBJ/spere2.obj");
			test_model2->LoadIntoVAO();

			

		

			int edit_target = 171;
			//Load atlas
			test_atlas = new PGMapAtlas("Asset/map/AtlasMap.txt");
			//Load require region data from their file using the new loaded atlas
			test_atlas->LoadRegionsAndFillDisplayTemplate(edit_target, &region_display[0]);
			region_edited[4] = true;
			region_edited[3] = true;
			region_edited[1] = true;
			this->ShouldRender = true;
		}
		void PGTerrainEditorScene::HandleControler(Controler *controler) override {
			Scene::HandleControler(controler);
			float speed = 0.15f;
			
			PGGridRawData *grid_data = region_display[4]->grid;
			if (controler->GetKey(PGKey_Left_Ctrl)->IsPress == true) {
				if (controler->IsRelease(PGKey_1) == true) {
					for (int i = 0; i < 9; i++) {
						if (region_edited[i] == true) {
							PGGridRawData *grid = region_display[i]->grid;
							for (int grid_index = 0;
								grid_index < grid->Grid_size.x*grid->Grid_size.y;
								grid_index++) {
								if (grid->selected_indexes[grid_index] == true) {
									grid->grid_material_data[grid_index] = Material_Green;
								}
							}
						}
					}
				}
				if (controler->IsRelease(PGKey_2) == true) {
					for (int i = 0; i < 9; i++) {
						if (region_edited[i] == true) {
							PGGridRawData *grid = region_display[i]->grid;
							for (int grid_index = 0;
								grid_index < grid->Grid_size.x*grid->Grid_size.y;
								grid_index++) {
								if (grid->selected_indexes[grid_index] == true) {
									grid->grid_material_data[grid_index] = Material_Brown_1;
								}
							}
						}
					}
				}
				if (controler->IsRelease(PGKey_3) == true) {
					for (int i = 0; i < 9; i++) {
						if (region_edited[i] == true) {
							PGGridRawData *grid = region_display[i]->grid;
							for (int grid_index = 0;
								grid_index < grid->Grid_size.x*grid->Grid_size.y;
								grid_index++) {
								if (grid->selected_indexes[grid_index] == true) {
									grid->grid_material_data[grid_index] = Material_Gray;
								}
							}
						}
					}
				}
				if (controler->IsRelease(PGKey_4) == true) {
					for (int i = 0; i < 9; i++) {
						if (region_edited[i] == true) {
							PGGridRawData *grid = region_display[i]->grid;
							for (int grid_index = 0;
								grid_index < grid->Grid_size.x*grid->Grid_size.y;
								grid_index++) {
								if (grid->selected_indexes[grid_index] == true) {
									grid->grid_material_data[grid_index] = Material_Blue;
								}
							}
						}
					}
				}
				if (controler->IsRelease(PGKey_5) == true) {
					for (int i = 0; i < 9; i++) {
						if (region_edited[i] == true) {
							PGGridRawData *grid = region_display[i]->grid;
							for (int grid_index = 0;
								grid_index < grid->Grid_size.x*grid->Grid_size.y;
								grid_index++) {
								if (grid->selected_indexes[grid_index] == true) {
									grid->tile_type[grid_index] =1;
								}
							}
						}
					}
				}
				if (controler->IsRelease(PGKey_7) == true) { //Align all tile height
					for (int i = 0; i < 9; i++) {
						if (region_edited[i] == true) {
							PGGridRawData *grid = region_display[i]->grid;
							for (int grid_index = 0;
								grid_index < grid->Grid_size.x*grid->Grid_size.y;
								grid_index++) {
								if (grid->selected_indexes[grid_index] == true) {
									grid->grid_height_data[grid_index] = 1;
								}
							}
						}
					}
				}
				if (controler->IsRelease(PGKey_6) == true) { //Align all tile height
					for (int i = 0; i < 9; i++) {
						if (region_edited[i] == true) {
							PGGridRawData *grid = region_display[i]->grid;
							for (int grid_index = 0;
								grid_index < grid->Grid_size.x*grid->Grid_size.y;
								grid_index++) {
								if (grid->selected_indexes[grid_index] == true) {
									grid->tile_type[grid_index] = 2;
								}
							}
						}
					}
				}
				if (controler->IsRelease(PGKey_A) == true) {
					for (int i = 0; i < 9; i++) {
						if (region_edited[i] == true) {
							PGGridRawData *grid = region_display[i]->grid;
							for (int grid_index = 0;
								grid_index < grid->Grid_size.x*grid->Grid_size.y;
								grid_index++) {
								if (grid->selected_indexes[grid_index] == true) {
									grid->grid_height_data[grid_index] -= 0.1f;
								}
							}
						}
					}

				}
				if( controler->IsRelease(PGKey_Q) == true) {
					for (int i = 0; i < 9; i++) {
						if (region_edited[i] == true) {
							PGGridRawData *grid = region_display[i]->grid;
							for (int grid_index = 0;
								grid_index < grid->Grid_size.x*grid->Grid_size.y;
								grid_index++) {
								if (grid->selected_indexes[grid_index] == true) {
									grid->grid_height_data[grid_index] += 0.1f;
								}
							}
						}
					}
					
				}
				if (controler->IsRelease(PGKey_S) == true) {
					for (int i = 0; i < 9; i++) {
						if (region_edited[i] == true) {
							region_display[i]->grid->SaveToFile(region_display[i]->FilePath->data_ptr);
						}
					}

				}
			}
			if (controler->IsRelease(PGKey_Left_Ctrl) == true) {
				for (int i = 0; i < 9; i++) {
					if (region_edited[i] == true) {
						PGGridRawData *grid = region_display[i]->grid;
						for (int grid_index = 0;
							grid_index < grid->Grid_size.x*grid->Grid_size.y;
							grid_index++) {
							grid->selected_indexes[grid_index] = false;
						}
					}
				}
			}
			int picked_index = -1;
			//Picking into world space
			//*************************************************************************************		
			if (controler->GetKey(PGKey_Left_Ctrl)->IsPress == true 
				&& controler->IsRelease(PGMouse_Right) == true) {
				v3 world_ray;
				v3 plane_normal = v3(0.f, 0.f, 1.f);
				r32 z_offset = 0.f;
				v3 result_point = v3(0.f);
				world_ray = Mouse_Picker->CastRay(controler, &this->Projection_Matrice, this->scene_camera->GetViewMatrice());
				PGGridRawData *grid_data = region_display[4]->grid;
				v3 possition_offset = v3(grid_data->CalculateNextMapOffetPossition(1), grid_data->CalculateNextMapOffetPossition(2), 0.f);
				v3 possition_cursor = v3(0.f) - possition_offset;
				for (int i = 0;i < 9;	i++) {
					if (i % 3 == 0 && i != 0) {
						possition_cursor.y += possition_offset.y;
						possition_cursor.x -= possition_offset.x*3;
					}
					if (region_edited[i] == true) {
						PGGridRawData *grid = region_display[i]->grid;
						for (int grid_index = 0;
							grid_index < grid->Grid_size.x*grid->Grid_size.y;
							grid_index++) {
							z_offset = grid->grid_height_data[grid_index];
							float dis_t = -((glm::dot(this->scene_camera->Possition, plane_normal) - z_offset) / glm::dot(world_ray, plane_normal));
							result_point = this->scene_camera->Possition + world_ray*dis_t;
							v3 possition = v3(possition_cursor.x + grid->grid_pos_data[grid_index].x, possition_cursor.y + grid->grid_pos_data[grid_index].y, grid->grid_height_data[grid_index]);
							float dist = glm::distance(result_point, possition);
							if (dist < grid->Tile_size) {
								if (grid->selected_indexes[grid_index] == true) {
									grid->selected_indexes[grid_index] = false;
								}
								else {
									grid->selected_indexes[grid_index] = true;
								}
								break;
							}
						}
					}
					possition_cursor.x += possition_offset.x;
				}
			}
			//*************************************************************************************
			//Todo(Marc): remove all light systems
			if (controler->GetKey(PGKey_Left_Ctrl)->IsPress == true) {

			}
			else {
				if (controler->GetKey(PGKey_Left)->IsPress == true) {
					this->scene_light.position += v4(0.1f, 0.0f, 0.0f, 0.f);
				}
				if (controler->GetKey(PGKey_Right)->IsPress == true) {
					this->scene_light.position -= v4(0.1f, 0.0f, 0.0, 0.f);
				}
				if (controler->GetKey(PGKey_Page_Up)->IsPress == true) {
					this->scene_light.position -= v4(0.0f, 0.0f, 0.1f, 0.f);
				}
				if (controler->GetKey(PGKey_Page_Down)->IsPress == true) {
					this->scene_light.position += v4(0.0f, 0.0f, 0.1f, 0.f);
				}
				if (controler->GetKey(PGKey_C)->IsPress == true) {
					this->scene_camera->RotateZAxis(speed, this->scene_camera->LookAt);
				}
				if (controler->GetKey(PGKey_Z)->IsPress == true) {
					this->scene_camera->RotateZAxis(-speed, this->scene_camera->LookAt);
				}
				if (controler->GetKey(PGKey_A)->IsPress == true) {
					this->scene_camera->Possition += v3(-speed, 0.f, 0.f);
					this->scene_camera->LookAt += v3(-speed, 0.f, 0.f);
				}
				if (controler->GetKey(PGKey_D)->IsPress == true) {
					this->scene_camera->Possition += v3(speed, 0.f, 0.f);
					this->scene_camera->LookAt += v3(speed, 0.f, 0.f);
				}
				if (controler->GetKey(PGKey_W)->IsPress == true) {
					this->scene_camera->Possition += v3(0.f, speed, 0.f);
					this->scene_camera->LookAt += v3(0.f, speed, 0.f);
				}
				if (controler->GetKey(PGKey_S)->IsPress == true) {
					this->scene_camera->Possition += v3(0.0f, -speed, 0.f);
					this->scene_camera->LookAt += v3(0.0f, -speed, 0.f);
				}
				if (controler->GetKey(PGKey_Q)->IsPress == true) {
					this->scene_camera->Possition += v3(0.0f, 0.f, speed);
					this->scene_camera->LookAt += v3(0.0f, 0.f, speed);
				}
				if (controler->GetKey(PGKey_E)->IsPress == true) {
					this->scene_camera->Possition += v3(0.0f, 0.f, -speed);
					this->scene_camera->LookAt += v3(0.0f, 0.f, -speed);
				}
				if (controler->GetKey(PGKey_Up)->IsPress == true) {
					this->scene_light.position += v4(0.0f, 0.1f, 0.0f, 0.f);
				}
				if (controler->GetKey(PGKey_Down)->IsPress == true) {
					this->scene_light.position -= v4(0.0f, 0.1f, 0.0f,0.f);
				}
			}
			
		}

};

#endif		