#pragma once

#include "nsimgf.h"
#include <string>
#include <vector>

class imgf::CDragDrop
{
	void					onDropFiles(std::vector<std::string>& vecPaths);
};