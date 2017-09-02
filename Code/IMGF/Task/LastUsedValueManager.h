#pragma once

#include "nsimgf.h"
#include "Type/Types.h"
#include "Object/CManager.h"
#include "Format/IMG/Regular/EIMGVersion.h"
#include "Format/IMG/Regular/EIMGEntryProperty.h"
#include "Game/EPlatformedGame.h"
#include <string>

class bxgi::CRWVersion;
class bxcf::CRasterDataFormat;
class bxgi::CCOLVersion;

class imgf::LastUsedValueManager : public bxcf::CManager
{
public:
	LastUsedValueManager(void);
	
	void								init(void);
	void								uninit(void);
	
	// todo - remove "LastUsedValue" from all property names and method names.

	void								setLastUsedValue_Open2_IMGPath(std::string strIMGPath) { m_strLastUsedValue_Open2_IMGPath = strIMGPath; } // todo - move these funcs and properties to LastUsedValueManager
	std::string							getLastUsedValue_Open2_IMGPath(void) { return m_strLastUsedValue_Open2_IMGPath; }

	void								setLastUsedValue_Convert_IMGVersion(bxgi::EIMGVersion EIMGVersionValue) { m_uiLastUsedValue_Convert_IMGVersion = EIMGVersionValue; }
	bxgi::EIMGVersion							getLastUsedValue_Convert_IMGVersion(void) { return m_uiLastUsedValue_Convert_IMGVersion; }

	void								setLastUsedValue_ClearLogs_AllTabs(bool bAllTabs) { m_bLastUsedValue_ClearLogs_AllTabs = bAllTabs; }
	bool								getLastUsedValue_ClearLogs_AllTabs(void) { return m_bLastUsedValue_ClearLogs_AllTabs; }

	void								setLastUsedValue_Close2_CloseAll(bool bCloseAll) { m_bLastUsedValue_Close2_CloseAll = bCloseAll; }
	bool								getLastUsedValue_Close2_CloseAll(void) { return m_bLastUsedValue_Close2_CloseAll; }

	void								setLastUsedValue_ConvertDFF_RWVersion(bxgi::CRWVersion *pRWVersion) { m_pLastUsedValue_ConvertDFF_RWVersion = pRWVersion; }
	bxgi::CRWVersion*							getLastUsedValue_ConvertDFF_RWVersion(void) { return m_pLastUsedValue_ConvertDFF_RWVersion; }

	void								setLastUsedValue_ConvertTXD_Game(bxgi::EPlatformedGame EPlatformedGameValue) { m_uiLastUsedValue_ConvertTXD_Game = EPlatformedGameValue; }
	bxgi::EPlatformedGame						getLastUsedValue_ConvertTXD_Game(void) { return m_uiLastUsedValue_ConvertTXD_Game; }

	void								setLastUsedValue_ConvertTXD_TextureFormat(bxcf::CRasterDataFormat *pRasterDataFormat) { m_pLastUsedValue_ConvertTXD_RasterDataFormat = pRasterDataFormat; }
	bxcf::CRasterDataFormat*					getLastUsedValue_ConvertTXD_TextureFormat(void) { return m_pLastUsedValue_ConvertTXD_RasterDataFormat; }

	void								setLastUsedValue_Copy_IMGEntryProperty(bxgi::EIMGEntryProperty EIMGEntryPropertyValue) { m_uiLastUsedValue_Copy_IMGEntryProperty = EIMGEntryPropertyValue; }
	bxgi::EIMGEntryProperty					getLastUsedValue_Copy_IMGEntryProperty(void) { return m_uiLastUsedValue_Copy_IMGEntryProperty; }

	void								setLastUsedValue_SaveLog_ActiveTab(bool bActiveTab) { m_bLastUsedValue_SaveLog_ActiveTab = bActiveTab; }
	bool								getLastUsedValue_SaveLog_ActiveTab(void) { return m_bLastUsedValue_SaveLog_ActiveTab; }

	void								setLastUsedValue_SaveLog_NormalFormat(bool bNormalFormat) { m_bLastUsedValue_SaveLog_NormalFormat = bNormalFormat; }
	bool								getLastUsedValue_SaveLog_NormalFormat(void) { return m_bLastUsedValue_SaveLog_NormalFormat; }

