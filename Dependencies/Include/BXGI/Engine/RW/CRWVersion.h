#ifndef CRWVersion_H
#define CRWVersion_H

#include "bxgi.h"
#include "eRWVersion.h"
#include "eRWVersionType.h"
#include "Games/ePlatformedGame.h"
#include <string>
#include <vector>

class bxgi::CRWVersion
{
public:
	CRWVersion(void) :
		m_eVersionId(RW_VERSION_UNKNOWN),
		m_eVersionType(TYPE_MODEL),
		m_uiVersionCC(0),
		m_uiVersionGames(0)
	{};

	bxgi::ePlatformedGame					getFirstGame(void);
	std::vector<bxgi::ePlatformedGame>		getGames(void);

	void							unload(void) {}

	void							setVersionId(bxgi::eRWVersion eVersionId) { m_eVersionId = eVersionId; }
	bxgi::eRWVersion						getVersionId(void) { return m_eVersionId; }

	void							setVersionType(bxgi::eRWVersionType eVersionType) { m_eVersionType = eVersionType; }
	bxgi::eRWVersionType					getVersionType(void) { return m_eVersionType; }

	void							setVersionCC(uint32 uiVersionCC) { m_uiVersionCC = uiVersionCC; }
	uint32							getVersionCC(void) { return m_uiVersionCC; }

	void							setVersionName(std::string strVersionName) { m_strVersionName = strVersionName; }
	std::string						getVersionName(void) { return m_strVersionName; }

	void							setVersionGames(uint32 uiVersionGames) { m_uiVersionGames = uiVersionGames; }
	uint32							getVersionGames(void) { return m_uiVersionGames; }

	void							setVersionGamesStr(std::string strVersionGames) { m_strVersionGames = strVersionGames; }
	std::string						getVersionGamesStr(void) { return m_strVersionGames; }

	void							setLocalizationKey(std::string strLocalizationKey) { m_strLocalizationKey = strLocalizationKey; }
	std::string						getLocalizationKey(void) { return m_strLocalizationKey; }

	bool							doesGameUseVersion(bxgi::ePlatformedGame ePlatformedGameValue) { return (m_uiVersionGames & ePlatformedGameValue) == ePlatformedGameValue; }

	std::string						getText(void);

	static uint32					packVersionStamp(uint32 uiRWVersionNumber, uint32 uiRWBuildNumber);
	static uint32					unpackVersionStamp(uint32 uiRWVersionStamp);
	static std::string				unpackVersionStampAsString(uint32 uiRWVersionPackedInt);
	static std::string				unpackVersionStampAsStringWithBuild(uint32 uiRWVersionPackedInt);

private:
	bxgi::eRWVersion						m_eVersionId;				// e.g. 0
	bxgi::eRWVersionType					m_eVersionType;				// e.g. DFF
	uint32							m_uiVersionCC;				// e.g. 0xblah
	std::string						m_strVersionName;			// e.g. 3.0.0.0
	uint32							m_uiVersionGames;			// e.g. GAME_III | GAME_VC
	std::string						m_strVersionGames;			// e.g. GTA 3 & VC
	std::string						m_strLocalizationKey;		// e.g. RWVersion_1
};

#endif