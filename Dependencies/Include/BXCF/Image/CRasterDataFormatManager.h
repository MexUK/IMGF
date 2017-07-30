#ifndef CRasterDataFormatManager_H
#define CRasterDataFormatManager_H

#include "bxcf.h"
#include "Object/CManager.h"
#include "CRasterDataFormat.h"
#include "Pool/CVectorPool.h"

class bxcf::CRasterDataFormatManager : public bxcf::CManager, public bxcf::CVectorPool<bxcf::CRasterDataFormat*>
{
public:
	void							init(void);
	void							uninit(void);

private:
	void							initRasterDataFormats(void);
};

#endif