#pragma once

#include "nsbxcf.h"
#include <string>

class bxcf::CDebug
{
public:
	static void			log(std::string strData, std::string strPath = "");
};