#pragma once

#include "nsimgf.h"
#include <string>
#include <vector>

class imgf::DragDrop
{
	void					onDropFiles(std::vector<std::string>& vecPaths);
};