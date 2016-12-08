#ifndef CRWVersion_H
#define CRWVersion_H

#include "mcore.h"
#include "eRWVersion.h"
#include "eRWVersionType.h"
#include "Collection/Games/ePlatformedGame.h"
#include <string>
#include <vector>

class mcore::CRWVersion
{
public:
	CRWVersion(void) :
		m_eVersionId(RW_VERSION_UNKNOWN),
		m_eVersionType(TYPE_MODEL),
		m_uiVersionCC(0),
		m_uiVersionGames(0)
	{};

	mcore::ePlatformedGame					getFirstGame(void);
	std::vector<mcore::ePlatformedGame>		getGames(void);

	void							unload(void) {}

	void							setVersionId(mcore::eRWVersion eVersionId) { m_eVersionId = eVersionId; }
	mcore::eRWVersion						getVersionId(void) { return m_eVersionId; }

	void							setVersionType(mcore::eRWVersionType eVersionType) { m_eVersionType = eVersionType; }
	mcore::eRWVersionType					getVersionType(void) { return m_eVersionType; }

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

	bool							doesGameUseVersion(mcore::ePlatformedGame ePlatformedGameValue) { return (m_uiVersionGames & ePlatformedGameValue) == ePlatformedGameValue; }

	std::string						getText(void);

	static uint32					packVersionStamp(uint32 uiRWVersionNumber, uint32 uiRWBuildNumber);
	static uint32					unpackVersionStamp(uint32 uiRWVersionStamp);

private:
	mcore::eRWVersion						m_eVersionId;				// e.g. 0
	mcore::eRWVersionType					m_eVersionType;				// e.g. DFF
	uint32							m_uiVersionCC;				// e.g. 0xblah
	std::string						m_strVersionName;			// e.g. 3.0.0.0
	uint32							m_uiVersionGames;			// e.g. GAME_III | GAME_VC
	std::string						m_strVersionGames;			// e.g. GTA 3 & VC
	std::string						m_strLocalizationKey;		// e.g. RWVersion_1
};

#endif