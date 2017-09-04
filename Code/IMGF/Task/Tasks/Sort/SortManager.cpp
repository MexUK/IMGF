#pragma warning(disable : 4005)

#include "SortManager.h"
#include "IMGF.h"
#include "Globals.h"
#include "Task/TaskManager.h"
#include "Task/Tasks/Tasks.h"
#include "Format/IMG/Regular/IMGFormat.h"
#include "Format/IMG/Regular/IMGEntry.h"
#include "Static/String.h"
#include "Static/StdVector.h"
#include "Static/Path.h"
#include "SortPriority.h"
#include "SortType.h"
#include "ESortType.h"
#include "Static/Input.h"
#include "Format/IDE/IDEManager.h"
#include "Format/COL/COLManager.h"
#include "Format/COL/COLFormat.h"
#include "Localization/LocalizationManager.h"
#include "SortTypes.h"
#include "SortPriorities.h"
#include "SortMenuItems.h"
#include "Format/IDE/IDEFormat.h"
#include <algorithm>

using namespace std;
using namespace bxcf;
using namespace bxgi;
using namespace imgf;

SortManager::SortManager(void)
{
	m_pSortTypes = new SortTypes;
	m_pSortPriorities = new SortPriorities;
	m_pSortMenuItems = new SortMenuItems;
}
SortManager::~SortManager(void)
{
	delete m_pSortTypes;
	delete m_pSortPriorities;
	delete m_pSortMenuItems;
}


void		SortManager::init(void)
{
	initSortTypes();
	initSortPriorities();
}
void		SortManager::uninit(void)
{
	uninitSortTypes();
	uninitSortPriorities();
}

void		SortManager::initSortTypes(void)
{
	SortType *pSortType = nullptr;

	pSortType = new SortType;
	pSortType->setType(SORT_NAME_AZ);
	pSortType->setText(LocalizationManager::get()->getTranslatedText("Sort_EntryName_AToZ"));
	getSortTypes()->addEntry(pSortType);

	pSortType = new SortType;
	pSortType->setType(SORT_NAME_ZA);
	pSortType->setText(LocalizationManager::get()->getTranslatedText("Sort_EntryName_ZToA"));
	getSortTypes()->addEntry(pSortType);

	pSortType = new SortType;
	pSortType->setType(SORT_OFFSET_LOWHIGH);
	pSortType->setText(LocalizationManager::get()->getTranslatedText("Sort_Offset_LowToHigh"));
	getSortTypes()->addEntry(pSortType);

	pSortType = new SortType;
	pSortType->setType(SORT_OFFSET_HIGHLOW);
	pSortType->setText(LocalizationManager::get()->getTranslatedText("Sort_Offset_HighToLow"));
	getSortTypes()->addEntry(pSortType);

	pSortType = new SortType;
	pSortType->setType(SORT_SIZE_SMALLBIG);
	pSortType->setText(LocalizationManager::get()->getTranslatedText("Sort_Size_SmallToBig"));
	getSortTypes()->addEntry(pSortType);

	pSortType = new SortType;
	pSortType->setType(SORT_SIZE_BIGSMALL);
	pSortType->setText(LocalizationManager::get()->getTranslatedText("Sort_Size_BigToSmall"));
	getSortTypes()->addEntry(pSortType);

	pSortType = new SortType;
	pSortType->setType(SORT_IDE_FILE);
	pSortType->setText(LocalizationManager::get()->getTranslatedText("Sort_IDE"));
	getSortTypes()->addEntry(pSortType);

	pSortType = new SortType;
	pSortType->setType(SORT_COL_FILE);
	pSortType->setText(LocalizationManager::get()->getTranslatedText("Sort_COL"));
	getSortTypes()->addEntry(pSortType);

	pSortType = new SortType;
	pSortType->setType(SORT_FILE_EXTENSIONS);
	pSortType->setText(LocalizationManager::get()->getTranslatedText("Sort_Extensions"));
	getSortTypes()->addEntry(pSortType);
}
void		SortManager::uninitSortTypes(void)
{
	getSortTypes()->removeAllEntries();
}

void		SortManager::initSortPriorities(void)
{
	for (uint32 i = 0; i < 10; i++)
	{
		getSortPriorities()->addEntry(new SortPriority);
	}
}
void		SortManager::uninitSortPriorities(void)
{
	getSortPriorities()->removeAllEntries();
}

