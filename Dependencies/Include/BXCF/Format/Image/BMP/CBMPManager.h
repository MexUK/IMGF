#ifndef CBMPManager_H
#define CBMPManager_H

#include "bxcf.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"

class bxcf::CBMPFormat;

class bxcf::CBMPManager : public bxcf::CFormatManager<bxcf::CBMPFormat>, public bxcf::CSingleton<bxcf::CBMPManager>
{
public:
	CBMPManager(void);

	void						init(void);
	void						uninit(void);
};

#endif