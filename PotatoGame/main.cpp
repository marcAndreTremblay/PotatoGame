#include "stdafx.h"
#include "EditorInstance.h"
#include "Quaternion.h"

#include "GameModel.h"


#include "Debugger.h"

int main(int argc, char **argv)
{
	Quaternion *t = new Quaternion();

	Debug::Instance().Write("Game starting\n");

	EditorInstance* main_instance = new EditorInstance();
			main_instance->Build();
			main_instance->Start();
		delete(main_instance);

		
	return 0;
}

