#include "stdafx.h"
#include "TileEditorUIWindow.h"


TileEditorUIWindow::TileEditorUIWindow(AssetManager* asset_manager) : WindowMenu(){
	this->SetSize(PG::Core::v2(300, 400));


	Font* default_f = asset_manager->SeachForFont("Hammersmith_Regular");

	Label * lab0 = new Label(new Str("Tile Atributes :"), default_f);
		lab0->SetPossition(v2(5.f, 5.f));
		lab0->text_scale = 0.5f;
	Label * lab1 = new Label(new Str("Top mat"), default_f);
		lab1->SetPossition(v2(5.f, 35.f));
		lab1->text_scale = 0.5f;
	Label * lab2 = new Label(new Str("Bottom mat"), default_f);
		lab2->SetPossition(v2(5.f, 65.f));
		lab2->text_scale = 0.5f;
	this->AddChild(lab0);
	this->AddChild(lab1);
	this->AddChild(lab2);
	DropDownMenu* bottom_tile_style_drop_down = new DropDownMenu(default_f);
		bottom_tile_style_drop_down->SetSize(v2(120, 25.f));
		bottom_tile_style_drop_down->SetPossition(v2(150.f, 65.f));
	this->AddChild(bottom_tile_style_drop_down);
		bottom_tile_style_drop_down->AddElement(new GUIStringNode("Grass 1\n", default_f));
		bottom_tile_style_drop_down->AddElement(new GUIStringNode("Water 1\n", default_f));
		bottom_tile_style_drop_down->AddElement(new GUIStringNode("Dirt 1\n", default_f));
		bottom_tile_style_drop_down->AddElement(new GUIStringNode("Rock 1\n", default_f));
	DropDownMenu* topo_tile_style_drop_down = new DropDownMenu(default_f);
		topo_tile_style_drop_down->SetSize(v2(120,30));
		topo_tile_style_drop_down->SetPossition(v2(100.f, 30.f));
	this->AddChild(topo_tile_style_drop_down);
		topo_tile_style_drop_down->AddElement(new GUIStringNode("Rock 1\n", default_f));
		topo_tile_style_drop_down->AddElement(new GUIStringNode("Dirt 1\n", default_f));
		topo_tile_style_drop_down->AddElement(new GUIStringNode("Water 1\n", default_f));

}


TileEditorUIWindow::~TileEditorUIWindow() {
}
