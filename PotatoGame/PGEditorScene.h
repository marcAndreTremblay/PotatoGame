	#if !defined(PG_EDITOR_SCENE_H)
#define PG_EDITOR_SCENE_H

#include "stdafx.h"

#include "PGCore.h"
#include "PGBaseRenderer.h"	
#include "PGBaseScene.h"
#include "PGControler.h"
#include "PGEntity.h"
#include "PGString.h"
#include "PGBaseScene.h"
#include "PGBuildableObject.h"
#include "PGMapGrid.h"
#include "PGMousePicker.h"

#include "PGBackgroundMapGridMesh.h"
#include "PGMapAtlas.h"

using namespace PG::Core;
using namespace PG::Engine;

class PGTerrainEditorScene : public PGBaseScene {
	protected:
	private:
		PGMapAtlas * test_atlas;
		PGGridRawData *grid_data;
		PGGridRawData *grid_data_1;
		PGLight scene_light;
		RawModelData *test_model;
		RawModelData *test_model2;
		RawModelData *test_model3;
		double time;
		double tempo_var;
		PGMapMesh* test_mesh;
	public:
		PGTerrainEditorScene()	: PGBaseScene() {
			this->time = 0.1f;
			this->tempo_var = 0.1f;
			this->scene_light = PGLight();
			this->scene_light.position = v4(15.f, 15.f, 14.f, 1.f);
			
			this->scene_light.diffuse = v4(1.f, 1.f, 1.f, 1.f);
			this->scene_light.ambient = v4(0.6f, 0.6f, 0.6f, 1.f);
			this->scene_light.specular = v4(0.6f, 0.6f, 0.6f, 1.f);
			
		}
		~PGTerrainEditorScene() {
			delete(grid_data);
			delete(test_mesh);
			delete(test_atlas);
		}
		void PGTerrainEditorScene::Update(PGControler *controler, double timeElapse) override {
			PGBaseScene::Update(controler, timeElapse);
		}
		void PGTerrainEditorScene::Render(PGBaseRenderer *renderer) override {
			PGBaseScene::Render(renderer);
	
			renderer->PushLightPossition(&scene_light.position);;
			renderer->PushLightData(&scene_light);

			renderer->axisMesh->Render(v3(0.f, 0.f, 0.f), v4(0.f, 0.f, 1.f, 1.f));
			renderer->cubeMesh->Render(v3(scene_light.position.x, scene_light.position.y, scene_light.position.z), v3(0.1f, 0.1f, 0.1f), scene_light.diffuse);
			
			if (test_model != nullptr) {
				//Render a dommy player model somewhere on the map
				int possition_index = 55;
				v4 possition = grid_data->grid_pos_data[possition_index];
				possition.z = grid_data->grid_height_data[possition_index];
				renderer->model_renderer->Render(test_model, v3(possition), v3(1.f, 1.f, 1.f));
			}
			if (test_model2 != nullptr) {
				renderer->model_renderer->Render(test_model2, v3(10.f, 10.f, 17.f), v3(3.f, 3.f, 3.f));
			}
			if (test_model3 != nullptr) {
				renderer->model_renderer->Render(test_model3, v3(17.f, 17.f, 17.f), v3(1.2f, 1.2f, 1.2f));
			}
			if (grid_data != nullptr) {
				v3 possition;
				v3 scale;
				for (int grid_index = 0;
					grid_index < grid_data->Grid_size.x*grid_data->Grid_size.y;
					grid_index++) {
					possition = v3(grid_data->grid_pos_data[grid_index]);
					scale = v3(grid_data->Tile_size, grid_data->Tile_size, grid_data->grid_height_data[grid_index]);
					if (grid_data->selected_indexes[grid_index] == true) {
						renderer->materialHexagoneMesh->Render(possition, scale, &Material_Copper);
					}
					else {
						renderer->materialHexagoneMesh->Render(possition, scale, &grid_data->grid_material_data[grid_index]);
					}
					if (grid_data->tile_type[grid_index] != 0)  {
						renderer->model_renderer->Render(test_model3, v3(possition.x, possition.y, scale.z), v3(1.f, 1.f, 1.f));
					}
						
				}
				
				v3 possition_offset = v3(grid_data_1->CalculateNextMapOffetPossition(1), grid_data_1->CalculateNextMapOffetPossition(2), 0.f);
				v3 possition_cursor = v3(0.f) - possition_offset;
				for (int grid_index = 0;
					grid_index < 9;
					grid_index++) {
					if (grid_index % 3 == 0 && grid_index != 0) {
						possition_cursor.y += possition_offset.y;
						possition_cursor.x -= possition_offset.x*3;
					}
					if (grid_index != 4) {
					//	renderer->axisMesh->Render(possition_cursor, v4(0.f, 0.f, 1.f, 1.f));
						test_mesh->Render(possition_cursor);
					}
					
					possition_cursor.x += possition_offset.x;
					
				}
			}
		}

		void PGTerrainEditorScene::Build(PGMousePicker* mouse_picker)  {
			PGBaseScene::Build(mouse_picker);

			this->Set_Name("GridEditorScene");			
			
			this->scene_camera = new Camera(
					v3(-15, -15, 15), //Possition
					v3(0, 0, 0), //look at
					v3(0, 0, 1)	 //up
					);
			this->Projection_Matrice = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 150.0f);
			
			test_model = new RawModelData("Asset/RawOBJ/player_v1.obj");
			test_model->LoadIntoVAO();

			test_model3 = new RawModelData("Asset/RawOBJ/forest.obj");
			test_model3->LoadIntoVAO();

