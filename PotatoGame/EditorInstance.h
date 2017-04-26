#if !defined(EDITOR_INSTANCE_H)
#define EDITOR_INSTANCE_H

#include "stdafx.h"
#include "EngineInstance.h"

#include "GUICanvas.h"
#include "CombatScene.h"
#include "MapEditorScene.h"

using namespace PG::Engine;
using namespace PG::GUI;

class EditorInstance :
	public EngineInstance {
private:
	GUICanvas* game_canvas;
public:
	EditorInstance();
	virtual ~EditorInstance();
	void Build();
	void Update(double _TimeElapse) override;
	void HandleControler() override;
	void Render() override;
};
#endif

