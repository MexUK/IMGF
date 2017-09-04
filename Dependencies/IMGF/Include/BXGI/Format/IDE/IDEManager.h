#pragma once

#include "nsbxgi.h"
#include "Format/FormatManager.h"
#include "Object/Singleton.h"
#include <string>
#include <vector>

class bxgi::IDEFormat;

class bxgi::IDEManager : public bxcf::FormatManager<bxgi::IDEFormat>, public bxcf::Singleton<bxgi::IDEManager>
{
public:
	IDEManager(void);
	
	void								init(void);
	void								uninit(void);

	static std::vector<std::string>		getIDEEntryNamesWithoutExtension(std::vector<std::string> vecIDEPaths, bool bModelNames = true, bool bTXDNames = true);
};