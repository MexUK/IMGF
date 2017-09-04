#pragma once

#include "nsbxgi.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"
#include <string>
#include <vector>

class bxgi::CIDEFormat;

class bxgi::CIDEManager : public bxcf::CFormatManager<bxgi::CIDEFormat>, public bxcf::CSingleton<bxgi::CIDEManager>
{
public:
	CIDEManager(void);
	
	void								init(void);
	void								uninit(void);

	static std::vector<std::string>		getIDEEntryNamesWithoutExtension(std::vector<std::string> vecIDEPaths, bool bModelNames = true, bool bTXDNames = true);
};