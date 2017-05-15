#include "stdafx.h"
#include "CombatScene.h"


CombatScene::CombatScene(MousePicker* mouse_picker) : Scene(mouse_picker){

}


CombatScene::~CombatScene() {
}

void CombatScene::Update(Controler * controler, double timeElapse) {
	Scene::Update(controler, timeElapse);
}

void CombatScene::Render(BaseRenderer * renderer) {
	Scene::Render(renderer);
}

void CombatScene::Build() {
	Scene::Build();
	this->Set_Name("Combat_Scene");
	this->scene_camera = new Camera(
		v3(-15, -15, 15), //Possition
		v3(0, 0, 0), //look at
		v3(0, 0, 1)	 //up
	);
	this->Projection_Matrice = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 150.0f);
	this->ShouldRender = true;
}

void CombatScene::HandleControler(Controler * controler) {
	Scene::HandleControler(controler);
}
