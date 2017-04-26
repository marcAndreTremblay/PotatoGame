#include "stdafx.h"
#include "EditorInstance.h"
#include "Quaternion.h"

#include "GameModel.h"

int main(int argc, char **argv)
{
	Quaternion *t = new Quaternion();

	

	EditorInstance* main_instance = new EditorInstance();
			main_instance->Build();
			main_instance->Start();
		delete(main_instance);

		
	return 0;
}

