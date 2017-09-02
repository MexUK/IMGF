#include "LastUsedValueManager.h"

using namespace bxcf;
using namespace imgf;

LastUsedValueManager::LastUsedValueManager(void) :
	m_uiLastUsedValue_Convert_IMGVersion(bxgi::IMG_UNKNOWN),
	m_bLastUsedValue_ClearLogs_AllTabs(false),
	m_bLastUsedValue_Close2_CloseAll(false),
	m_pLastUsedValue_ConvertDFF_RWVersion(nullptr),
	m_uiLastUsedValue_ConvertTXD_Game(bxgi::UNKNOWN_PLATFORMED_GAME),
	m_pLastUsedValue_ConvertTXD_RasterDataFormat(nullptr),
	m_uiLastUsedValue_Copy_IMGEntryProperty(bxgi::IMG_ENTRY_ID),
	m_bLastUsedValue_SaveLog_ActiveTab(false),
	m_bLastUsedValue_SaveLog_NormalFormat(false),
	m_pLastUsedValue_Select_RWVersion(nullptr),
	m_ucLastUsedValue_Shift_Direction(0),
	m_pLastUsedValue_ConvertTXD_RWVersion(nullptr),
	m_ucLastUsedValue_NameCase_CaseType(0),
	m_ucLastUsedValue_NameCase_FilenameType(0),
	m_uiLastUsedValue_New_IMGVersion(bxgi::IMG_UNKNOWN),
	m_pLastUsedValue_ConvertCOL_COLVersion(nullptr),
	m_uiLastUsedValue_SortViaColumn_Column(0)
{
}

void								LastUsedValueManager::init(void)
{
}

void								LastUsedValueManager::uninit(void)
{
}