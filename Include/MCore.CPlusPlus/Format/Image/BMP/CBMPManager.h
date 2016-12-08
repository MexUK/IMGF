#ifndef CBMPManager_H
#define CBMPManager_H

#include "mcore.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"

class mcore::CBMPFormat;

class mcore::CBMPManager : public mcore::CFormatManager<mcore::CBMPFormat>, public mcore::CSingleton<mcore::CBMPManager>
{
public:
	CBMPManager(void);

	void						init(void);
	void						uninit(void);
};

#endif