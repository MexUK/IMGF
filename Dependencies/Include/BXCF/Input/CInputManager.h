#ifndef CBXCF_CInputManager_H
#define CBXCF_CInputManager_H

#include <Windows.h>
#include "bxcf.h"
#include "Type/Types.h"
#include <string>
#include <vector>

class bxcf::CInputManager
{
public:
	static void								setParentWindowHwnd(HWND hParentWindowHwnd) { CInputManager::m_hParentWindowHwnd = hParentWindowHwnd; }
	static HWND								getParentWindowHwnd(void) { return CInputManager::m_hParentWindowHwnd; }

	static std::vector<std::string>			openFile(std::string strInitialDir = "", std::string strExtensionFilters = "", bool bAllowMultiSelect = true, std::string strDefaultFileName = "");
	static std::vector<std::string>			openFile(uint32 uiInitialDirectoryId, std::string strExtensionFilters = "", bool bAllowMultiSelect = true, std::string strDefaultFileName = "");
	static std::string						saveFileDialog(std::string strInitialDir = "", std::string strExtensionFilters = "", std::string strDefaultFileName = "");
	static std::string						chooseFolderDialog(std::string strTitle, std::string strInitialDir = "");
	static std::string						chooseFolderDialog(HWND hOwnerHwnd, std::string strTitle, std::string strInitialDir = "");
	static int CALLBACK						onChooseFolderDialogInit(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);

	static std::string						getInitialDirectory(uint32 uiDirectory);

	static void								setDirectoryForId(uint32 uiDirectory, std::string& strDirectoryPath);
	static std::string						getDirectoryFromId(uint32 uiDirectory);

	static uint32							showMessage(std::string strMessage, std::string strTitle, uint32 uiButtonType = MB_OKCANCEL);

	static void								setMenuText(HMENU hMenu, uint32 uiControlIndex, std::string strText);
	static std::string						getEditText(uint32 uiControlIndex);

	static bool								isControlKeyDown(void);
	static bool								isShiftKeyDown(void);
	static bool								isAltKeyDown(void);
	static bool								isCapsLockOn(void);
	static bool								isTextInputUppercase(void);
	static std::string						getTextInInputCase(std::string& strText);

	static HWND								m_hParentWindowHwnd;
};

#endif