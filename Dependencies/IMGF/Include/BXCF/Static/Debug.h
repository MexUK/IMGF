#pragma once

#include "nsbxcf.h"
#include <string>

class bxcf::Debug
{
public:
	static void			log(std::string strData, std::string strPath = "");
};