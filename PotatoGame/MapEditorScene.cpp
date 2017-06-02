#include "stdafx.h"
#include "MapEditorScene.h"/


MapEditorScene::MapEditorScene(MousePicker* mouse_picker) : Scene(mouse_picker){
	current_mode = Mode_Camera_Move;
	this->time = 0.1f;
	this->tempo_var = 0.1f;
	this->scene_light = PGLight();
	this->scene_light.position = v4(0.f, 0.f, 0.f, 1.f);

	this->scene_light.diffuse = v4(1.f, 1.f, 1.f, 1.f);
	this->scene_light.ambient = v4(0.6f, 0.6f, 0.6f, 1.f);
	this->scene_light.specular = v4(0.6f, 0.6f, 0.6f, 1.f);
	
	map_atlas = nullptr;
	for (int i = 0; i <= 9; i++) {
		map_atlas_region_display[i] = nullptr;
		map_atlas_region_edited[i] = false;
	}

	top_tile_raw_data = nullptr;
	bottom_tile_raw_data = nullptr;
	bottom_tile_mesh = nullptr;
	top_tile_mesh = nullptr;
	sphere_mesh = nullptr;

	Model_Atlas_File = nullptr;
}


MapEditorScene::~MapEditorScene() {
	delete(top_tile_raw_data);
	delete(bottom_tile_raw_data);
	delete(bottom_tile_mesh);
	delete(top_tile_mesh);
	delete(Model_Atlas_File);
	delete(map_atlas);
	delete(solar_data);
	delete(test_forest);
	delete(test_floor_tile);
}

void MapEditorScene::Update(Controler * controler, double timeElapse) {
	Scene::Update(controler, timeElapse);
	time += timeElapse;

}
void MapEditorScene::RenderSolarSystem(BaseRenderer * renderer) {
	solar_data->bodies_list->GetHead();

	for (int i = 0; i < solar_data->bodies_list->element_count; i++) {
		CelestialBody* c_body = solar_data->bodies_list->GetAt(i); //Change this
		MaterielRawData* color = material_file->FindByNameId(i);
		renderer->model_mtl_shader_program->Render(sphere_mesh,
													&c_body->GetWorldPossition(),
													&c_body->GetWorldSize(),
													color);
	}
}
void MapEditorScene::RenderMapGrid(BaseRenderer * renderer) {
	GridRawDataV2 *grid_data = map_atlas_region_display[0]->file_data;
	v3 grid_offset = grid_data->CalculateGridOffset();
	v3 possition_cursor = v3(0.f) - grid_offset;

	for (int grid_index = 0; grid_index < 9; grid_index++) {
		if (grid_index % 3 == 0 && grid_index != 0) {
			possition_cursor.y += grid_offset.y;
			possition_cursor.x -= grid_offset.x * 3;
		}
		if (map_atlas_region_edited[grid_index] == true) {
			GridRawDataV2 *grid = map_atlas_region_display[grid_index]->file_data;
			
					v3 tile_possition;
					v3 scale = v3(1.f);
					int* top_tile_data = grid->GetTopMaterialPtr();
					r32* height_data = grid->GetHeightArrayPtr();
					int* bottom_tile_data = grid->GetBottomMaterialPtr();
					for (int grid_index = 0; grid_index < grid->Grid_size.x*grid->Grid_size.y;grid_index++) {	

						tile_possition = possition_cursor + v3(grid->grid_pos_data[grid_index]);
						tile_possition.z = height_data[grid_index];
						if (grid->selected_indexes[grid_index] == true) {
							renderer->model_base_shader_program->Render(top_tile_mesh, &tile_possition, grid->mtl_file->FindByNameId(0));
						}	
						else {
							renderer->model_base_shader_program->Render(top_tile_mesh, &tile_possition, grid->mtl_file->FindByNameId(top_tile_data[grid_index]));

						}
						tile_possition.z = 0.f;
						renderer->model_base_shader_program->Render(bottom_tile_mesh, &tile_possition,&v3(1.f, 1.f, height_data[grid_index]), grid->mtl_file->FindByNameId(bottom_tile_data[grid_index]));
						
						tile_possition.z = height_data[grid_index];
						renderer->model_mtl_shader_program->Render(test_forest, &tile_possition, &v3(1.f),nullptr);
					}
		}
		else {
			if (map_atlas_region_display[grid_index] != nullptr) {
				renderer->map_shader_program->Render(map_atlas_region_display[grid_index]->region_mesh, &possition_cursor);
			}
		}
		possition_cursor.x += grid_offset.x;
	}
}
void MapEditorScene::Render(BaseRenderer * renderer) {
	Scene::Render(renderer);

	renderer->PushLightPossition(&scene_light.position);;
	renderer->PushLightData(&scene_light);

	renderer->axisMesh->Render(v3(0.f, 0.f, 0.f), v4(0.f, 0.f, 1.f, 1.f));
	renderer->cubeMesh->Render(v3(scene_light.position.x, scene_light.position.y, scene_light.position.z), v3(0.1f, 0.1f, 0.1f), scene_light.diffuse);
	
	for (float x = 0.f; x < 5.f; x = x + 1.f) {
		for (float y = 0.f; y < 5.f; y = y + 1.f) {
			renderer->model_mtl_shader_program->Render(test_floor_tile, &v3(x * 2, y * 2, 10.f),nullptr);
		}
	}
	
	RenderSolarSystem(renderer);
	RenderMapGrid(renderer);

	for (int i = 0; i < material_file->Count(); i++) {
		MaterielRawData* yrdy = material_file->FindByNameId(i);
		renderer->model_mtl_shader_program->Render(sphere_mesh, &v3(i * 2, i*2, i * 2), yrdy);

	}

}

