#if !defined(PG_EDITOR_SCENE_H)
#define PG_EDITOR_SCENE_H

#include "stdafx.h"

#include "PGCore.h"
#include "PGBaseRenderer.h"	
#include "PGControler.h"
#include "PGEntity.h"
#include "PGBaseEvent.h"
#include "PGString.h"
#include "PGBaseScene.h"
#include "PGBuildableObject.h"
#include "PGMapGrid.h"






class PGTerrainEditorScene : public PGBaseScene {
	protected:
	private:
		v3 light_color =  v3(1.f, 1.f, 1.f);
		
		PGGridRawData *grid_data;

		PGLight scene_light;

		double time;
		double tempo_var;
		
	public:
		PGTerrainEditorScene()	: PGBaseScene() {
			this->time = 0.1f;
			this->tempo_var = 0.1f;
			this->scene_light = PGLight();
			this->scene_light.position = v4(-1.f, -1.f, 5.f, 1.f);
			
			this->scene_light.diffuse = v4(1.f, 1.f, 1.f, 1.f);
			this->scene_light.ambient = v4(1.f, 1.f, 1.f, 1.f);
			this->scene_light.specular = v4(0.75f, 0.75f, 0.75f, 1.f);

		}
		~PGTerrainEditorScene() {
			delete(grid_data);
		}
		void PGTerrainEditorScene::Update(PGControler *controler, double timeElapse) override {
			PGBaseScene::Update(controler, timeElapse);
		}
		void PGTerrainEditorScene::Render(PGBaseRenderer *renderer) override {
			PGBaseScene::Render(renderer);
	
			renderer->PushLightPossition(&scene_light.position);
			renderer->PushLightColor(&light_color);
			renderer->PushLightData(&scene_light);

			renderer->axisMesh->Render(v3(0.f, 0.f, 0.f), v4(0.f, 0.f, 1.f, 1.f));
			renderer->cubeMesh->Render(v3(scene_light.position.x, scene_light.position.y, scene_light.position.z), v3(0.1f, 0.1f, 0.1f), v4(light_color, 1.f));
	
			if (grid_data != nullptr) {
				for (int grid_index = 0;
					grid_index < grid_data->Grid_size.x*grid_data->Grid_size.y;
					grid_index++) {
					if (grid_data->selected_indexes[grid_index] == true) {
						renderer->materialHexagoneMesh->Render(v3(grid_data->grid_pos_data[grid_index]), v3(grid_data->Tile_size, grid_data->Tile_size, grid_data->grid_height_data[grid_index]), &Material_Copper);
					}
					else {
						renderer->materialHexagoneMesh->Render(v3(grid_data->grid_pos_data[grid_index]), v3(grid_data->Tile_size, grid_data->Tile_size, grid_data->grid_height_data[grid_index]), &grid_data->grid_material_data[grid_index]);						
					}
				}
			}
		}

		void PGTerrainEditorScene::Build(PGMousePicker* mouse_picker)  {
			PGBaseScene::Build(mouse_picker);

			this->Set_Name("GridEditorScene");			
			
			this->Camera = new PGBaseCamera(v3(-10, -10, 15), v3(0, 0, 0), v3(0, 0, 1));
			this->Projection_Matrice = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 50.0f);
			
			
			FILE * file_2 = fopen("Asset/layout_1.pgmap", "r");
			if (file_2 != nullptr) {
				grid_data = new PGGridRawData();
				grid_data->LoadFromFile("Asset/layout_1.pgmap");
				//grid_data->BuildGridPosData(v3(0.f, 0.f, 0.f));
			}
			else {
				grid_data = new PGGridRawData(v2(15, 15), 1.f);
			}

			


		

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
					grid_data->SaveToFile("Asset/layout_1.pgmap");
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
				world_ray = MousePicker->CastRay(controler, &this->Projection_Matrice, this->Camera->GetViewMatrice());
				for (int grid_index = 0;
					grid_index < grid_data->Grid_size.x*grid_data->Grid_size.y;
					grid_index++) 
				{
					offset = -grid_data->grid_height_data[grid_index]; //Note(Marc): Dont know why the (-) we should find out
					float dis_t = -((glm::dot(this->Camera->Possition, plane_normal) + offset) / glm::dot(world_ray, plane_normal));
					result_point = this->Camera->Possition + world_ray*dis_t;
					
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
			if (controler->GetKey(PGKey_Left_Ctrl)->IsPress == true) {
				if (controler->GetKey(PGKey_Left)->IsPress == true) {
					this->light_color -= v3(0.01f, 0.0f, 0.0f);
					if (this->light_color.x < 0.f) this->light_color.x = 0.f;
				}
				if (controler->GetKey(PGKey_Right)->IsPress == true) {
					this->light_color += v3(0.01f, 0.0f, 0.0f);
					if (this->light_color.x > 1.f) this->light_color.x = 1.f;	
				}
				if (controler->GetKey(PGKey_Up)->IsPress == true) {
					this->light_color -= v3(0.f, 0.01f, 0.0f);
					if (this->light_color.y < 0.f) this->light_color.y = 0.f;
				}
				if (controler->GetKey(PGKey_Down)->IsPress == true) {
					this->light_color += v3(0.f, 0.01f, 0.0f);
					if (this->light_color.y > 1.f) this->light_color.y = 1.f;
				}
				if (controler->GetKey(PGKey_Page_Up)->IsPress == true) {
					this->light_color -= v3(0.f, 0.0f, 0.01f);
					if (this->light_color.z < 0.f) this->light_color.z = 0.f;
				}
				if (controler->GetKey(PGKey_Page_Down)->IsPress == true) {
					this->light_color += v3(0.f, 0.0f, 0.01f);
					if (this->light_color.z > 1.f) this->light_color.z = 1.f;
				}
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
					this->Camera->RotateZAxis(speed, this->Camera->LookAt);
				}
				if (controler->GetKey(PGKey_Z)->IsPress == true) {
					this->Camera->RotateZAxis(-speed, this->Camera->LookAt);
				}
				if (controler->GetKey(PGKey_A)->IsPress == true) {
					this->Camera->Possition += v3(-speed, 0.f, 0.f);
					this->Camera->LookAt += v3(-speed, 0.f, 0.f);
				}
				if (controler->GetKey(PGKey_D)->IsPress == true) {
					this->Camera->Possition += v3(speed, 0.f, 0.f);
					this->Camera->LookAt += v3(speed, 0.f, 0.f);
				}
				if (controler->GetKey(PGKey_W)->IsPress == true) {
					this->Camera->Possition += v3(0.f, speed, 0.f);
					this->Camera->LookAt += v3(0.f, speed, 0.f);
				}
				if (controler->GetKey(PGKey_S)->IsPress == true) {
					this->Camera->Possition += v3(0.0f, -speed, 0.f);
					this->Camera->LookAt += v3(0.0f, -speed, 0.f);
				}
				if (controler->GetKey(PGKey_Q)->IsPress == true) {
					this->Camera->Possition += v3(0.0f, 0.f, speed);
					this->Camera->LookAt += v3(0.0f, 0.f, speed);
				}
				if (controler->GetKey(PGKey_E)->IsPress == true) {
					this->Camera->Possition += v3(0.0f, 0.f, -speed);
					this->Camera->LookAt += v3(0.0f, 0.f, -speed);
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