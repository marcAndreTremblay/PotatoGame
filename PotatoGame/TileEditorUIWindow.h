#if !defined(TILE_EDITOR_UIWINDOW_H)
#define TILE_EDITOR_UIWINDOW_H

#include "AssetManager.h"
#include "Font.h"
using namespace PG::Engine;
#include "WindowMenu.h"
#include "DropDownMenu.h"
#include "Label.h"
using namespace PG::GUI;

class TileEditorUIWindow : public WindowMenu {
public:
	DropDownMenu* drop_down_menu_tile_top_material;
	TileEditorUIWindow(AssetManager* asset_manager);
	virtual ~TileEditorUIWindow();
	virtual void OnEvent(GUIEvent *event);
};
#endif

