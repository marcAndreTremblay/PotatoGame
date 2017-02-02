#if !defined(PG_EDITOR_SCENE_H)
#define PG_EDITOR_SCENE_H

#include "stdafx.h"

#include "PGCore.h"
#include "PGBaseRenderer.h"	
#include "PGControler.h"
#include "PGSceneEntity.h"
#include "PGBaseEvent.h"
#include "PGString.h"
#include "PGBaseScene.h"
#include "PGBuildableObject.h"


class PGGridRawData {
protected:
private:

public:
	v4* grid_pos_data = nullptr;
	r32* grid_height_data = nullptr;
	PGMaterial* grid_material_data = nullptr;
	int selected_index;
	v2 Grid_size; 
	r32 Tile_size;
	PGGridRawData() {
		selected_index = -1;
		Grid_size = v2(0, 0);
		Tile_size = 0;
	}
	PGGridRawData(v2 grid_size, r32 grid_tile_size) {
		Grid_size = grid_size;
		Tile_size = grid_tile_size;

		//			o
		//		o		o
		//	o				o
		//	o				o	
		//	o		o		o	
		//	o				o
		//	o				o
		//		o		o		
		//			o
		//Note(Marc): We use the bottom left as the starting point 
		//Note(Marc): We go left to right and bottom to top in the world space starting from 0,0,0
		v4 major_row_offset = v4(grid_tile_size, (2 * grid_tile_size) - (grid_tile_size / glm::tan(glm::radians(60.f))), 0.f, 0.f);
		v4 minor_row_offset = v4(-grid_tile_size, (2 * grid_tile_size) - (grid_tile_size / glm::tan(glm::radians(60.f))), 0.f, 0.f);

		v4 starting_offset = v4(-10.f, -10, 0.f, 0.f); //Note(Marc): Offset for the starting possition

		this->grid_pos_data = (v4*)malloc(sizeof(v4)*grid_size.x*grid_size.y);
		this->grid_height_data = (r32*)malloc(sizeof(r32)*grid_size.x*grid_size.y);
		this->grid_material_data = (PGMaterial*)malloc(sizeof(PGMaterial)*grid_size.x*grid_size.y);


		float height_tempo = 0.f;

		int index_cpt = 0;
		for (int y_xpt = 0; y_xpt < grid_size.y; y_xpt++) {
			v4 row_start_tempo = starting_offset;
			for (int x_xpt = 0; x_xpt < grid_size.x; x_xpt++) {
				v4 tile_color = v4(0.23f, 0.34f, 0.19f, 1.f);


				starting_offset.x += grid_tile_size*2.f;
				grid_pos_data[index_cpt] = starting_offset;
				grid_height_data[index_cpt] = 1 + sin(y_xpt/4.f) ;

				index_cpt++;
			}
			starting_offset = row_start_tempo;
			if (y_xpt % 2 == 0) {//If pair
				starting_offset += major_row_offset;
			}
			else {
				starting_offset += minor_row_offset;
			}
		}
	}
	~PGGridRawData() {
		delete(grid_pos_data);
		delete(grid_height_data);
		delete(grid_material_data);
	}
	void SaveToFile(char *file_path) {
		FILE * file_2 = fopen(file_path, "w");
		if (file_2 != nullptr) {
			fwrite(&Grid_size.x, sizeof(float), 1, file_2);
			fwrite(&Grid_size.y, sizeof(float), 1, file_2);
			fwrite(&Tile_size, sizeof(float), 1, file_2);
			
			fwrite(grid_pos_data, sizeof(v4), Grid_size.x*Grid_size.y, file_2);
			fwrite(grid_height_data, sizeof(float), Grid_size.x*Grid_size.y,file_2);
			fwrite(grid_material_data, sizeof(PGMaterial), Grid_size.x*Grid_size.y, file_2);

			fclose(file_2);
		}

	}
	void LoadFromFile(char *file_path) {
		if (grid_pos_data != nullptr) delete(grid_pos_data);
		if (grid_height_data != nullptr) delete(grid_height_data);
		if (grid_material_data != nullptr) delete(grid_material_data);

		FILE * file_2 = fopen(file_path, "r");
		if (file_2 != nullptr) {
			float x, y , size;
			fread(&x, sizeof(float), 1, file_2);
			fread(&y, sizeof(float), 1, file_2);
			fread(&size, sizeof(float), 1, file_2);
			
			this->Tile_size = size;
			this->Grid_size = v2(x,y);
			
			this->grid_pos_data = (v4*)malloc(sizeof(v4)*x*y);
			this->grid_height_data = (r32*)malloc(sizeof(r32)*x*y);
			this->grid_material_data = (PGMaterial*)malloc(sizeof(PGMaterial)*x*y);
			
			fread(grid_pos_data, sizeof(v4), x*y, file_2);
			fread(grid_height_data, sizeof(float), x*y, file_2);
			fread(grid_material_data, sizeof(PGMaterial), x*y, file_2);
			
			fclose(file_2);
		}
	}

};
 
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
			time += timeElapse / 9.f;
			tempo_var += timeElapse / 7.f;
			if (time > 1.f) {
				this->time = 0.1f;
			}
			if (tempo_var > 1.1f) {
				this->tempo_var = 0.1f;
			}

		}
		void PGTerrainEditorScene::Render(PGBaseRenderer *renderer) override {
			PGBaseScene::Render(renderer);

			v3 peak_possition = v3(6.f, 6.f, 0.f);
			float peak_influance_radius = 5.0f;

			renderer->PushLightPossition(&scene_light.position);
			renderer->PushLightColor(&light_color);
			renderer->PushLightData(&scene_light);

			renderer->axisMesh->Render(v3(0.f, 0.f, 0.f), v4(0.f, 0.f, 1.f, 1.f));
			renderer->cubeMesh->Render(v3(scene_light.position.x, scene_light.position.y, scene_light.position.z), v3(0.1f, 0.1f, 0.1f), v4(light_color, 1.f));
	
			if (grid_data != nullptr) {
				for (int grid_index = 0;
					grid_index < grid_data->Grid_size.x*grid_data->Grid_size.y;
					grid_index++) {
					if (grid_index == grid_data->selected_index) {
						renderer->materialHexagoneMesh->Render(v3(grid_data->grid_pos_data[grid_index]), v3(grid_data->Tile_size, grid_data->Tile_size, grid_data->grid_height_data[grid_index]), &Material_Emerald);
					}
					else {
						renderer->materialHexagoneMesh->Render(v3(grid_data->grid_pos_data[grid_index]), v3(grid_data->Tile_size, grid_data->Tile_size, grid_data->grid_height_data[grid_index]), &Material_Gold);

					}
				}
			}
		}

		void PGTerrainEditorScene::Build(PGEventWorkGroup* targetWorkGroup,PGMousePicker* mouse_picker)  {
			PGBaseScene::Build(targetWorkGroup,mouse_picker);

			this->Set_Name("TestScene");			
			
			this->Camera = new PGBaseCamera(v3(0, 10, 10), v3(0, 0, 0), v3(0, 0, 1));
			this->Projection_Matrice = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 50.0f);
			
			
			FILE * file_2 = fopen("Asset/layout_1.pgmap", "r");
			if (file_2 != nullptr) {
				grid_data = new PGGridRawData();
				grid_data->LoadFromFile("Asset/layout_1.pgmap");
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
				if (controler->IsRelease(PGKey_A) == true) {
					if (grid_data->selected_index >= 0 && grid_data->selected_index < grid_data->Grid_size.x*grid_data->Grid_size.y) {
						grid_data->grid_height_data[grid_data->selected_index] -= 0.1f;
					}
				}
			
				if( controler->IsRelease(PGKey_Q) == true) {
					if (grid_data->selected_index >= 0 && grid_data->selected_index < grid_data->Grid_size.x*grid_data->Grid_size.y) {
						grid_data->grid_height_data[grid_data->selected_index] += 0.1f;
					}
				}
				if (controler->IsRelease(PGKey_S) == true) {
					grid_data->SaveToFile("Asset/layout_1.pgmap");
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
				world_ray = MousePicker->CastRay(controler, &this->Projection_Matrice, &this->Camera->GetViewMatrice());
				for (int grid_index = 0;
					grid_index < grid_data->Grid_size.x*grid_data->Grid_size.y;
					grid_index++) 
				{
					offset = -grid_data->grid_height_data[grid_index]; //Note(Marc): Dont know why the (-) we should find out
					float dis_t = -((glm::dot(this->Camera->Possition, plane_normal) + offset) / glm::dot(world_ray, plane_normal));
					result_point = this->Camera->Possition + world_ray*dis_t;
					
					float dist = glm::distance(result_point, v3(grid_data->grid_pos_data[grid_index].x, grid_data->grid_pos_data[grid_index].y, grid_data->grid_height_data[grid_index]));
					if (dist < grid_data->Tile_size) {
						picked_index = grid_index;
						break;
					}
				}
				grid_data->selected_index = picked_index;
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
		void PGTerrainEditorScene::HandlerEvents(PGEventWorkGroup *work_group) override {
			PGBaseScene::HandlerEvents(work_group);

		}
};

#endif