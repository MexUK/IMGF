#ifndef CIDEManager_H
#define CIDEManager_H

#include "bxa.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"
#include <string>
#include <vector>

class bxa::CIDEFormat;

class bxa::CIDEManager : public bxa::CFormatManager<bxa::CIDEFormat>, public bxa::CSingleton<bxa::CIDEManager>
{
public:
	CIDEManager(void);
	
	void								init(void);
	void								uninit(void);

	static std::vector<std::string>		getIDEEntryNamesWithoutExtension(std::vector<std::string> vecIDEPaths, bool bModelNames = true, bool bTXDNames = true);
};

#endif