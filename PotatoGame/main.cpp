#include "stdafx.h"
#include "PGEditorInstance.h"

#include "Quaternion.h"



int main(int argc, char **argv)
{
	Quaternion *t = new Quaternion();

	int i = 65;
	char c = (char)i;


	PGEditorInstance* main_instance = new PGEditorInstance();
			main_instance->Build();
			main_instance->Start();
		delete(main_instance);


	return 0;
}

