#ifndef CIDEManager_H
#define CIDEManager_H

#include "bxcf.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"
#include <string>
#include <vector>

class bxcf::CIDEFormat;

class bxcf::CIDEManager : public bxcf::CFormatManager<bxcf::CIDEFormat>, public bxcf::CSingleton<bxcf::CIDEManager>
{
public:
	CIDEManager(void);
	
	void								init(void);
	void								uninit(void);

	static std::vector<std::string>		getIDEEntryNamesWithoutExtension(std::vector<std::string> vecIDEPaths, bool bModelNames = true, bool bTXDNames = true);
};

#endif