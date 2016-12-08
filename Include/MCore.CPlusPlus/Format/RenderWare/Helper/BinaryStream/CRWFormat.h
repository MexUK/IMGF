#ifndef CRWFormat_H
#define CRWFormat_H

#include "mcore.h"
#include "Type/Types.h"
#include "Format/CFormat.h"
#include "CRWSectionContainer.h"
#include "Format/RenderWare/Helper/BinaryStream/CRWVersion.h"
#include "Format/RenderWare/Helper/BinaryStream/eRWSection.h"
#include "Collection/Games/ePlatformedGame.h"
#include <vector>
#include <unordered_map>

class mcore::CRWSection;
class mcore::C2dEffect;
class mcore::CTextureEntry;

class mcore::CRWFormat : public mcore::CFormat, public mcore::CRWSectionContainer
{
public:
	CRWFormat(void) :
		CFormat(true, mcore::LITTLE_ENDIAN),
		m_pRWVersion(nullptr)
	{};

	void												setRWVersion(CRWVersion* pRWVersion, mcore::eRWSection eRWSectionValue = (mcore::eRWSection)-1);	// Sets the RW version for all sections. Use -1 for eRWSectionValue to apply to all sections.
	CRWVersion*											getRWVersion(mcore::eRWSection eRWSectionValue = (mcore::eRWSection)-1);							// Sets the RW version for all sections. Use -1 for eRWSectionValue to apply to all sections.

	mcore::CRWSection*											getLatestClump(void) { return nullptr; } // todo

	std::vector<mcore::CTextureEntry*>&						getTextureEntries(void) { return m_vecTextureEntries; } // todo - inconsisteny in func name: Entry - remove word: Entry
	std::unordered_map<std::string, mcore::CTextureEntry*>&	getTextureEntryNamesUpper(void) { return m_umapTexturesByNameUpper; } // todo - inconsisteny in func name: Entry - remove word: Entry
	void												removeTextureEntry(mcore::CTextureEntry *pTextureEntry);

	mcore::CTextureEntry*										getTextureByDiffuseName(std::string strTextureDiffuseName);
	mcore::CTextureEntry*										getTextureByDiffuseOrAlphaName(std::string strTextureName);
	std::vector<std::string>							getTextureNames(void);

	void												fixAlphaTextureStates(void);
	bool												doesHaveTextureWithInvalidTXDRasterDataFormat(void);

	void												setGames(std::vector<mcore::ePlatformedGame> vecGames) { m_vecGames = vecGames; }
	std::vector<mcore::ePlatformedGame>&				getGames(void) { return m_vecGames; }

private:
	void												unserialize(void);
	void												serialize(void);

	void												loadTextureEntries(void);

private:
	CRWVersion*											m_pRWVersion;
	std::vector<mcore::CTextureEntry*>							m_vecTextureEntries; // todo - inconsisteny in func name: Entry - remove word: Entry
	std::vector<mcore::ePlatformedGame>					m_vecGames;
	std::unordered_map<std::string, mcore::CTextureEntry*>		m_umapTexturesByNameUpper;
};

#endif