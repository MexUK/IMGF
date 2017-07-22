#ifndef CBMPManager_H
#define CBMPManager_H

#include "bxa.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"

class bxa::CBMPFormat;

class bxa::CBMPManager : public bxa::CFormatManager<bxa::CBMPFormat>, public bxa::CSingleton<bxa::CBMPManager>
{
public:
	CBMPManager(void);

	void						init(void);
	void						uninit(void);
};

#endif