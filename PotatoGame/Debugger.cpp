#include "stdafx.h"
#include "Debugger.h"


Debug & Debug::Instance() {	
	static Debug _instance;
	return _instance;
}

void Debug::Write(char *message) {
	printf("%i", id);
	id++;
}

Debug::Debug(Debug const &) {
	id = 0;
}

Debug::Debug() {
	id = 0;
}


Debug::~Debug() {
}