void MapEditorScene::Build(AnimatorManager* anmation_manager) {
	Scene::Build();

	this->Set_Name("GridEditorScene");

	this->scene_camera = new Camera(
		v3(-15, -15, 10), //Possition
		v3(0, 0, 0), //look at
		v3(0, 0, 1)	 //up
	);
	animation_test = new CameraAnimation(scene_camera);
	//Todo(): Maybe we should test if we should calculate the aspect racio from the physical screen size or perharp with the window size???
	this->Projection_Matrice = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 150.0f);

	solar_data = new SolorSystemEntities();
	
	Star* s1 = new Star(3.0f,12.f);
	solar_data->bodies_list->Add(s1);


	Planet* p1 = new Planet(6.2f, 0.f, PG_Pi32/3.f, 0.2f, s1);
		anmation_manager->AttachAnimation(new CelestialBodyAnimation(p1));
	solar_data->bodies_list->Add(p1);

	Planet* p2 = new Planet(10.2f, PG_Pi32, PG_Pi32 / 5.f, 0.2f, s1);
		anmation_manager->AttachAnimation(new CelestialBodyAnimation(p2));
	solar_data->bodies_list->Add(p2);;

	Planet* p3 = new Planet(15.f, PG_Pi32*1.5f, PG_Pi32 / 8.f, 0.2f, s1);
		anmation_manager->AttachAnimation(new CelestialBodyAnimation(p3));
	solar_data->bodies_list->Add(p3);;

	Planet* p4 = new Planet(22.f, PG_Pi32/3.f, PG_Pi32 / 6.f, 0.2f, s1);
		anmation_manager->AttachAnimation(new CelestialBodyAnimation(p4));
	solar_data->bodies_list->Add(p4);;

	Moon* p2_l1 = new Moon(2.f, PG_Pi32 / 2.f, PG_Pi32, 0.3f, p2);
		anmation_manager->AttachAnimation(new CelestialBodyAnimation(p2_l1));
	solar_data->bodies_list->Add(p2_l1);;

	Moon* p2_l2 = new Moon(3.5f, PG_Pi32 / 4.f, PG_Pi32, 0.6f, p2);
		anmation_manager->AttachAnimation(new CelestialBodyAnimation(p2_l2));
	solar_data->bodies_list->Add(p2_l2);;

	Model_Atlas_File = new ModelAtlasFile("Asset/Map_Data/Asset/atlas_model_map.txt");
	Model_Atlas_File->LoadFromFile();

	material_file = new FileMtlRawDataV2();
	material_file->LoadFromFile("Asset/Map_Data/Asset/atlas_material_map.mtl");


	top_tile_raw_data = new ModelRawDataV1();
	top_tile_raw_data->LoadFromFile("Asset/Map_Data/Asset/tile_top_type_1.obj");

	bottom_tile_raw_data = new ModelRawDataV1();
	bottom_tile_raw_data->LoadFromFile("Asset/Map_Data/Asset/tile_bottom2.obj");

	ModelRawDataV1* forest_model_data = new ModelRawDataV1();
	forest_model_data->LoadFromFile("Asset/Map_Data/Asset/forest.obj");
	test_forest = new ModelMeshV1(forest_model_data);
	test_forest->Build();

	delete(forest_model_data);

	top_tile_mesh = new ModelMeshV1(top_tile_raw_data);
	top_tile_mesh->Build();

	bottom_tile_mesh = new ModelMeshV1(bottom_tile_raw_data);
	bottom_tile_mesh->Build();

	ModelRawDataV1* spher_data = new ModelRawDataV1();
	spher_data->LoadFromFile("Asset/RawOBJ/spere3.obj");
	sphere_mesh = new ModelMeshV1(spher_data);
	sphere_mesh->Build();
	delete(spher_data);



	ModelRawDataV1* floor_data = new ModelRawDataV1();
	floor_data->LoadFromFile("Asset/RawOBJ/tile_floor.obj");
    test_floor_tile = new ModelMeshV1(floor_data);
	test_floor_tile->Build();
	delete(floor_data);
	
	int edit_target = 171;
	//Load V2 of WorldAtlas
	map_atlas = new MapAtlasRawDataV1("Asset/Map_Data/AtlasMapV2.txt");
	map_atlas->LoadFromFile();
	map_atlas->LoadRegionsAndFillDisplayTemplate(edit_target,&map_atlas_region_display[0]);
	map_atlas_region_edited[0] = true;

	

	test_mat = material_file->FindByNameId(1);
	selected_mat = material_file->FindByNameId(2);
	this->ShouldRender = true;



}

