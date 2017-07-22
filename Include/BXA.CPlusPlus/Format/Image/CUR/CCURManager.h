#ifndef CCURManager_H
#define CCURManager_H

#include "BXA.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"

class bxa::CCURFormat;
class bxa::CBMPFormat;

class bxa::CCURManager : public bxa::CFormatManager<bxa::CCURFormat>, public bxa::CSingleton<bxa::CCURManager>
{
public:
	CCURManager(void);

	void						init(void);
	void						uninit(void);

	CCURFormat*					createFormatFromBMP(CBMPFormat *pBMPFormat);
};

#endif