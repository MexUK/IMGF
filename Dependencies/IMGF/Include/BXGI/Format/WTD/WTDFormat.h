#pragma once

#include "nsbxgi.h"
#include "Format/Format.h"
#include "Pool/VectorPool.h"
#include "WTDEntry.h"
#include "d3d9.h"
#include <string>

class bxgi::IntermediateTextureFormat;

class bxgi::WTDFormat : public bxcf::Format, public bxcf::VectorPool<bxgi::WTDEntry*>
{
public:
	WTDFormat(void) : Format(true, bxcf::LITTLE_ENDIAN) {}

	void						unload(void);

	bxgi::IntermediateTextureFormat*	convertToIntermediateFormat(void);

	static uint32				getFileHeaderFlagsFromSystemAndGraphicsStreamSizes(uint32 uiSystemStreamSize, uint32 uiGraphicsStreamSize);

	static std::string			getFourCCFromD3DFormat(D3DFORMAT d3dFormat);
	static D3DFORMAT			getD3DFormatFromFourCC(std::string strFourCC);

private:
	void						unserialize(void);
	void						serialize(void);

	static uint32				getCompactSize(uint32 uiSize);
	uint32						convertULongToOffset(uint32 uiValue);
	uint32						convertULongToDataOffset(uint32 uiValue);

	std::string					decompressWTDFormatData(uint32& uiSystemSegmentSize, uint32& uiGPUSegmentSize);
};