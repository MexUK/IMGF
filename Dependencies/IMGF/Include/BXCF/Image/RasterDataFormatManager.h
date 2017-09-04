#pragma once

#include "nsbxcf.h"
#include "Object/Manager.h"
#include "RasterDataFormat.h"
#include "Pool/VectorPool.h"

class bxcf::RasterDataFormatManager : public bxcf::Manager, public bxcf::VectorPool<bxcf::RasterDataFormat*>
{
public:
	void							init(void);
	void							uninit(void);

private:
	void							initRasterDataFormats(void);
};