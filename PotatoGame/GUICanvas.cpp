#include "stdafx.h"
#include "GUICanvas.h"

void PG::GUI::GUICanvas::AddElement(UIElement * element) {
	if (element != nullptr) {
		this->Element_list->Add(element);
	}
}
