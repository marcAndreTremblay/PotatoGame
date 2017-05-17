=============================================u===========================
    CONSOLE APPLICATION : PotatoGame Project Overview
========================================================================

AppWizard has created this PotatoGame application for you.

This file contains a summary of what you will find in each of the files that
make up your PotatoGame application.


PotatoGame.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

PotatoGame.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

PotatoGame.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named PotatoGame.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:
TODO(GameEditor)
	- Add a tab for in game item management
	- Add house file manager editor
	- Add a oepngGL widget
TODO(Game):
	- Map entities selection
	- Player entities movement
	- (FF) Simple AI with Map entitites
TODO(MapEditor):
	- Refactor the File model class so it's more generic for aall custom file'
	- Make the UI More robust, now prety bad
		- Make the UI and the scene , and game instance capable of talking to each other ... 
			- Implement map editor fonctionality into the UI
	- Add a file format description for each custom file format
	- Implement a Animation system 
		- Implement a File loading scene with a loading display

TODO(Engine):
	- Do ground work for scene transition
	- Implement a particle system , with physic ? 
	- Add debugger singleton for all debug output
	- Use Muthi-thread for the Update and Render
	- Create a Job System for prrallelize file loading and other loading
	- Refector the canvas to own by the engine instance
		- (FF)Implement a in engine console , extend a UI element and addd it to the engine canvas canvas

/////////////////////////////////////////////////////////////////////////////




Film_Info -> Role: ( film_id, acteur_id , str)