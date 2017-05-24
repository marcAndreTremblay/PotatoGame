#include "stdafx.h"
#include "EditorInstance.h"


EditorInstance::EditorInstance() {
	anmation_manager = new AnimatorManager();
}


EditorInstance::~EditorInstance() {
	delete(game_canvas);
	delete(anmation_manager);
}

void EditorInstance::Build() {
	EngineInstance::Build();
	BuildableObject::StartBuilding();

	//Build a work group for the game and active scenes



	this->Asset_Manager->LoadTexture(PG_PNG, "Asset/texture/Archer_right.png", "ArcherRight");
	this->Asset_Manager->LoadTexture(PG_BMP, "Asset/uvtemplate.bmp", "UV_Template");
	this->Asset_Manager->LoadTexture(PG_PNG, "Asset/texture/asteroid_1.png", "Asteroid_1");
	this->Asset_Manager->LoadTexture(PG_PNG, "Asset/texture/solar_panel.png", "SolarPanel");
	this->Asset_Manager->LoadTexture(PG_PNG, "Asset/texture/Water_0.png", "Water");

	//Load a basic Font for debugging
	this->Default_Engine_Font = this->Asset_Manager->LoadFont("Asset/font/Roboto-Bold.ttf", "Roboto_Bold");
	this->Asset_Manager->LoadFont("Asset/font/Roboto-Light.ttf", "Roboto-Light");
	this->Asset_Manager->LoadFont("Asset/font/Immortal.ttf", "Immortal");
	this->Asset_Manager->LoadFont("Asset/font/Hammersmith_Regular.ttf", "Hammersmith_Regular");





	//Build the needed UI for the game
	this->game_canvas = new GUICanvas();
	this->game_canvas->Build(this->Game_Window, this->Mouse_Picker, this->Asset_Manager);



	//Build the first scene
	MapEditorScene* terrain_editor_scene = new MapEditorScene(this->Mouse_Picker);
	terrain_editor_scene->Set_Id(1);
	terrain_editor_scene->Build(anmation_manager);
	this->LoadedScenes->Add(terrain_editor_scene);

	this->CurrentViewedScene = terrain_editor_scene;





	BuildableObject::EndBuilding();
}

void EditorInstance::Update(double _TimeElapse) {
	EngineInstance::Update(_TimeElapse);
	anmation_manager->Update(_TimeElapse);
	bool actif = this->game_canvas->Update(this->Controlers, _TimeElapse);
	
}

void EditorInstance::HandleControler() {
	EngineInstance::HandleControler();
}

void EditorInstance::Render() {
	EngineInstance::Render();
	this->game_canvas->Render(this->GameRenderer);
}
