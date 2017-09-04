#pragma once

#include "nsbxcf.h"
#include "Type/Types.h"
#include <string>

class bxcf::CompressionManager
{
public:
	static std::string				compressZLib(std::string& strData, uint32 uiCompressionLevel = 9);
	static std::string				decompressZLib(std::string& strData, uint32 uiUncompressedDataLength);

	static std::string				compressLZO1X999(std::string& strData);
	static std::string				decompressLZO1X(std::string& strData, uint32 uiUncompressedDataLength);

	static std::string				compressLZ4(std::string& strData, uint32 uiCompressionLevel = 9);
	static std::string				decompressLZ4(std::string& strData, uint32 uiUncompressedDataLength);
};