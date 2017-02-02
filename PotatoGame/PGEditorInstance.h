#if !defined(PG_EDITOR_INSTANCE_H)
#define PG_EDITOR_INSTANCE_H

#include "stdafx.h"
#include "PGBaseGame.h"


using namespace PGEngine;

class PGEditorInstance :public PGBaseGame {
protected:
	virtual void PGEditorInstance::Render() override {
		PGBaseGame::Render();
		this->game_canvas->Render(this->GameRenderer);
		
		
	}
	virtual void PGEditorInstance::HandlerEvents() override {
		PGBaseGame::HandlerEvents();

	}
	virtual void PGEditorInstance::HandleControler() override {
		PGBaseGame::HandleControler();
	}
	virtual void PGEditorInstance::Update(double _TimeElapse) override {
		PGBaseGame::Update(_TimeElapse);
		
		this->game_canvas->Update(this->Controlers, _TimeElapse);
	}
private:
	PGUICanvas* game_canvas;	
public:
	PGEditorInstance() {
	}
	~PGEditorInstance() {
		delete(game_canvas);
	}
	virtual void PGEditorInstance::Build() {
		PGBaseGame::Build();
		PGBuildableObject::StartBuilding();

			//Build a work group for the game and active scenes
			this->WorkGroup = EventManager->AddWorkGroup("Game_Scene\n");

		
			this->AssetManager->LoadTexture(PG_PNG, "Asset/texture/Archer_right.png", "ArcherRight\n");
			this->AssetManager->LoadTexture(PG_BMP, "Asset/uvtemplate.bmp", "UV_Template\n");
			this->AssetManager->LoadTexture(PG_PNG, "Asset/texture/asteroid_1.png", "Asteroid_1\n");
			this->AssetManager->LoadTexture(PG_PNG, "Asset/texture/solar_panel.png", "SolarPanel\n");
			 
			//Load a basic Font for debugging
			this->Default_Engine_Font = this->AssetManager->LoadFont("Asset/font/Roboto-Bold.ttf", "Roboto_Bold\n");
			this->AssetManager->LoadFont("Asset/font/Roboto-Light.ttf", "Roboto-Light\n");
			this->AssetManager->LoadFont("Asset/font/Immortal.ttf", "Immortal\n");
			this->AssetManager->LoadFont("Asset/font/Hammersmith_Regular.ttf", "Hammersmith_Regular\n");
			

			
			//Build the needed UI for the game
			this->game_canvas = new PGUICanvas();
			this->game_canvas->Build(this->GameWindow,this->MousePicker ,this->AssetManager);

			//Build the first scene
			PGTerrainEditorScene* terrain_editor_scene = new PGTerrainEditorScene();
				terrain_editor_scene->Set_Id(1);
				terrain_editor_scene->Build(this->WorkGroup, this->MousePicker);
			this->LoadedScenes->Add(terrain_editor_scene);

			this->CurrentViewedScene = terrain_editor_scene;





		PGBuildableObject::EndBuilding();
	}
};

#endif