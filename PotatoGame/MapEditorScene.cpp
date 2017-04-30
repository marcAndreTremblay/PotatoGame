#include "stdafx.h"
#include "MapEditorScene.h"


MapEditorScene::MapEditorScene() {
	current_mode = Mode_Camera_Move;
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


MapEditorScene::~MapEditorScene() {
	delete(test_atlas);
	delete(region_mesh);
}

void MapEditorScene::Update(Controler * controler, double timeElapse) {
	Scene::Update(controler, timeElapse);
}

void MapEditorScene::Render(BaseRenderer * renderer) {
	Scene::Render(renderer);

	renderer->PushLightPossition(&scene_light.position);;
	renderer->PushLightData(&scene_light);

	renderer->axisMesh->Render(v3(0.f, 0.f, 0.f), v4(0.f, 0.f, 1.f, 1.f));
	renderer->cubeMesh->Render(v3(scene_light.position.x, scene_light.position.y, scene_light.position.z), v3(0.1f, 0.1f, 0.1f), scene_light.diffuse);

	renderer->map_shader_program->Render(region_mesh, &v3(0.f, 0.f, 20.f));
	
	//renderer->map_shader_program->Render(test_model_mesh, &v3(0.f, 0.f, 10.f));
	
	renderer->model_mtl_shader_program->Render(test1_model_mesh, &v3(0.f, 0.f, 10.f));
	renderer->model_base_shader_program->Render(test2_model_mesh, &v3(2.f, 0.f, 10.f),&v4(1.f, 0.f, 1.f, 1.f));

	v3 selected_item_marker_color = v3(1.f,0.f, 0.f);
	v3 selected_item_marker_scale = v3(1.f, 1.f, 1.f);

	PGGridRawData *grid_data = region_display[4]->grid;
	v3 possition_offset = v3(grid_data->CalculateNextMapOffetPossition(1), grid_data->CalculateNextMapOffetPossition(2), 0.f);
	v3 possition_cursor = v3(0.f) - possition_offset;
	for (int grid_index = 0; grid_index < 9; grid_index++) {
		if (grid_index % 3 == 0 && grid_index != 0) {
			possition_cursor.y += possition_offset.y;
			possition_cursor.x -= possition_offset.x * 3;
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
					renderer->cubeMesh->Render(v3(possition.x, possition.y, scale.z), v3(0.1f, 0.1f, 0.1f), scene_light.diffuse);
				}
				
				renderer->materialHexagoneMesh->Render(possition, scale, &grid->grid_material_data[grid_index]);
				
				if (grid->tile_type[grid_index] == 1) {
					renderer->model_renderer->Render(test_model3, v3(possition.x, possition.y, scale.z), v3(1.f, 1.f, 1.f));
				}
				if (grid->tile_type[grid_index] == 2) {
					renderer->model_renderer->Render(test_model, v3(possition.x, possition.y, scale.z), v3(1.f, 1.f, 1.f));
				}
			}
		}

		else {
			if (region_display[grid_index] != nullptr) {
				renderer->map_shader_program->Render(region_display[grid_index]->mesh, &possition_cursor);
				
			}
		}

		possition_cursor.x += possition_offset.x;

	}

}

void MapEditorScene::Build(MousePicker * mouse_picker) {
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


	
	grid_data_V2 = new GridRawDataV2(v2(10, 15), 1.f);
	grid_data_V2->SaveToFile("Asset/TestMapV2.mmv2");
	delete(grid_data_V2);
	grid_data_V2 = new GridRawDataV2();
	grid_data_V2->LoadFromFile("Asset/TestMapV2.mmv2");
	delete(grid_data_V2);
	material_Test = new FileMtlRawDataV2();
	material_Test->LoadFromFile("Asset/map/Asset/base_material.mtl");
	delete(material_Test);

	modele_test1 = new ModelRawDataV1();
	modele_test1->LoadFromFile("Asset/map/Asset/forest.obj");
	modele_test2 = new ModelRawDataV1();
	modele_test2->LoadFromFile("Asset/map/Asset/tile_bottom.obj");

	test1_model_mesh = new ModelMeshV1(modele_test1);
	test1_model_mesh->Build();
	
	test2_model_mesh = new ModelMeshV1(modele_test2);
	test2_model_mesh->Build();
	delete(modele_test1);
	delete(modele_test2);


	int edit_target = 171;
	//Load atlas
	test_atlas = new PGMapAtlas("Asset/map/AtlasMap.txt");
	//Load require region data from their file using the new loaded atlas
	test_atlas->LoadRegionsAndFillDisplayTemplate(edit_target, &region_display[0]);
	region_edited[0] = true;
	region_edited[1] = true;
	region_edited[2] = true;
	region_edited[3] = true;
		region_edited[4] = true;
	region_edited[5] = true;
	//region_edited[6] = true;
	//region_edited[7] = true;
	//region_edited[8] = true;
	
	
	region_mesh = new HexaGridMapMesh(region_display[0]->grid);
	region_mesh->Build();
	

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
		PGGridRawData *grid_data = region_display[4]->grid;
		v3 possition_offset = v3(grid_data->CalculateNextMapOffetPossition(1), grid_data->CalculateNextMapOffetPossition(2), 0.f);
		v3 possition_cursor = v3(0.f) - possition_offset;
		for (int i = 0; i < 9; i++) {
			if (i % 3 == 0 && i != 0) {
				possition_cursor.y += possition_offset.y;
				possition_cursor.x -= possition_offset.x * 3;
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
				if (region_edited[i] == true) {
					region_display[i]->grid->SaveToFile(region_display[i]->FilePath->data_ptr);
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
			//*************************************************************************************

			break; }
		case Mode_Edit_Tile_Material:
			HandleCameraMovement(controler);
			HandleTilePicking(controler);
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
			break;
		case Mode_Edit_Tile_Height:{
			HandleCameraMovement(controler);
			HandleTilePicking(controler);
			if (controler->IsRelease(PGKey_1) == true) {
				float height_count = 0.f;
				float element_count = 0.f;
				for (int i = 0; i < 9; i++) {
					if (region_edited[i] == true) {
						PGGridRawData *grid = region_display[i]->grid;
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
					if (region_edited[i] == true) {
						PGGridRawData *grid = region_display[i]->grid;
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
			break; }
		case Mode_Edit_Tile_Model:{
			if (controler->IsRelease(PGKey_1) == true) {
				for (int i = 0; i < 9; i++) {
					if (region_edited[i] == true) {
						PGGridRawData *grid = region_display[i]->grid;
						for (int grid_index = 0;
							grid_index < grid->Grid_size.x*grid->Grid_size.y;
							grid_index++) {
							if (grid->selected_indexes[grid_index] == true) {
								grid->tile_type[grid_index] = 0;
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
								grid->tile_type[grid_index] = 1;
							}
						}
					}
				}
			}

			if (controler->IsRelease(PGKey_3) == true) { //Align all tile height
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
			break; }
		default: {current_mode = Mode_Camera_Move;
			break; }
				 
	}
	

	



}
