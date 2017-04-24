#if !defined(PG_EDITOR_INSTANCE_H)
#define PG_EDITOR_INSTANCE_H

#include "stdafx.h"
#include "EngineInstance.h"
#include "PGMapEditor.h"
#include "GUICanvas.h"


using namespace PG::Engine;
using namespace PG::GUI;

class PGEditorInstance :public EngineInstance {
protected:
	virtual void PGEditorInstance::Render() override {
		EngineInstance::Render();
		this->game_canvas->Render(this->GameRenderer);
	}
	virtual void PGEditorInstance::HandleControler() override {
		EngineInstance::HandleControler();
	}
	virtual void PGEditorInstance::Update(double _TimeElapse) override {
		bool actif = this->game_canvas->Update(this->Controlers, _TimeElapse);
		EngineInstance::Update(_TimeElapse);
	}
private:
	GUICanvas* game_canvas;
public:
	PGEditorInstance() {
	}
	~PGEditorInstance() {
		delete(game_canvas);
	}
	virtual void PGEditorInstance::Build() {
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
		PGMapEditor* terrain_editor_scene = new PGMapEditor();
		terrain_editor_scene->Set_Id(1);
		terrain_editor_scene->Build(this->Mouse_Picker);
		this->LoadedScenes->Add(terrain_editor_scene);

		this->CurrentViewedScene = terrain_editor_scene;





		BuildableObject::EndBuilding();
	}
};

#endif