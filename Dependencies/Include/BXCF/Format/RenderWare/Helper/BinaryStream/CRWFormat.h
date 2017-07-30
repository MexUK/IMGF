#ifndef CRWFormat_H
#define CRWFormat_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Format/CFormat.h"
#include "CRWSectionContainer.h"
#include "Format/RenderWare/Helper/BinaryStream/CRWVersion.h"
#include "Format/RenderWare/Helper/BinaryStream/eRWSection.h"
#include "Collection/Games/ePlatformedGame.h"
#include <vector>
#include <unordered_map>

class bxcf::CRWSection;
class bxcf::C2dEffect;
class bxcf::CTextureEntry;

class bxcf::CRWFormat : public bxcf::CFormat, public bxcf::CRWSectionContainer
{
public:
	CRWFormat(void) :
		CFormat(true, bxcf::LITTLE_ENDIAN),
		m_pRWVersion(nullptr)
	{};

	void												setRWVersion(CRWVersion* pRWVersion, bxcf::eRWSection eRWSectionValue = (bxcf::eRWSection)-1);	// Sets the RW version for all sections. Use -1 for eRWSectionValue to apply to all sections.
	CRWVersion*											getRWVersion(bxcf::eRWSection eRWSectionValue = (bxcf::eRWSection)-1);							// Sets the RW version for all sections. Use -1 for eRWSectionValue to apply to all sections.

	bxcf::CRWSection*											getLatestClump(void) { return nullptr; } // todo

	std::vector<bxcf::CTextureEntry*>&						getTextureEntries(void) { return m_vecTextureEntries; } // todo - inconsisteny in func name: Entry - remove word: Entry
	std::unordered_map<std::string, bxcf::CTextureEntry*>&	getTextureEntryNamesUpper(void) { return m_umapTexturesByNameUpper; } // todo - inconsisteny in func name: Entry - remove word: Entry
	void												removeTextureEntry(bxcf::CTextureEntry *pTextureEntry);

	bxcf::CTextureEntry*										getTextureByDiffuseName(std::string strTextureDiffuseName);
	bxcf::CTextureEntry*										getTextureByDiffuseOrAlphaName(std::string strTextureName);
	std::vector<std::string>							getTextureNames(void);

	void												fixAlphaTextureStates(void);
	bool												doesHaveTextureWithInvalidTXDRasterDataFormat(void);

	void												setGames(std::vector<bxcf::ePlatformedGame> vecGames) { m_vecGames = vecGames; }
	std::vector<bxcf::ePlatformedGame>&				getGames(void) { return m_vecGames; }

private:
	void												unserialize(void);
	void												serialize(void);

	void												loadTextureEntries(void);

private:
	CRWVersion*											m_pRWVersion;
	std::vector<bxcf::CTextureEntry*>							m_vecTextureEntries; // todo - inconsisteny in func name: Entry - remove word: Entry
	std::vector<bxcf::ePlatformedGame>					m_vecGames;
	std::unordered_map<std::string, bxcf::CTextureEntry*>		m_umapTexturesByNameUpper;
};

#endif