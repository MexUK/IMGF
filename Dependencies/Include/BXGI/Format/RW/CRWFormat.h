#ifndef CRWFormat_H
#define CRWFormat_H

#include "bxgi.h"
#include "Type/Types.h"
#include "Format/CFormat.h"
#include "CRWSectionContainer.h"
#include "Engine/RW/CRWVersion.h"
#include "Format/RW/eRWSection.h"
#include "Games/ePlatformedGame.h"
#include <vector>
#include <unordered_map>

class bxgi::CRWSection;
class bxgi::C2dEffect;
class bxgi::CTextureEntry;

class bxgi::CRWFormat : public bxcf::CFormat, public bxgi::CRWSectionContainer
{
public:
	CRWFormat(void) :
		CFormat(true, bxcf::LITTLE_ENDIAN),
		m_pRWVersion(nullptr)
	{};

	void												setRWVersion(CRWVersion* pRWVersion, bxgi::eRWSection eRWSectionValue = (bxgi::eRWSection)-1);	// Sets the RW version for all sections. Use -1 for eRWSectionValue to apply to all sections.
	CRWVersion*											getRWVersion(bxgi::eRWSection eRWSectionValue = (bxgi::eRWSection)-1);							// Sets the RW version for all sections. Use -1 for eRWSectionValue to apply to all sections.

	bxgi::CRWSection*											getLatestClump(void) { return nullptr; } // todo

	std::vector<bxgi::CTextureEntry*>&						getTextureEntries(void) { return m_vecTextureEntries; } // todo - inconsisteny in func name: Entry - remove word: Entry
	std::unordered_map<std::string, bxgi::CTextureEntry*>&	getTextureEntryNamesUpper(void) { return m_umapTexturesByNameUpper; } // todo - inconsisteny in func name: Entry - remove word: Entry
	void												removeTextureEntry(bxgi::CTextureEntry *pTextureEntry);

	bxgi::CTextureEntry*										getTextureByDiffuseName(std::string strTextureDiffuseName);
	bxgi::CTextureEntry*										getTextureByDiffuseOrAlphaName(std::string strTextureName);
	std::vector<std::string>							getTextureNames(void);

	void												fixAlphaTextureStates(void);
	bool												doesHaveTextureWithInvalidTXDRasterDataFormat(void);

	void												setGames(std::vector<bxgi::ePlatformedGame> vecGames) { m_vecGames = vecGames; }
	std::vector<bxgi::ePlatformedGame>&				getGames(void) { return m_vecGames; }

private:
	void												unserialize(void);
	void												serialize(void);

	void												loadTextureEntries(void);

private:
	CRWVersion*											m_pRWVersion;
	std::vector<bxgi::CTextureEntry*>							m_vecTextureEntries; // todo - inconsisteny in func name: Entry - remove word: Entry
	std::vector<bxgi::ePlatformedGame>					m_vecGames;
	std::unordered_map<std::string, bxgi::CTextureEntry*>		m_umapTexturesByNameUpper;
};

#endif