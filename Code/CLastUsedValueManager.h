#ifndef CLastUsedValueManager_H
#define CLastUsedValueManager_H

#include "Type/Types.h"
#include "Object/CManager.h"
#include "Format/RockstarGames/IMG/eIMGVersion.h"
#include "Format/RockstarGames/IMG/eIMGEntryProperty.h"
#include "Collection/Games/ePlatformedGame.h"
#include <string>

class mcore::CRWVersion;
class mcore::CRasterDataFormat;
class mcore::CCOLVersion;

class CLastUsedValueManager : public mcore::CManager
{
public:
	CLastUsedValueManager(void) :
		m_eLastUsedValue_Convert_IMGVersion(mcore::IMG_UNKNOWN),
		m_bLastUsedValue_ClearLogs_AllTabs(false),
		m_bLastUsedValue_Close2_CloseAll(false),
		m_pLastUsedValue_ConvertDFF_RWVersion(nullptr),
		m_eLastUsedValue_ConvertTXD_Game(mcore::PLATFORMED_GAME_UNKNOWN),
		m_pLastUsedValue_ConvertTXD_RasterDataFormat(nullptr),
		m_eLastUsedValue_Copy_IMGEntryProperty(mcore::IMG_ENTRY_ID),
		m_bLastUsedValue_SaveLog_ActiveTab(false),
		m_bLastUsedValue_SaveLog_NormalFormat(false),
		m_pLastUsedValue_Select_RWVersion(nullptr),
		m_ucLastUsedValue_Shift_Direction(0),
		m_pLastUsedValue_ConvertTXD_RWVersion(nullptr),
		m_ucLastUsedValue_NameCase_CaseType(0),
		m_ucLastUsedValue_NameCase_FilenameType(0),
		m_eLastUsedValue_New_IMGVersion(mcore::IMG_UNKNOWN),
		m_pLastUsedValue_ConvertCOL_COLVersion(nullptr),
		m_uiLastUsedValue_SortViaColumn_Column(0)
	{};
	
	void								init(void);
	void								uninit(void);
	
	// todo - remove "LastUsedValue" from all property names and method names.

	void								setLastUsedValue_Open2_IMGPath(std::string strIMGPath) { m_strLastUsedValue_Open2_IMGPath = strIMGPath; } // todo - move these funcs and properties to CLastUsedValueManager
	std::string							getLastUsedValue_Open2_IMGPath(void) { return m_strLastUsedValue_Open2_IMGPath; }

	void								setLastUsedValue_Convert_IMGVersion(mcore::eIMGVersion eIMGVersionValue) { m_eLastUsedValue_Convert_IMGVersion = eIMGVersionValue; }
	mcore::eIMGVersion							getLastUsedValue_Convert_IMGVersion(void) { return m_eLastUsedValue_Convert_IMGVersion; }

	void								setLastUsedValue_ClearLogs_AllTabs(bool bAllTabs) { m_bLastUsedValue_ClearLogs_AllTabs = bAllTabs; }
	bool								getLastUsedValue_ClearLogs_AllTabs(void) { return m_bLastUsedValue_ClearLogs_AllTabs; }

	void								setLastUsedValue_Close2_CloseAll(bool bCloseAll) { m_bLastUsedValue_Close2_CloseAll = bCloseAll; }
	bool								getLastUsedValue_Close2_CloseAll(void) { return m_bLastUsedValue_Close2_CloseAll; }

	void								setLastUsedValue_ConvertDFF_RWVersion(mcore::CRWVersion *pRWVersion) { m_pLastUsedValue_ConvertDFF_RWVersion = pRWVersion; }
	mcore::CRWVersion*							getLastUsedValue_ConvertDFF_RWVersion(void) { return m_pLastUsedValue_ConvertDFF_RWVersion; }

	void								setLastUsedValue_ConvertTXD_Game(mcore::ePlatformedGame ePlatformedGameValue) { m_eLastUsedValue_ConvertTXD_Game = ePlatformedGameValue; }
	mcore::ePlatformedGame						getLastUsedValue_ConvertTXD_Game(void) { return m_eLastUsedValue_ConvertTXD_Game; }

	void								setLastUsedValue_ConvertTXD_TextureFormat(mcore::CRasterDataFormat *pRasterDataFormat) { m_pLastUsedValue_ConvertTXD_RasterDataFormat = pRasterDataFormat; }
	mcore::CRasterDataFormat*					getLastUsedValue_ConvertTXD_TextureFormat(void) { return m_pLastUsedValue_ConvertTXD_RasterDataFormat; }

	void								setLastUsedValue_Copy_IMGEntryProperty(mcore::eIMGEntryProperty eIMGEntryPropertyValue) { m_eLastUsedValue_Copy_IMGEntryProperty = eIMGEntryPropertyValue; }
	mcore::eIMGEntryProperty					getLastUsedValue_Copy_IMGEntryProperty(void) { return m_eLastUsedValue_Copy_IMGEntryProperty; }

