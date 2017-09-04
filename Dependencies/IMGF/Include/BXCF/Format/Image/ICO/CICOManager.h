#pragma once

#include "nsbxcf.h"
#include "Format/CFormatManager.h"
#include "Object/CSingleton.h"

class bxcf::CICOFormat;
class bxcf::CBMPFormat;

class bxcf::CICOManager : public bxcf::CFormatManager<bxcf::CICOFormat>, public bxcf::CSingleton<bxcf::CICOManager>
{
public:
	CICOManager(void);

	void						init(void);
	void						uninit(void);

	bxcf::CICOFormat*			createFormatFromBMP(bxcf::CBMPFormat *pBMPFormat);
};