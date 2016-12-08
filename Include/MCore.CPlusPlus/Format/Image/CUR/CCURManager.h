#ifndef CCURManager_H
#define CCURManager_H

#include "mcore.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"

class mcore::CCURFormat;
class mcore::CBMPFormat;

class mcore::CCURManager : public mcore::CFormatManager<mcore::CCURFormat>, public mcore::CSingleton<mcore::CCURManager>
{
public:
	CCURManager(void);

	void						init(void);
	void						uninit(void);

	CCURFormat*					createFormatFromBMP(CBMPFormat *pBMPFormat);
};

#endif