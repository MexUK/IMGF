#ifndef CMCore_CGUIManager_H
#define CMCore_CGUIManager_H

#include <Windows.h>
#include "mcore.h"
#include "Type/Types.h"
#include <string>
#include <vector>

class mcore::CGUIManager
{
public:
	static void								setParentWindowHwnd(HWND hParentWindowHwnd) { CGUIManager::m_hParentWindowHwnd = hParentWindowHwnd; }
	static HWND								getParentWindowHwnd(void) { return CGUIManager::m_hParentWindowHwnd; }

	static std::vector<std::string>			openFileDialog(std::string strInitialDir = "", std::string strExtensionFilters = "", bool bAllowMultiSelect = true, std::string strDefaultFileName = "");
	static std::string						saveFileDialog(std::string strInitialDir = "", std::string strExtensionFilters = "", std::string strDefaultFileName = "");
	static std::string						chooseFolderDialog(std::string strTitle, std::string strInitialDir = "");
	static std::string						chooseFolderDialog(HWND hOwnerHwnd, std::string strTitle, std::string strInitialDir = "");
	static int CALLBACK						onChooseFolderDialogInit(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);
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