#ifndef gui_hpp
#define gui_hpp

//Project Files
#include "../window/window.hpp"

//Pragma
#pragma once

namespace GUI
{
	// Initializes the IMGUI library
	void Init();

	// Unloads the IMGUI library
	void Destroy();
}

#endif /* guiInit_hpp */