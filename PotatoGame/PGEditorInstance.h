#if !defined(PG_EDITOR_INSTANCE_H)
#define PG_EDITOR_INSTANCE_H

#include "stdafx.h"
#include "PGEngineInstance.h"
#include "PGEditorScene.h"
#include "PGUICanvas.h"


using namespace PG::Engine;
using namespace PG::GUI;

class PGEditorInstance :public PGEngineInstance {
protected:
	virtual void PGEditorInstance::Render() override {
		PGEngineInstance::Render();
		this->game_canvas->Render(this->GameRenderer);
	}
	virtual void PGEditorInstance::HandlerEvents() override {
		PGEngineInstance::HandlerEvents();

	}
	virtual void PGEditorInstance::HandleControler() override {
		PGEngineInstance::HandleControler();
	}
	virtual void PGEditorInstance::Update(double _TimeElapse) override {
		PGEngineInstance::Update(_TimeElapse);
		
		this->game_canvas->Update(this->Controlers, _TimeElapse);
	}
private:
	PGUICanvas* game_canvas;	
public:	
	PGEditorInstance() {
	}
	~PGEditorInstance()  {
		delete(game_canvas);
	}
	virtual void PGEditorInstance::Build() {
		PGEngineInstance::Build();
		PGBuildableObject::StartBuilding();

			//Build a work group for the game and active scenes
		

		
			this->AssetManager->LoadTexture(PG_PNG, "Asset/texture/Archer_right.png", "ArcherRight");
			this->AssetManager->LoadTexture(PG_BMP, "Asset/uvtemplate.bmp", "UV_Template");
			this->AssetManager->LoadTexture(PG_PNG, "Asset/texture/asteroid_1.png", "Asteroid_1");
			this->AssetManager->LoadTexture(PG_PNG, "Asset/texture/solar_panel.png", "SolarPanel");
			this->AssetManager->LoadTexture(PG_PNG, "Asset/texture/Water_0.png", "Water");

			//Load a basic Font for debugging
			this->Default_Engine_Font = this->AssetManager->LoadFont("Asset/font/Roboto-Bold.ttf", "Roboto_Bold");
			this->AssetManager->LoadFont("Asset/font/Roboto-Light.ttf", "Roboto-Light");
			this->AssetManager->LoadFont("Asset/font/Immortal.ttf", "Immortal");
			this->AssetManager->LoadFont("Asset/font/Hammersmith_Regular.ttf", "Hammersmith_Regular");
			

			
			
			
			//Build the needed UI for the game
			this->game_canvas = new PGUICanvas();
			this->game_canvas->Build(this->GameWindow,this->MousePicker ,this->AssetManager);
			
			
			//Build the first scene
			PGTerrainEditorScene* terrain_editor_scene = new PGTerrainEditorScene();
				terrain_editor_scene->Set_Id(1);
				terrain_editor_scene->Build(this->MousePicker);
			this->LoadedScenes->Add(terrain_editor_scene);

			this->CurrentViewedScene = terrain_editor_scene;





		PGBuildableObject::EndBuilding();
	}
};

#endif