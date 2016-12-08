#ifndef CICOManager_H
#define CICOManager_H

#include "mcore.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"

class mcore::CICOFormat;
class mcore::CBMPFormat;

class mcore::CICOManager : public mcore::CFormatManager<mcore::CICOFormat>, public mcore::CSingleton<mcore::CICOManager>
{
public:
	CICOManager(void);

	void						init(void);
	void						uninit(void);

	mcore::CICOFormat*			createFormatFromBMP(mcore::CBMPFormat *pBMPFormat);
};

#endif