#ifndef CRasterDataFormatManager_H
#define CRasterDataFormatManager_H

#include "mcore.h"
#include "Object/CManager.h"
#include "CRasterDataFormat.h"
#include "Pool/CVectorPool.h"

class mcore::CRasterDataFormatManager : public mcore::CManager, public mcore::CVectorPool<mcore::CRasterDataFormat*>
{
public:
	void							init(void);
	void							uninit(void);

private:
	void							initRasterDataFormats(void);
};

#endif