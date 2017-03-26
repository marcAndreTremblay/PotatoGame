#include "stdafx.h"
#include "PGEditorInstance.h"

#include "PGAssetManager.h"


#include "PGTree.h"



#include "PGString.h"
#include "PGTexture.h"




int main(int argc, char **argv)
{

	
		PGEditorInstance* main_instance = new PGEditorInstance();
			main_instance->Build();
			main_instance->Start();
			


	return 0;
}

