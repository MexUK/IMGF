#ifndef CBMPFormat_H
#define CBMPFormat_H

#include "bxa.h"
#include "Type/Types.h"
#include "Format/CFormat.h"
#include <string>
#include <vector>

class bxa::CBMPFormat : public bxa::CFormat
{
public:
	CBMPFormat(void);

	void							unload(void) {}

	void							setSkipBMPFileHeaderForSerialize(bool bSkipBMPFileHeaderForSerialize) { m_bSkipBMPFileHeaderForSerialize = bSkipBMPFileHeaderForSerialize; }
	bool							getSkipBMPFileHeaderForSerialize(void) { return m_bSkipBMPFileHeaderForSerialize; }

	void							setBMPVersion(uint8 uiBMPVersion) { m_uiBMPVersion = uiBMPVersion; }
	uint8							getBMPVersion(void) { return m_uiBMPVersion; }

	void							setRasterDataBGRA32(std::string& strRasterDataBGRA32);
	std::string						getRasterDataBGRA32(void);

	void							swapRows(void);

	void							setFileType(uint16 usFileType) { m_usFileType = usFileType; }
	uint16							getFileType(void) { return m_usFileType; }

	void							setFileSize(uint16 usFileSize) { m_usFileSize = usFileSize; }
	uint16							getFileSize(void) { return m_usFileSize; }

	void							setColourPlaneCount(uint16 usColourPlaneCount) { m_usColourPlaneCount = usColourPlaneCount; }
	uint16							getColourPlaneCount(void) { return m_usColourPlaneCount; }

	void							setHasPalette(bool bHasPalette) { m_bHasPalette = bHasPalette; }
	bool							doesHavePalette(void) { return m_bHasPalette; }

	void							setPaletteData(std::string& strPaletteData) { m_strPaletteData = strPaletteData; }
	std::string&					getPaletteData(void) { return m_strPaletteData; }

	void							setRasterData(std::string& strRasterData) { m_strRasterData = strRasterData; }
	std::string&					getRasterData(void) { return m_strRasterData; }

	void							setWidth(uint32 uiWidth) { m_uiWidth = uiWidth; }
	uint32							getWidth(void) { return m_uiWidth; }

	void							setHeight(uint32 uiHeight) { m_uiHeight = uiHeight; }
	uint32							getHeight(void) { return m_uiHeight; }

	void							setBPP(uint16 usBPP) { m_usBPP = usBPP; }
	uint16							getBPP(void) { return m_usBPP; }

private:
	virtual void					unserialize(void);
	virtual void					serialize(void);

	void							unserializeVersion1(void);
	void							unserializeVersion2(void);
	void							unserializeVersion3(void);
	void							unserializeVersion4(void);

	void							serializeVersion1(void);
	void							serializeVersion2(void);
	void							serializeVersion3(void);
	void							serializeVersion4(void);

	uint8							detectBMPVersion(void);

private:
	uint8							m_bSkipBMPFileHeaderForSerialize	: 1;
	uint8							m_bHasPalette						: 1;
	uint8							m_uiBMPVersion;
	uint16							m_usFileType;
	uint16							m_usFileSize;
	uint16							m_usColourPlaneCount;
	std::string						m_strPaletteData;
	std::string						m_strRasterData;
	uint32							m_uiWidth;
	uint32							m_uiHeight;
	uint16							m_usBPP;
};

#endif