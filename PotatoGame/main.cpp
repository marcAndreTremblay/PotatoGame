#include "stdafx.h"
#include "EditorInstance.h"
#include "Quaternion.h"

#include "GameModel.h"


#include "Debugger.h"



int main(int argc, char **argv)
{
	
	Quaternion* quaternion_test = new Quaternion(1.f, 1.f, 1.f, 1.f);
	
	m4 *test = new m4();
	*test = glm::toMat4(*quaternion_test);
	delete(quaternion_test);
	delete(test);
	
	Debug::Instance().Write("Game starting");
	Debug::Instance().Write("Game starting");
	Debug::Instance().Write("Game starting");

	EditorInstance* main_instance = new EditorInstance();
			main_instance->Build();
			main_instance->Start();
		delete(main_instance);

		
	return 0;
}

