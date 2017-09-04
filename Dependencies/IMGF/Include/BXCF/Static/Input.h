#pragma once

#include <Windows.h>
#include "nsbxcf.h"
#include "Type/Types.h"
#include <string>
#include <vector>

class bxcf::Input
{
public:
	static void								setParentWindowHwnd(HWND hParentWindowHwnd) { m_hParentWindowHwnd = hParentWindowHwnd; }
	static HWND								getParentWindowHwnd(void) { return m_hParentWindowHwnd; }

	static std::vector<std::string>			openFile(std::string strInitialDirKey = "", std::string strExtensionFilters = "", bool bAllowMultiSelect = true, std::string strDefaultFileName = "");
	static std::string						saveFileDialog(std::string strInitialDir = "", std::string strExtensionFilters = "", std::string strDefaultFileName = "");
	static std::string						chooseFolderDialog(std::string strTitle, std::string strInitialDir = "");
	static std::string						chooseFolderDialog(HWND hOwnerHwnd, std::string strTitle, std::string strInitialDir = "");
	static int CALLBACK						onChooseFolderDialogInit(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);

	static uint32							showMessage(std::string strMessage, std::string strTitle, uint32 uiButtonType = MB_OKCANCEL);

	static bool								isControlKeyDown(void);
	static bool								isShiftKeyDown(void);
	static bool								isAltKeyDown(void);
	static bool								isCapsLockOn(void);
	static bool								isTextInputUppercase(void);
	static std::string						getTextInInputCase(std::string& strText);
	
	static void								setMenuText(HMENU hMenu, uint32 uiControlIndex, std::string strText); // todo - remove
	static std::string						getEditText(uint32 uiControlIndex); // todo - remove

private:
	static HWND								m_hParentWindowHwnd;
};