	void								setLastUsedValue_SaveLog_ActiveTab(bool bActiveTab) { m_bLastUsedValue_SaveLog_ActiveTab = bActiveTab; }
	bool								getLastUsedValue_SaveLog_ActiveTab(void) { return m_bLastUsedValue_SaveLog_ActiveTab; }

	void								setLastUsedValue_SaveLog_NormalFormat(bool bNormalFormat) { m_bLastUsedValue_SaveLog_NormalFormat = bNormalFormat; }
	bool								getLastUsedValue_SaveLog_NormalFormat(void) { return m_bLastUsedValue_SaveLog_NormalFormat; }

	void								setLastUsedValue_Select_RWVersion(mcore::CRWVersion *pRWVersion) { m_pLastUsedValue_Select_RWVersion = pRWVersion; }
	mcore::CRWVersion*							getLastUsedValue_Select_RWVersion(void) { return m_pLastUsedValue_Select_RWVersion; }

	void								setLastUsedValue_Shift_Direction(uint8 ucShiftDirection) { m_ucLastUsedValue_Shift_Direction = ucShiftDirection; }
	uint8								getLastUsedValue_Shift_Direction(void) { return m_ucLastUsedValue_Shift_Direction; }

	void								setLastUsedValue_ConvertTXD_RWVersion(mcore::CRWVersion *pRWVersion) { m_pLastUsedValue_ConvertTXD_RWVersion = pRWVersion; }
	mcore::CRWVersion*							getLastUsedValue_ConvertTXD_RWVersion(void) { return m_pLastUsedValue_ConvertTXD_RWVersion; }

	void								setLastUsedValue_NameCase_CaseType(uint8 ucCaseType) { m_ucLastUsedValue_NameCase_CaseType = ucCaseType; }
	uint8								getLastUsedValue_NameCase_CaseType(void) { return m_ucLastUsedValue_NameCase_CaseType; }

	void								setLastUsedValue_NameCase_FilenameType(uint8 ucFilenameType) { m_ucLastUsedValue_NameCase_FilenameType = ucFilenameType; }
	uint8								getLastUsedValue_NameCase_FilenameType(void) { return m_ucLastUsedValue_NameCase_FilenameType; }

	void								setLastUsedValue_New_IMGVersion(mcore::eIMGVersion eIMGVersionValue) { m_eLastUsedValue_New_IMGVersion = eIMGVersionValue; }
	mcore::eIMGVersion							getLastUsedValue_New_IMGVersion(void) { return m_eLastUsedValue_New_IMGVersion; }

	void								setLastUsedValue_ConvertCOL_COLVersion(mcore::CCOLVersion *pCOLVersion) { m_pLastUsedValue_ConvertCOL_COLVersion = pCOLVersion; }
	mcore::CCOLVersion*						getLastUsedValue_ConvertCOL_COLVersion(void) { return m_pLastUsedValue_ConvertCOL_COLVersion; }

	void								setLastUsedValue_SortViaColumn_Column(uint32 uiColumnIndex) { m_uiLastUsedValue_SortViaColumn_Column = uiColumnIndex; }
	uint32								getLastUsedValue_SortViaColumn_Column(void) { return m_uiLastUsedValue_SortViaColumn_Column; }
	
private:
	std::string							m_strLastUsedValue_Open2_IMGPath;
	mcore::eIMGVersion							m_eLastUsedValue_Convert_IMGVersion;
	bool								m_bLastUsedValue_ClearLogs_AllTabs;
	bool								m_bLastUsedValue_Close2_CloseAll;
	mcore::CRWVersion*							m_pLastUsedValue_ConvertDFF_RWVersion;
	mcore::ePlatformedGame						m_eLastUsedValue_ConvertTXD_Game;
	mcore::CRasterDataFormat*					m_pLastUsedValue_ConvertTXD_RasterDataFormat;
	mcore::eIMGEntryProperty					m_eLastUsedValue_Copy_IMGEntryProperty;
	bool								m_bLastUsedValue_SaveLog_ActiveTab;
	bool								m_bLastUsedValue_SaveLog_NormalFormat;
	mcore::CRWVersion*							m_pLastUsedValue_Select_RWVersion;
	uint8								m_ucLastUsedValue_Shift_Direction;
	mcore::CRWVersion*							m_pLastUsedValue_ConvertTXD_RWVersion;
	uint8								m_ucLastUsedValue_NameCase_CaseType;
	uint8								m_ucLastUsedValue_NameCase_FilenameType;
	mcore::eIMGVersion							m_eLastUsedValue_New_IMGVersion;
	mcore::CCOLVersion*						m_pLastUsedValue_ConvertCOL_COLVersion;
	uint32								m_uiLastUsedValue_SortViaColumn_Column;
};

#endif