	void								setLastUsedValue_Select_RWVersion(bxgi::CRWVersion *pRWVersion) { m_pLastUsedValue_Select_RWVersion = pRWVersion; }
	bxgi::CRWVersion*							getLastUsedValue_Select_RWVersion(void) { return m_pLastUsedValue_Select_RWVersion; }

	void								setLastUsedValue_Shift_Direction(uint8 ucShiftDirection) { m_ucLastUsedValue_Shift_Direction = ucShiftDirection; }
	uint8								getLastUsedValue_Shift_Direction(void) { return m_ucLastUsedValue_Shift_Direction; }

	void								setLastUsedValue_ConvertTXD_RWVersion(bxgi::CRWVersion *pRWVersion) { m_pLastUsedValue_ConvertTXD_RWVersion = pRWVersion; }
	bxgi::CRWVersion*							getLastUsedValue_ConvertTXD_RWVersion(void) { return m_pLastUsedValue_ConvertTXD_RWVersion; }

	void								setLastUsedValue_NameCase_CaseType(uint8 ucCaseType) { m_ucLastUsedValue_NameCase_CaseType = ucCaseType; }
	uint8								getLastUsedValue_NameCase_CaseType(void) { return m_ucLastUsedValue_NameCase_CaseType; }

	void								setLastUsedValue_NameCase_FilenameType(uint8 ucFilenameType) { m_ucLastUsedValue_NameCase_FilenameType = ucFilenameType; }
	uint8								getLastUsedValue_NameCase_FilenameType(void) { return m_ucLastUsedValue_NameCase_FilenameType; }

	void								setLastUsedValue_New_IMGVersion(bxgi::EIMGVersion EIMGVersionValue) { m_uiLastUsedValue_New_IMGVersion = EIMGVersionValue; }
	bxgi::EIMGVersion							getLastUsedValue_New_IMGVersion(void) { return m_uiLastUsedValue_New_IMGVersion; }

	void								setLastUsedValue_ConvertCOL_COLVersion(bxgi::CCOLVersion *pCOLVersion) { m_pLastUsedValue_ConvertCOL_COLVersion = pCOLVersion; }
	bxgi::CCOLVersion*						getLastUsedValue_ConvertCOL_COLVersion(void) { return m_pLastUsedValue_ConvertCOL_COLVersion; }

	void								setLastUsedValue_SortViaColumn_Column(uint32 uiColumnIndex) { m_uiLastUsedValue_SortViaColumn_Column = uiColumnIndex; }
	uint32								getLastUsedValue_SortViaColumn_Column(void) { return m_uiLastUsedValue_SortViaColumn_Column; }
	
private:
	std::string							m_strLastUsedValue_Open2_IMGPath;
	bxgi::EIMGVersion							m_uiLastUsedValue_Convert_IMGVersion;
	bool								m_bLastUsedValue_ClearLogs_AllTabs;
	bool								m_bLastUsedValue_Close2_CloseAll;
	bxgi::CRWVersion*							m_pLastUsedValue_ConvertDFF_RWVersion;
	bxgi::EPlatformedGame						m_uiLastUsedValue_ConvertTXD_Game;
	bxcf::CRasterDataFormat*					m_pLastUsedValue_ConvertTXD_RasterDataFormat;
	bxgi::EIMGEntryProperty					m_uiLastUsedValue_Copy_IMGEntryProperty;
	bool								m_bLastUsedValue_SaveLog_ActiveTab;
	bool								m_bLastUsedValue_SaveLog_NormalFormat;
	bxgi::CRWVersion*							m_pLastUsedValue_Select_RWVersion;
	uint8								m_ucLastUsedValue_Shift_Direction;
	bxgi::CRWVersion*							m_pLastUsedValue_ConvertTXD_RWVersion;
	uint8								m_ucLastUsedValue_NameCase_CaseType;
	uint8								m_ucLastUsedValue_NameCase_FilenameType;
	bxgi::EIMGVersion							m_uiLastUsedValue_New_IMGVersion;
	bxgi::CCOLVersion*						m_pLastUsedValue_ConvertCOL_COLVersion;
	uint32								m_uiLastUsedValue_SortViaColumn_Column;
};