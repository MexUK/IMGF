#ifndef CICOManager_H
#define CICOManager_H

#include "bxa.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"

class bxa::CICOFormat;
class bxa::CBMPFormat;

class bxa::CICOManager : public bxa::CFormatManager<bxa::CICOFormat>, public bxa::CSingleton<bxa::CICOManager>
{
public:
	CICOManager(void);

	void						init(void);
	void						uninit(void);

	bxa::CICOFormat*			createFormatFromBMP(bxa::CBMPFormat *pBMPFormat);
};

#endif