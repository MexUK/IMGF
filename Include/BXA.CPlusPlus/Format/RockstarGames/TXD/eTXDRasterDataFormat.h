#ifndef eTXDRasterDataFormat_H
#define eTXDRasterDataFormat_H

#include "BXA.h"

enum bxa::eTXDRasterDataFormat
{
	TXDRASTERDATAFORMAT_DEFAULT					= 0,
	TXDRASTERDATAFORMAT_1555					= 0x100,
	TXDRASTERDATAFORMAT_565						= 0x200,
	TXDRASTERDATAFORMAT_4444					= 0x300,
	TXDRASTERDATAFORMAT_LUM8					= 0x400,
	TXDRASTERDATAFORMAT_8888					= 0x500,
	TXDRASTERDATAFORMAT_888						= 0x600,
	TXDRASTERDATAFORMAT_555						= 0xA00,

	TXDRASTERDATAFORMAT_EXT_AUTO_MIPMAP			= 0x1000,
	TXDRASTERDATAFORMAT_EXT_PAL8				= 0x2000,
	TXDRASTERDATAFORMAT_EXT_PAL4				= 0x4000,
	TXDRASTERDATAFORMAT_EXT_MIPMAP				= 0x8000,

	TXDRASTERDATAFORMAT_PS2_SWIZZLEDNOHEADER	= 0x10000,
	TXDRASTERDATAFORMAT_PS2_SWIZZLEDWITHHEADER	= 0x20000
};

#endif