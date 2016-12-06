#pragma warning(disable : 4005)

#include "CSortManager.h"
#include "CIMGF.h"
#include "Globals.h"
#include "Task/CTaskManager.h"
#include "Task/CTaskDispatchManager.h"
#include "Format/RockstarGames/IMG/CIMGFormat.h"
#include "Format/RockstarGames/IMG/CIMGEntry.h"
#include "Type/String/CString2.h"
#include "Type/StdVector/CStdVector.h"
#include "Path/CPathManager.h"
#include "CSortPriority.h"
#include "CSortType.h"
#include "eSortType.h"
#include "GUI/CGUIManager.h"
#include "CPopupGUIManager.h"
#include "Format/RockstarGames/IDE/CIDEManager.h"
#include "Format/RockstarGames/IDE/CIDEManager.h"
#include "Format/RockstarGames/COL/CCOLManager.h"
#include "Format/RockstarGames/COL/CCOLFormat.h"
#include "Localization/CLocalizationManager.h"
#include "CSortTypes.h"
#include "CSortPriorities.h"
#include "CSortMenuItems.h"
#include "Format/RockstarGames/IDE/CIDEFormat.h"
#include <algorithm>

using namespace std;
using namespace mcore;

CSortManager::CSortManager(void)
{
	m_pSortTypes = new CSortTypes;
	m_pSortPriorities = new CSortPriorities;
	m_pSortMenuItems = new CSortMenuItems;
}
CSortManager::~CSortManager(void)
{
	delete m_pSortTypes;
	delete m_pSortPriorities;
	delete m_pSortMenuItems;
}


void		CSortManager::init(void)
{
	initSortTypes();
	initSortPriorities();
}
void		CSortManager::uninit(void)
{
	uninitSortTypes();
	uninitSortPriorities();
}

void		CSortManager::initSortTypes(void)
{
	CSortType *pSortType = nullptr;

	pSortType = new CSortType;
	pSortType->setType(SORT_NAME_AZ);
	pSortType->setText(CLocalizationManager::getInstance()->getTranslatedText("Sort_EntryName_AToZ"));
	getSortTypes()->addEntry(pSortType);

	pSortType = new CSortType;
	pSortType->setType(SORT_NAME_ZA);
	pSortType->setText(CLocalizationManager::getInstance()->getTranslatedText("Sort_EntryName_ZToA"));
	getSortTypes()->addEntry(pSortType);

	pSortType = new CSortType;
	pSortType->setType(SORT_OFFSET_LOWHIGH);
	pSortType->setText(CLocalizationManager::getInstance()->getTranslatedText("Sort_Offset_LowToHigh"));
	getSortTypes()->addEntry(pSortType);

	pSortType = new CSortType;
	pSortType->setType(SORT_OFFSET_HIGHLOW);
	pSortType->setText(CLocalizationManager::getInstance()->getTranslatedText("Sort_Offset_HighToLow"));
	getSortTypes()->addEntry(pSortType);

	pSortType = new CSortType;
	pSortType->setType(SORT_SIZE_SMALLBIG);
	pSortType->setText(CLocalizationManager::getInstance()->getTranslatedText("Sort_Size_SmallToBig"));
	getSortTypes()->addEntry(pSortType);

	pSortType = new CSortType;
	pSortType->setType(SORT_SIZE_BIGSMALL);
	pSortType->setText(CLocalizationManager::getInstance()->getTranslatedText("Sort_Size_BigToSmall"));
	getSortTypes()->addEntry(pSortType);

	pSortType = new CSortType;
	pSortType->setType(SORT_IDE_FILE);
	pSortType->setText(CLocalizationManager::getInstance()->getTranslatedText("Sort_IDE"));
	getSortTypes()->addEntry(pSortType);

	pSortType = new CSortType;
	pSortType->setType(SORT_COL_FILE);
	pSortType->setText(CLocalizationManager::getInstance()->getTranslatedText("Sort_COL"));
	getSortTypes()->addEntry(pSortType);

	pSortType = new CSortType;
	pSortType->setType(SORT_FILE_EXTENSIONS);
	pSortType->setText(CLocalizationManager::getInstance()->getTranslatedText("Sort_Extensions"));
	getSortTypes()->addEntry(pSortType);
}
void		CSortManager::uninitSortTypes(void)
{
	getSortTypes()->removeAllEntries();
}

