#ifndef CRasterDataFormatManager_H
#define CRasterDataFormatManager_H

#include "BXA.h"
#include "Object/CManager.h"
#include "CRasterDataFormat.h"
#include "Pool/CVectorPool.h"

class bxa::CRasterDataFormatManager : public bxa::CManager, public bxa::CVectorPool<bxa::CRasterDataFormat*>
{
public:
	void							init(void);
	void							uninit(void);

private:
	void							initRasterDataFormats(void);
};

#endif