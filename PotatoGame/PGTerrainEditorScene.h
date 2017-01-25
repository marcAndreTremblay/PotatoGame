#if !defined(PG_SCENE_INSTANCE_H)
#define PG_SCENE_INSTANCE_H

#include "stdafx.h"

#include "PGCore.h"
#include "PGBaseRenderer.h"
#include "PGControler.h"
#include "PGSceneEntity.h"
#include "PGBaseEvent.h"
#include "PGString.h"
#include "PGBaseScene.h"
#include "PGBuildableObject.h"


 
class PGTerrainEditorScene : public PGBaseScene {
	protected:
	private:
		v3 light_color =  v3(1.f, 1.f, 1.f);
		
		v4* grid_pos_data;
		r32* grid_height_data;
		v2	grid_size;
		float grid_tile_size;

		v4 obj_list[10];
		int next_index = 0;
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
			free(this->grid_pos_data);
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

			for (int i = 0; i <= 9; i++)  {
				if (obj_list[i].w == 1) {
					renderer->materialHexagoneMesh->Render(v3(obj_list[i]), v3(2.0f, 2.0f, 0.5f), &Material_Copper);
				}
			}
			
		//	renderer->lightedCubeMesh->Render(v3(-1.f, -2.f, 0.f), v3(1.0f), v4(1.f, 0.f, 1.f, 1.f));
			renderer->materialHexagoneMesh->Render(v3(-9.5f, -9.f, 2.f), v3(2.0f, 2.0f, 0.5f), &Material_Gold);
			renderer->materialHexagoneMesh->Render(v3(-3.5f, -2.f, 2.f), v3(2.0f, 2.0f, 0.5f), &Material_Emerald);

		//	renderer->lightedHexagoneMesh->Render(v3(-6.0f, -6.f, 2.f), v3(2.0f, 2.0f, 0.5f), v4(0.7f, 0.6f, 0.3f, 1.f));


			for (int grid_index = 0; grid_index < this->grid_size.x*grid_size.y; grid_index++) {
				renderer->materialHexagoneMesh->Render(v3(grid_pos_data[grid_index]), v3(grid_tile_size, grid_tile_size, grid_height_data[grid_index]), &Material_Gold);
			}

			float water_height = 0.5f;

			v2 hexa_grid_size = v2(10,10);
			float hexa_size = 0.7f;
			v3 major_row_offset = v3(hexa_size, (2 * hexa_size) - (hexa_size / glm::tan(glm::radians(60.f))), 0.f);
			v3 minor_row_offset = v3(-hexa_size, (2 * hexa_size) - (hexa_size / glm::tan(glm::radians(60.f))), 0.f);
			
			v3 target_possition = v3(0.f, 0.f, 0.f);
			for (int y_xpt = 0; y_xpt < hexa_grid_size.y; y_xpt++) {	
				v3 row_start_tempo = target_possition;
				for (int x_xpt = 0; x_xpt < hexa_grid_size.x; x_xpt++) {
					v4 tile_color = v4(0.23f, 0.34f, 0.19f, 1.f);

					float sincos_value = (float)(glm::sin(target_possition.y / 2.0f  *time) + glm::cos(target_possition.x / 1.5f  * tempo_var));
					float tile_height = 1.f + sincos_value;
					float distance_from_peak = glm::distance(peak_possition, target_possition);
					if (distance_from_peak < peak_influance_radius) {
						tile_height += (peak_influance_radius - distance_from_peak);
						tile_color = v4(0.3f, 0.3f, 0.3f, 1.f);
					}
					renderer->materialHexagoneMesh->Render(target_possition, v3(hexa_size, hexa_size, tile_height), &Material_Test);
						if (tile_height < water_height) {
							renderer->lightedHexagoneMesh->Render(v3(target_possition.x, target_possition.y, tile_height), v3(hexa_size, hexa_size, water_height - tile_height), v4(0.3f, 0.7f, 0.99f, 0.8f));
						}
					target_possition.x += hexa_size*2.f;
				}
				target_possition = row_start_tempo;
				if (y_xpt % 2 == 0) {//If pair
					target_possition += major_row_offset;
				}
				else {
					target_possition += minor_row_offset;
				}
			}

		}
		void PGTerrainEditorScene::Build(PGEventWorkGroup* targetWorkGroup,PGMousePicker* mouse_picker)  {
			PGBaseScene::Build(targetWorkGroup,mouse_picker);

			this->Set_Name("TestScene");			
			
			this->Camera = new PGBaseCamera(v3(0, 10, 10), v3(0, 0, 0), v3(0, 0, 1));
			this->Projection_Matrice = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 50.0f);

			
			
			grid_size = v2(10, 10);
			grid_tile_size = 0.7f;
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
			
			v4 starting_offset = v4(-15.f, -15, 0.f, 1.f); //Note(Marc): Offset for the starting possition
			
			grid_pos_data = (v4*)malloc(sizeof(v4)*grid_size.x*grid_size.y);
			grid_height_data = (r32*)malloc(sizeof(r32)*grid_size.x*grid_size.y);
			
			float height_tempo = 0.f;

			int index_cpt = 0;
			for (int y_xpt = 0; y_xpt < grid_size.y; y_xpt++) {
				v4 row_start_tempo = starting_offset;
				for (int x_xpt = 0; x_xpt < grid_size.x; x_xpt++) {
					v4 tile_color = v4(0.23f, 0.34f, 0.19f, 1.f);

	
					starting_offset.x += grid_tile_size*2.f;
					grid_pos_data[index_cpt] = starting_offset;
					grid_height_data[index_cpt] = height_tempo;
					height_tempo += 0.01f;
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


			this->ShouldRender = true;
		}
		void PGTerrainEditorScene::HandleControler(PGControler *controler) override {
			PGBaseScene::HandleControler(controler);
			float speed = 0.15f;
			
			v3 world_ray;
			v3 plane_normal = v3(0.f, 0.f, 1.f);
			r32 offset = 0.f;
			v3 result_point = v3(0.f);
			if(controler->IsRelease(PGMouseRight) == true){
				world_ray = MousePicker->CastRay(controler, &this->Projection_Matrice, &this->Camera->GetViewMatrice());
				float dis_t = -((glm::dot(this->Camera->Possition, plane_normal) + offset) / glm::dot(world_ray, plane_normal));

				result_point = this->Camera->Possition + world_ray*dis_t;

				obj_list[next_index] = v4(result_point,1.f);
				next_index++;	
				if (next_index == 10) {
					next_index = 0;
				}
			}

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