void		CSortManager::initSortPriorities(void)
{
	for (uint32 i = 0; i < 10; i++)
	{
		getSortPriorities()->addEntry(new CSortPriority);
	}
}
void		CSortManager::uninitSortPriorities(void)
{
	getSortPriorities()->removeAllEntries();
}

void		CSortManager::sort(CIMGFormat *pIMGFile)
{
	m_uiSortPriorityIndex = 0;
	std::sort(pIMGFile->getEntries().begin(), pIMGFile->getEntries().end(), CSortManager::sortIMGEntries);
}

bool		CSortManager::sortIMGEntries(CIMGEntry *p1, CIMGEntry *p2)
{
	CSortManager *pSortManager = getIMGF()->getSortManager();
	CSortPriority *pSortPriority = pSortManager->getSortPriorities()->getEntryByIndex((uint16)pSortManager->m_uiSortPriorityIndex);
	if (!pSortPriority->isEnabled())
	{
		//CDebugger::log("not enabled: " + CString2::toString((uint16)pSortManager->m_uiSortPriorityIndex));
		return false;
	}
	eSortType eSortType = pSortPriority->getType()->getType();
	if (eSortType == SORT_NAME_AZ)
	{
		if (CString2::toUpperCase(p1->getEntryName()) == CString2::toUpperCase(p2->getEntryName()))
		{
			pSortManager->m_uiSortPriorityIndex++;
			bool bResult = sortIMGEntries(p1, p2);
			pSortManager->m_uiSortPriorityIndex--;
			return bResult;
		}
		else if (CString2::toUpperCase(p1->getEntryName()) < CString2::toUpperCase(p2->getEntryName()))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (eSortType == SORT_NAME_ZA)
	{
		if (CString2::toUpperCase(p1->getEntryName()) == CString2::toUpperCase(p2->getEntryName()))
		{
			pSortManager->m_uiSortPriorityIndex++;
			bool bResult = sortIMGEntries(p1, p2);
			pSortManager->m_uiSortPriorityIndex--;
			return bResult;
		}
		else if (CString2::toUpperCase(p1->getEntryName()) > CString2::toUpperCase(p2->getEntryName()))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (eSortType == SORT_OFFSET_LOWHIGH)
	{
		if (p1->getEntryOffsetInSectors() == p2->getEntryOffsetInSectors())
		{
			pSortManager->m_uiSortPriorityIndex++;
			bool bResult = sortIMGEntries(p1, p2);
			pSortManager->m_uiSortPriorityIndex--;
			return bResult;
		}
		else if (p1->getEntryOffsetInSectors() < p2->getEntryOffsetInSectors())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (eSortType == SORT_OFFSET_HIGHLOW)
	{
		if (p1->getEntryOffsetInSectors() == p2->getEntryOffsetInSectors())
		{
			pSortManager->m_uiSortPriorityIndex++;
			bool bResult = sortIMGEntries(p1, p2);
			pSortManager->m_uiSortPriorityIndex--;
			return bResult;
		}
		else if (p1->getEntryOffsetInSectors() > p2->getEntryOffsetInSectors())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (eSortType == SORT_SIZE_SMALLBIG)
	{
		if (p1->getEntrySize() == p2->getEntrySize())
		{
			pSortManager->m_uiSortPriorityIndex++;
			bool bResult = sortIMGEntries(p1, p2);
			pSortManager->m_uiSortPriorityIndex--;
			return bResult;
		}
		else if (p1->getEntrySize() < p2->getEntrySize())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (eSortType == SORT_SIZE_BIGSMALL)
	{
		if (p1->getEntrySize() == p2->getEntrySize())
		{
			pSortManager->m_uiSortPriorityIndex++;
			bool bResult = sortIMGEntries(p1, p2);
			pSortManager->m_uiSortPriorityIndex--;
			return bResult;
		}
		else if (p1->getEntrySize() > p2->getEntrySize())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (eSortType == SORT_IDE_FILE)
	{
		uint32 uiKey1 = CStdVector::findKey(pSortPriority->getData(), CString2::toUpperCase(CPathManager::removeFileExtension(p1->getEntryName())));
		uint32 uiKey2 = CStdVector::findKey(pSortPriority->getData(), CString2::toUpperCase(CPathManager::removeFileExtension(p2->getEntryName())));
		if (uiKey1 == -1 || uiKey2 == -1)
		{
			return false;
		}
		else if (uiKey1 == uiKey2)
		{
			pSortManager->m_uiSortPriorityIndex++;
			bool bResult = sortIMGEntries(p1, p2);
			pSortManager->m_uiSortPriorityIndex--;
			return bResult;
		}
		else if (uiKey1 < uiKey2)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (eSortType == SORT_COL_FILE)
	{
		uint32 uiKey1 = CStdVector::findKey(pSortPriority->getData(), CString2::toUpperCase(CPathManager::removeFileExtension(p1->getEntryName())));
		uint32 uiKey2 = CStdVector::findKey(pSortPriority->getData(), CString2::toUpperCase(CPathManager::removeFileExtension(p2->getEntryName())));
		if (uiKey1 == -1 || uiKey2 == -1)
		{
			return false;
		}
		else if (uiKey1 == uiKey2)
		{
			pSortManager->m_uiSortPriorityIndex++;
			bool bResult = sortIMGEntries(p1, p2);
			pSortManager->m_uiSortPriorityIndex--;
			return bResult;
		}
		else if (uiKey1 < uiKey2)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (eSortType == SORT_FILE_EXTENSIONS)
	{
		uint32 uiKey1 = CStdVector::findKey(pSortPriority->getData(), CString2::toUpperCase(p1->getEntryName()));
		uint32 uiKey2 = CStdVector::findKey(pSortPriority->getData(), CString2::toUpperCase(p2->getEntryName()));
		if (uiKey1 == -1 || uiKey2 == -1)
		{
			return false;
		}
		else if (uiKey1 == uiKey2)
		{
			pSortManager->m_uiSortPriorityIndex++;
			bool bResult = sortIMGEntries(p1, p2);
			pSortManager->m_uiSortPriorityIndex--;
			return bResult;
		}
		else if (uiKey1 < uiKey2)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

void		CSortManager::setMenuPriorityTypesUnchecked(CSortPriority *pSortPriority)
{
	for (auto pSortMenuItem : getSortMenuItems()->getEntries())
	{
		if (pSortMenuItem->m_pPriority == pSortPriority)
		{
			// todo CheckMenuItem(getIMGF()->m_hMenu_Entry_Sort, pSortMenuItem->m_uiMenuHandle, MF_UNCHECKED);
		}
	}
}
void		CSortManager::setMenuPriorityTypeChecked(CSortPriority *pSortPriority, CSortType *pSortType, bool bState)
{
	for (auto pSortMenuItem : getSortMenuItems()->getEntries())
	{
		if (pSortMenuItem->m_pPriority == pSortPriority && pSortMenuItem->m_pType == pSortType)
		{
			// todo CheckMenuItem(getIMGF()->m_hMenu_Entry_Sort, pSortMenuItem->m_uiMenuHandle, bState ? MF_CHECKED : MF_UNCHECKED);
			break;
		}
	}
}

bool		CSortManager::isMenuHandleUsed(uint16 usMenuHandle)
{
	return getSortMenuItems()->getEntryByMenuHandle(usMenuHandle) != nullptr;
}
void		CSortManager::onClickMenuItem(uint16 usMenuHandle)
{
	bool bCancel = false;
	bool bCurrentState = false; // todo (GetMenuState(getIMGF()->m_hMenu_Entry_Sort, usMenuHandle, 0) & MF_CHECKED) == MF_CHECKED;
	CSortMenuItem *pSortMenuItem = getSortMenuItems()->getEntryByMenuHandle(usMenuHandle);
	CSortPriority *pSortPriority = pSortMenuItem->m_pPriority;

	setMenuPriorityTypesUnchecked(pSortPriority);

	if (bCurrentState)
	{
		setMenuPriorityTypeChecked(pSortPriority, pSortMenuItem->m_pType, false);
		pSortPriority->setEnabled(false);
	}
	else
	{
		setMenuPriorityTypeChecked(pSortPriority, pSortMenuItem->m_pType, true);
		pSortPriority->setEnabled(true);
		pSortPriority->setType(pSortMenuItem->m_pType);

		// todo CMenu *pSortMenu = nullptr; // todo CMenu::FromHandle(getIMGF()->m_hMenu_Entry_Sort);

		if (pSortMenuItem->m_pType->getType() == SORT_IDE_FILE)
		{
			vector<string> vecPaths = mcore::CGUIManager::openFileDialog(getIMGF()->getLastUsedDirectory("SORT_IDE"), "IDE", false);
			if (vecPaths.size() == 0)
			{
				bCancel = true;
			}
			else
			{
				getIMGF()->setLastUsedDirectory("SORT_IDE", CPathManager::getDirectory(vecPaths[0]));

				CIDEFormat *pIDEFile = CIDEManager::getInstance()->parseViaFile(vecPaths[0]);
				if(!pIDEFile->doesHaveError())
				{
					vector<string> vecModelNames = pIDEFile->getModelNames();
					vector<string> vecTextureNames = pIDEFile->getTXDNames();
					vector<string> vecEntryNames = CStdVector::toUpperCase(CStdVector::combineVectors(vecModelNames, vecTextureNames));
					pSortPriority->setData(vecEntryNames);
					pSortPriority->setStrData(CPathManager::getFileName(pIDEFile->getFilePath()));

					// todo pSortMenu->ModifyMenuW(usMenuHandle, 0, usMenuHandle, CLocalizationManager::getInstance()->getTranslatedFormattedTextW("Sort_ByText_WithFilename", pSortMenuItem->m_pType->getTextForMenu().c_str(), CPathManager::getFileName(pIDEFile->getFilePath()).c_str()).c_str());
				}
				pIDEFile->unload();
				delete pIDEFile;
			}
		}
		else if (pSortMenuItem->m_pType->getType() == SORT_COL_FILE)
		{
			vector<string> vecPaths = mcore::CGUIManager::openFileDialog(getIMGF()->getLastUsedDirectory("SORT_COL"), "COL", false);
			if (vecPaths.size() == 0)
			{
				bCancel = true;
			}
			else
			{
				getIMGF()->setLastUsedDirectory("SORT_COL", CPathManager::getDirectory(vecPaths[0]));

				CCOLFormat *pCOLFile = CCOLManager::getInstance()->parseViaFile(vecPaths[0]);
				if(!pCOLFile->doesHaveError())
				{
					vector<string> vecEntryNames = CStdVector::toUpperCase(pCOLFile->getModelNames());
					pSortPriority->setData(vecEntryNames);
					pSortPriority->setStrData(CPathManager::getFileName(pCOLFile->getFilePath()));

					// todo pSortMenu->ModifyMenuW(usMenuHandle, 0, usMenuHandle, CLocalizationManager::getInstance()->getTranslatedFormattedTextW("Sort_ByText_WithFilename", pSortMenuItem->m_pType->getTextForMenu().c_str(), CPathManager::getFileName(pCOLFile->getFilePath()).c_str()).c_str());
				}
				pCOLFile->unload();
				delete pCOLFile;
			}
		}
		else if (pSortMenuItem->m_pType->getType() == SORT_FILE_EXTENSIONS)
		{
			string strText = getIMGF()->getPopupGUIManager()->showTextInputDialog(CLocalizationManager::getInstance()->getTranslatedFormattedText("Sort_ByText", CLocalizationManager::getInstance()->getTranslatedTextW("Sort_Extensions").c_str()), CLocalizationManager::getInstance()->getTranslatedText("Window_TextInput_4_Message"));
			if (strText == "")
			{
				bCancel = true;
			}
			else
			{
				vector<string> vecFileExtensions = CString2::split(strText, ",");
				for (uint32 i = 0; i < vecFileExtensions.size(); i++)
				{
					vecFileExtensions[i] = CString2::toUpperCase(CString2::trim(vecFileExtensions[i]));
					if (vecFileExtensions[i].c_str()[0] == '.')
					{
						vecFileExtensions[i] = vecFileExtensions[i].substr(1);
					}
				}
				pSortPriority->setData(vecFileExtensions);
				pSortPriority->setStrData(CString2::join(vecFileExtensions, ", "));
				// todo pSortMenu->ModifyMenuW(usMenuHandle, 0, usMenuHandle, CLocalizationManager::getInstance()->getTranslatedFormattedTextW("Sort_ByText_WithFilename", pSortMenuItem->m_pType->getTextForMenu().c_str(), CString2::join(vecFileExtensions, ", ").c_str()).c_str());
			}
		}

		if (bCancel)
		{
			setMenuPriorityTypeChecked(pSortPriority, pSortMenuItem->m_pType, false);
		}
	}

	if (!bCancel)
	{
		getIMGF()->getTaskManager()->getDispatch()->onRequestSortEntries();
	}
}