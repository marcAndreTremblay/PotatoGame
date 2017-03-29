// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once



#include <stdio.h>

#include "targetver.h"


//Note(marc): Include for the glew lib
#include "Lib/glew/glew.h"
#define GLEW_STATIC

//Note(marc): Include for the glfw lib
#include "Lib/glfw/glfw3.h"
#include "Lib/glm/glm.hpp"
#include "lib/glm/gtc/matrix_transform.hpp"


//Note(marc): Include for the Freetype lib
#include <ft2build.h>
#include FT_FREETYPE_H  

//Note(marc): Include for the Freeimage lib
#include"lib\freeimage\FreeImage.h"