			test_model2 = new RawModelData("Asset/RawOBJ/spere2.obj");
			test_model2->LoadIntoVAO();

			

			FILE * file_2 = fopen("Asset/map/layout_1.pgmap", "r");
			if (file_2 != nullptr) {
				grid_data = new PGGridRawData();
				grid_data->LoadFromFile("Asset/map/layout_1.pgmap");
				//grid_data->BuildGridPosData(v3(0.f, 0.f, 0.f));
			}
			else {
				grid_data = new PGGridRawData(v2(10, 10), 1.f);
			}
			grid_data_1 = new PGGridRawData(v2(10, 10), 1.f);
			test_mesh = new PGMapMesh(grid_data_1);
			test_mesh->Build();
		

			int edit_target = 170;
			//Load atlas
		test_atlas = new PGMapAtlas("Asset/map/AtlasMap.txt");
			//Load require region data from their file using the new loaded atlas

			this->ShouldRender = true;
		}
		void PGTerrainEditorScene::HandleControler(PGControler *controler) override {
			PGBaseScene::HandleControler(controler);
			float speed = 0.15f;
			

			if (controler->GetKey(PGKey_Left_Ctrl)->IsPress == true) {
				if (controler->IsRelease(PGKey_1) == true) {
					for (int grid_index = 0;
						grid_index < grid_data->Grid_size.x*grid_data->Grid_size.y;
						grid_index++) {
						if (grid_data->selected_indexes[grid_index] == true) {
							grid_data->grid_material_data[grid_index] = Material_Green;
						}
					}
				}
				if (controler->IsRelease(PGKey_2) == true) {
					for (int grid_index = 0;
						grid_index < grid_data->Grid_size.x*grid_data->Grid_size.y;
						grid_index++) {
						if (grid_data->selected_indexes[grid_index] == true) {
							grid_data->grid_material_data[grid_index] = Material_Brown_1;
						}
					}
				}
				if (controler->IsRelease(PGKey_3) == true) {
					for (int grid_index = 0;
						grid_index < grid_data->Grid_size.x*grid_data->Grid_size.y;
						grid_index++) {
						if (grid_data->selected_indexes[grid_index] == true) {
							grid_data->grid_material_data[grid_index] = Material_Gray;
						}
					}
				}
				if (controler->IsRelease(PGKey_4) == true) {
					for (int grid_index = 0;
						grid_index < grid_data->Grid_size.x*grid_data->Grid_size.y;
						grid_index++) {
						if (grid_data->selected_indexes[grid_index] == true) {
							grid_data->grid_material_data[grid_index] = Material_Blue;
						}
					}
				}
				if (controler->IsRelease(PGKey_5) == true) {
					for (int grid_index = 0;
						grid_index < grid_data->Grid_size.x*grid_data->Grid_size.y;
						grid_index++) {
						if (grid_data->selected_indexes[grid_index] == true) {
							grid_data->tile_type[grid_index] = 1;
						}
					}
				}
				if (controler->IsRelease(PGKey_A) == true) {
					for (int grid_index = 0;
						grid_index < grid_data->Grid_size.x*grid_data->Grid_size.y;
						grid_index++) {
						if (grid_data->selected_indexes[grid_index] == true) {
							grid_data->grid_height_data[grid_index] -= 0.1f;
						}
					}

				}
			
				if( controler->IsRelease(PGKey_Q) == true) {
					for (int grid_index = 0;
						grid_index < grid_data->Grid_size.x*grid_data->Grid_size.y;
						grid_index++) {
						if (grid_data->selected_indexes[grid_index] == true) {
							grid_data->grid_height_data[grid_index] += 0.1f;
						}
					}
				}
				if (controler->IsRelease(PGKey_S) == true) {
					grid_data->SaveToFile("Asset/layout_3.pgmap");
				}
			}
			if (controler->IsRelease(PGKey_Left_Ctrl) == true) {
				for (int grid_index = 0;
					grid_index < grid_data->Grid_size.x*grid_data->Grid_size.y;
					grid_index++) {
					grid_data->selected_indexes[grid_index] = false;
				}
			}
			int picked_index = -1;
			//Picking into world space
			//*************************************************************************************		
			if (controler->GetKey(PGKey_Left_Ctrl)->IsPress == true 
				&& controler->IsRelease(PGMouse_Right) == true) {
				v3 world_ray;
				v3 plane_normal = v3(0.f, 0.f, 1.f);
				r32 offset = 0.f;
				v3 result_point = v3(0.f);
				world_ray = MousePicker->CastRay(controler, &this->Projection_Matrice, this->scene_camera->GetViewMatrice());
				for (int grid_index = 0;
					grid_index < grid_data->Grid_size.x*grid_data->Grid_size.y;
					grid_index++) 
				{
					offset = -grid_data->grid_height_data[grid_index]; //Note(Marc): Dont know why the (-) we should find out
					float dis_t = -((glm::dot(this->scene_camera->Possition, plane_normal) + offset) / glm::dot(world_ray, plane_normal));
					result_point = this->scene_camera->Possition + world_ray*dis_t;
					
					float dist = glm::distance(result_point, v3(grid_data->grid_pos_data[grid_index].x, grid_data->grid_pos_data[grid_index].y, grid_data->grid_height_data[grid_index]));
					if (dist < grid_data->Tile_size) {
						if (grid_data->selected_indexes[grid_index] == true) {
							grid_data->selected_indexes[grid_index] = false;
						}
						else {
							grid_data->selected_indexes[grid_index] = true;
						}
						break;
					}
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