void MapEditorScene::HandleTilePicking(Controler * controler) {
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
		GridRawDataV2 *grid_data = map_atlas_region_display[4]->file_data;
		v3 possition_offset = grid_data->CalculateGridOffset();
		v3 possition_cursor = v3(0.f) - possition_offset;
		for (int i = 0; i < 9; i++) {
			if (i % 3 == 0 && i != 0) {
				possition_cursor.y += possition_offset.y;
				possition_cursor.x -= possition_offset.x * 3;
			}
			if (map_atlas_region_edited[i] == true) {
				GridRawDataV2 *grid = map_atlas_region_display[i]->file_data;
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
}
void MapEditorScene::HandleCameraMovement(Controler * controler) {
	float speed = 0.15f;
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
	if (controler->GetKey(PGKey_Q)->IsPress == true) {
		this->scene_camera->RotateZAxis(speed, this->scene_camera->LookAt);
	}
	if (controler->GetKey(PGKey_E)->IsPress == true) {
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
	if (controler->GetKey(PGKey_R)->IsPress == true) {
		this->scene_camera->Possition += v3(0.f, 0.f, speed);
		this->scene_camera->LookAt += v3(0.f, 0.f, speed);
	}
	if (controler->GetKey(PGKey_F)->IsPress == true) {
		this->scene_camera->Possition += v3(0.0f, 0.f, -speed);
		this->scene_camera->LookAt += v3(0.0f, 0.f, -speed);
	}
	if (controler->GetKey(PGKey_Up)->IsPress == true) {
		this->scene_light.position += v4(0.0f, 0.1f, 0.0f, 0.f);
	}
	if (controler->GetKey(PGKey_Down)->IsPress == true) {
		this->scene_light.position -= v4(0.0f, 0.1f, 0.0f, 0.f);
	}
}
void MapEditorScene::HandleControler(Controler * controler) {
	Scene::HandleControler(controler);
	
	

	if (controler->IsRelease(PGKey_F1) == true) {
		current_mode = Mode_Camera_Move;
		printf("Mode_Camera_Move Mode\n");
	}
	if (controler->IsRelease(PGKey_F2) == true) {
		current_mode = Mode_Entities_Selection;
		printf("Mode_Entities_Selection Mode\n");
	}
	if (controler->IsRelease(PGKey_F3) == true) {
		current_mode = Mode_Tiles_Selection;
		printf("Mode_Tiles_Selection Mode\n");
	}
	if (controler->IsRelease(PGKey_F4) == true) {
		current_mode = Mode_Edit_Tile_Material;
		printf("Mode_Edit_Tile_Material Mode\n");
	}
	if (controler->IsRelease(PGKey_F5) == true) {
		current_mode = Mode_Edit_Tile_Height;
		printf("Mode_Edit_Tile_Height Mode\n");
	}
	if (controler->IsRelease(PGKey_F6) == true) {
		current_mode = Mode_Edit_Tile_Model;
		printf("Mode_Edit_Tile_Model Mode\n");
	}
	if (controler->GetKey(PGKey_Left_Ctrl)->IsPress == true) {
		if (controler->IsRelease(PGKey_S) == true) {
			for (int i = 0; i < 9; i++) {
				if (map_atlas_region_edited[i] == true) {
					map_atlas_region_display[i]->file_data->SaveToFile(map_atlas_region_display[i]->File_Path->CharAt());
				}
			}

		}
	}
	switch (current_mode) {
		case Mode_Camera_Move:
			HandleCameraMovement(controler);
			break;
		case Mode_Entities_Selection:
			break;
		case Mode_Tiles_Selection:
		{

			HandleCameraMovement(controler);
			HandleTilePicking(controler);
			//*************************************************************************************
			if (controler->IsRelease(PGKey_C) == true) {
				for (int i = 0; i < 9; i++) {
					if (map_atlas_region_edited[i] == true) {
						GridRawDataV2 *grid = map_atlas_region_display[i]->file_data;
						for (int grid_index = 0;
							grid_index < grid->Grid_size.x*grid->Grid_size.y;
							grid_index++) {
							grid->selected_indexes[grid_index] = false;
						}
					}
				}
			}
			//*************************************************************************************

			break; }
		case Mode_Edit_Tile_Material: {
			HandleCameraMovement(controler);
			HandleTilePicking(controler);
			//if (controler->IsRelease(PGKey_1) == true) {
			//	for (int i = 0; i < 9; i++) {
			//		if (map_atlas_region_edited[i] == true) {
			//			GridRawDataV2 *grid = map_atlas_region_display[i]->file_data;
			//			for (int grid_index = 0;
			//				grid_index < grid->Grid_size.x*grid->Grid_size.y;
			//				grid_index++) {
			//				if (grid->selected_indexes[grid_index] == true) {
			//					//Do shit here
			//				}
			//			}
			//		}
			//	}
			//}
			break;}
		case Mode_Edit_Tile_Height:{
			HandleCameraMovement(controler);
			HandleTilePicking(controler);
			//Average selected tile height and set that height to them
			if (controler->IsRelease(PGKey_1) == true) {
				float height_count = 0.f;
				float element_count = 0.f;
				for (int i = 0; i < 9; i++) {
					if (map_atlas_region_edited[i] == true) {
						GridRawDataV2 *grid = map_atlas_region_display[i]->file_data;
						for (int grid_index = 0; grid_index < grid->Grid_size.x*grid->Grid_size.y; grid_index++) {
							if (grid->selected_indexes[grid_index] == true) {
								height_count += grid->grid_height_data[grid_index];
								element_count += 1.0f;
							}
						}
						float new_height = height_count / element_count;
						for (int grid_index = 0; grid_index < grid->Grid_size.x*grid->Grid_size.y; grid_index++) {
							if (grid->selected_indexes[grid_index] == true) {
								grid->grid_height_data[grid_index] = new_height;
							}
						}
					}
				}

			}
			if (controler->IsRelease(PGKey_G) == true) {
				for (int i = 0; i < 9; i++) {
					if (map_atlas_region_edited[i] == true) {
						GridRawDataV2 *grid = map_atlas_region_display[i]->file_data;
						for (int grid_index = 0;grid_index < grid->Grid_size.x*grid->Grid_size.y;grid_index++) {
							if (grid->selected_indexes[grid_index] == true) {
								grid->grid_height_data[grid_index] -= 0.1f;
							}
						}
					}
				}

			}
			if (controler->IsRelease(PGKey_T) == true) {
				for (int i = 0; i < 9; i++) {
					if (map_atlas_region_edited[i] == true) {
						GridRawDataV2 *grid = map_atlas_region_display[i]->file_data;
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
			break; }
		case Mode_Edit_Tile_Model:{
			
			break; }
		default: {current_mode = Mode_Camera_Move;
			break; }
				 
	}
	

	



}