void		SortManager::sort(IMGFormat *pIMGFile)
{
	m_uiSortPriorityIndex = 0;
	std::sort(pIMGFile->getEntries().begin(), pIMGFile->getEntries().end(), SortManager::sortIMGEntries);
}

bool		SortManager::sortIMGEntries(IMGEntry *p1, IMGEntry *p2)
{
	SortManager *pSortManager = getIMGF()->getSortManager();
	SortPriority *pSortPriority = pSortManager->getSortPriorities()->getEntryByIndex((uint16)pSortManager->m_uiSortPriorityIndex);
	if (!pSortPriority->isEnabled())
	{
		//Debugger::log("not enabled: " + String::toString((uint16)pSortManager->m_uiSortPriorityIndex));
		return false;
	}
	ESortType ESortType = pSortPriority->getType()->getType();
	if (ESortType == SORT_NAME_AZ)
	{
		if (String::toUpperCase(p1->getEntryName()) == String::toUpperCase(p2->getEntryName()))
		{
			pSortManager->m_uiSortPriorityIndex++;
			bool bResult = sortIMGEntries(p1, p2);
			pSortManager->m_uiSortPriorityIndex--;
			return bResult;
		}
		else if (String::toUpperCase(p1->getEntryName()) < String::toUpperCase(p2->getEntryName()))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (ESortType == SORT_NAME_ZA)
	{
		if (String::toUpperCase(p1->getEntryName()) == String::toUpperCase(p2->getEntryName()))
		{
			pSortManager->m_uiSortPriorityIndex++;
			bool bResult = sortIMGEntries(p1, p2);
			pSortManager->m_uiSortPriorityIndex--;
			return bResult;
		}
		else if (String::toUpperCase(p1->getEntryName()) > String::toUpperCase(p2->getEntryName()))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (ESortType == SORT_OFFSET_LOWHIGH)
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
	else if (ESortType == SORT_OFFSET_HIGHLOW)
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
	else if (ESortType == SORT_SIZE_SMALLBIG)
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
	else if (ESortType == SORT_SIZE_BIGSMALL)
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
	else if (ESortType == SORT_IDE_FILE)
	{
		uint32 uiKey1 = StdVector::findKey(pSortPriority->getData(), String::toUpperCase(Path::removeFileExtension(p1->getEntryName())));
		uint32 uiKey2 = StdVector::findKey(pSortPriority->getData(), String::toUpperCase(Path::removeFileExtension(p2->getEntryName())));
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
	else if (ESortType == SORT_COL_FILE)
	{
		uint32 uiKey1 = StdVector::findKey(pSortPriority->getData(), String::toUpperCase(Path::removeFileExtension(p1->getEntryName())));
		uint32 uiKey2 = StdVector::findKey(pSortPriority->getData(), String::toUpperCase(Path::removeFileExtension(p2->getEntryName())));
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
	else if (ESortType == SORT_FILE_EXTENSIONS)
	{
		uint32 uiKey1 = StdVector::findKey(pSortPriority->getData(), String::toUpperCase(p1->getEntryName()));
		uint32 uiKey2 = StdVector::findKey(pSortPriority->getData(), String::toUpperCase(p2->getEntryName()));
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

void		SortManager::setMenuPriorityTypesUnchecked(SortPriority *pSortPriority)
{
	for (auto pSortMenuItem : getSortMenuItems()->getEntries())
	{
		if (pSortMenuItem->m_pPriority == pSortPriority)
		{
			// todo CheckMenuItem(getIMGF()->m_hMenu_Entry_Sort, pSortMenuItem->m_uiMenuHandle, MF_UNCHECKED);
		}
	}
}
void		SortManager::setMenuPriorityTypeChecked(SortPriority *pSortPriority, SortType *pSortType, bool bState)
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

bool		SortManager::isMenuHandleUsed(uint16 usMenuHandle)
{
	return getSortMenuItems()->getEntryByMenuHandle(usMenuHandle) != nullptr;
}
void		SortManager::onClickMenuItem(uint16 usMenuHandle)
{
	bool bCancel = false;
	bool bCurrentState = false; // todo (GetMenuState(getIMGF()->m_hMenu_Entry_Sort, usMenuHandle, 0) & MF_CHECKED) == MF_CHECKED;
	SortMenuItem *pSortMenuItem = getSortMenuItems()->getEntryByMenuHandle(usMenuHandle);
	SortPriority *pSortPriority = pSortMenuItem->m_pPriority;

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

		// todo Menu *pSortMenu = nullptr; // todo Menu::FromHandle(getIMGF()->m_hMenu_Entry_Sort);

		if (pSortMenuItem->m_pType->getType() == SORT_IDE_FILE)
		{
			vector<string> vecPaths = Input::openFile(getIMGF()->getLastUsedDirectory("SORT_IDE"), "IDE", false);
			if (vecPaths.size() == 0)
			{
				bCancel = true;
			}
			else
			{
				getIMGF()->setLastUsedDirectory("SORT_IDE", Path::getDirectory(vecPaths[0]));

				IDEFormat *pIDEFile = IDEManager::get()->parseViaFile(vecPaths[0]);
				if(!pIDEFile->doesHaveError())
				{
					vector<string> vecModelNames = pIDEFile->getModelNames();
					vector<string> vecTextureNames = pIDEFile->getTXDNames();
					vector<string> vecEntryNames = StdVector::toUpperCase(StdVector::combineVectors(vecModelNames, vecTextureNames));
					pSortPriority->setData(vecEntryNames);
					pSortPriority->setStrData(Path::getFileName(pIDEFile->getFilePath()));

					// todo pSortMenu->ModifyMenuW(usMenuHandle, 0, usMenuHandle, LocalizationManager::get()->getTranslatedFormattedTextW("Sort_ByText_WithFilename", pSortMenuItem->m_pType->getTextForMenu().c_str(), Path::getFileName(pIDEFile->getFilePath()).c_str()).c_str());
				}
				pIDEFile->unload();
				delete pIDEFile;
			}
		}
		else if (pSortMenuItem->m_pType->getType() == SORT_COL_FILE)
		{
			vector<string> vecPaths = Input::openFile(getIMGF()->getLastUsedDirectory("SORT_COL"), "COL", false);
			if (vecPaths.size() == 0)
			{
				bCancel = true;
			}
			else
			{
				getIMGF()->setLastUsedDirectory("SORT_COL", Path::getDirectory(vecPaths[0]));

				COLFormat *pCOLFile = COLManager::get()->parseViaFile(vecPaths[0]);
				if(!pCOLFile->doesHaveError())
				{
					vector<string> vecEntryNames = StdVector::toUpperCase(pCOLFile->getModelNames());
					pSortPriority->setData(vecEntryNames);
					pSortPriority->setStrData(Path::getFileName(pCOLFile->getFilePath()));

					// todo pSortMenu->ModifyMenuW(usMenuHandle, 0, usMenuHandle, LocalizationManager::get()->getTranslatedFormattedTextW("Sort_ByText_WithFilename", pSortMenuItem->m_pType->getTextForMenu().c_str(), Path::getFileName(pCOLFile->getFilePath()).c_str()).c_str());
				}
				pCOLFile->unload();
				delete pCOLFile;
			}
		}
		else if (pSortMenuItem->m_pType->getType() == SORT_FILE_EXTENSIONS)
		{
			string strText = ""; // todo - getIMGF()->getPopupGUIManager()->showTextInputDialog(LocalizationManager::get()->getTranslatedFormattedText("Sort_ByText", LocalizationManager::get()->getTranslatedTextW("Sort_Extensions").c_str()), LocalizationManager::get()->getTranslatedText("Window_TextInput_4_Message"));
			if (strText == "")
			{
				bCancel = true;
			}
			else
			{
				vector<string> vecFileExtensions = String::split(strText, ",");
				for (uint32 i = 0; i < vecFileExtensions.size(); i++)
				{
					vecFileExtensions[i] = String::toUpperCase(String::trim(vecFileExtensions[i]));
					if (vecFileExtensions[i].c_str()[0] == '.')
					{
						vecFileExtensions[i] = vecFileExtensions[i].substr(1);
					}
				}
				pSortPriority->setData(vecFileExtensions);
				pSortPriority->setStrData(String::join(vecFileExtensions, ", "));
				// todo pSortMenu->ModifyMenuW(usMenuHandle, 0, usMenuHandle, LocalizationManager::get()->getTranslatedFormattedTextW("Sort_ByText_WithFilename", pSortMenuItem->m_pType->getTextForMenu().c_str(), String::join(vecFileExtensions, ", ").c_str()).c_str());
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