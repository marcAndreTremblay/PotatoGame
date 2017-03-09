#include "stdafx.h"
#include "PGEditorInstance.h"




int main(int argc, char **argv)
{
	PGEditorInstance* main_instance = new PGEditorInstance();
		main_instance->Build();
		main_instance->Start();
	delete(main_instance);
	return 0;
}

