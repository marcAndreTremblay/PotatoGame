#include "stdafx.h"
#include "EditorInstance.h"

#include "GameModel.h"


#include "Debugger.h"

class command {
	command();
	~command();
	void Apply();
	void Undo();
};


int main(int argc, char **argv)
{
	
	Debug::Instance().Write("Game starting");

	EditorInstance* main_instance = new EditorInstance();
			main_instance->Build();
			main_instance->Start();
		delete(main_instance);

		
	return 0;
}

