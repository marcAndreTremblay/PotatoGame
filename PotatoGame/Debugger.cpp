#include "stdafx.h"
#include "Debugger.h"


Debug & Debug::Instance() {
	static Debug instance;
	return instance;
}

void Debug::Write(char *message) {
	printf(message);
}

Debug::Debug(Debug const &) {
}

Debug::Debug() {
}


Debug::~Debug() {
}


