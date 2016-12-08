#ifndef CIDEManager_H
#define CIDEManager_H

#include "mcore.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"
#include <string>
#include <vector>

class mcore::CIDEFormat;

class mcore::CIDEManager : public mcore::CFormatManager<mcore::CIDEFormat>, public mcore::CSingleton<mcore::CIDEManager>
{
public:
	CIDEManager(void);
	
	void								init(void);
	void								uninit(void);

	static std::vector<std::string>		getIDEEntryNamesWithoutExtension(std::vector<std::string> vecIDEPaths, bool bModelNames = true, bool bTXDNames = true);
};

#endif