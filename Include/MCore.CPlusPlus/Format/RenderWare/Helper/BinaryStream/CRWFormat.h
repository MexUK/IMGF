#ifndef CRWFormat_H
#define CRWFormat_H

#include "bxa.h"
#include "Type/Types.h"
#include "Format/CFormat.h"
#include "CRWSectionContainer.h"
#include "Format/RenderWare/Helper/BinaryStream/CRWVersion.h"
#include "Format/RenderWare/Helper/BinaryStream/eRWSection.h"
#include "Collection/Games/ePlatformedGame.h"
#include <vector>
#include <unordered_map>

class bxa::CRWSection;
class bxa::C2dEffect;
class bxa::CTextureEntry;

class bxa::CRWFormat : public bxa::CFormat, public bxa::CRWSectionContainer
{
public:
	CRWFormat(void) :
		CFormat(true, bxa::LITTLE_ENDIAN),
		m_pRWVersion(nullptr)
	{};

	void												setRWVersion(CRWVersion* pRWVersion, bxa::eRWSection eRWSectionValue = (bxa::eRWSection)-1);	// Sets the RW version for all sections. Use -1 for eRWSectionValue to apply to all sections.
	CRWVersion*											getRWVersion(bxa::eRWSection eRWSectionValue = (bxa::eRWSection)-1);							// Sets the RW version for all sections. Use -1 for eRWSectionValue to apply to all sections.

	bxa::CRWSection*											getLatestClump(void) { return nullptr; } // todo

	std::vector<bxa::CTextureEntry*>&						getTextureEntries(void) { return m_vecTextureEntries; } // todo - inconsisteny in func name: Entry - remove word: Entry
	std::unordered_map<std::string, bxa::CTextureEntry*>&	getTextureEntryNamesUpper(void) { return m_umapTexturesByNameUpper; } // todo - inconsisteny in func name: Entry - remove word: Entry
	void												removeTextureEntry(bxa::CTextureEntry *pTextureEntry);

	bxa::CTextureEntry*										getTextureByDiffuseName(std::string strTextureDiffuseName);
	bxa::CTextureEntry*										getTextureByDiffuseOrAlphaName(std::string strTextureName);
	std::vector<std::string>							getTextureNames(void);

	void												fixAlphaTextureStates(void);
	bool												doesHaveTextureWithInvalidTXDRasterDataFormat(void);

	void												setGames(std::vector<bxa::ePlatformedGame> vecGames) { m_vecGames = vecGames; }
	std::vector<bxa::ePlatformedGame>&				getGames(void) { return m_vecGames; }

private:
	void												unserialize(void);
	void												serialize(void);

	void												loadTextureEntries(void);

private:
	CRWVersion*											m_pRWVersion;
	std::vector<bxa::CTextureEntry*>							m_vecTextureEntries; // todo - inconsisteny in func name: Entry - remove word: Entry
	std::vector<bxa::ePlatformedGame>					m_vecGames;
	std::unordered_map<std::string, bxa::CTextureEntry*>		m_umapTexturesByNameUpper;
};

#endif