#include "CTextureViewer.h"
#include "Globals.h"
#include "CIMGF.h"
#include "Format/RenderWare/Helper/BinaryStream/Sections/CRWSection_TextureNative.h"
#include "CEntryViewerManager.h"
#include "Format/RockstarGames/IMG/CIMGEntry.h"
#include "Format/RockstarGames/TXD/CTXDManager.h"
#include "Format/RockstarGames/TXD/CTXDFormat.h"
#include "Format/RockstarGames/WTD/CWTDManager.h"
#include "Format/RockstarGames/WTD/CWTDFormat.h"
#include "Format/RockstarGames/WTD/CWTDEntry.h"
#include "CTextureViewerTextureData.h"
#include "Image/CImageManager.h"
#include "Localization/CLocalizationManager.h"
#include "GUI/CGUIManager.h"
#include "Type/String/CString2.h"
#include <gdiplus.h>

using namespace std;
using namespace Gdiplus;
using namespace mcore;

static bool bPremultipledAlphaApplied = false;
uint32 uiEntryViewerWindowWidth = 800;
uint32 uiEntryViewerWindowHeight = 722;
static int yMinScroll;       // minimum vertical scroll value 
static int yMaxScroll;       // maximum vertical scroll value
static int yCurrentScroll;   // current vertical scroll value 
static HDC hdcScreen;        // DC for entire screen 
static HDC hdcScreenCompat;  // memory DC for screen 
static BOOL fBlt;            // TRUE if BitBlt occurred 
static BOOL fScroll;         // TRUE if scrolling occurred 
static BOOL fSize;           // TRUE if fBlt & WM_SIZE 
static int uiSingleDisplayTypeTopScrollbarXCurrentScroll;
HWND hWndComboBox;
uint32 uiZoomLevels[20] = { 25, 50, 75, 100, 125, 150, 175, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 2000, 3000, 4000, 5000 };
uint32 g_uiLeftPanelWidth = 250;

inline void PremultiplyBitmapAlpha(HDC hDC, HBITMAP hBmp)
{
	BITMAP bm = { 0 };
	GetObject(hBmp, sizeof(bm), &bm);
	BITMAPINFO* bmi = (BITMAPINFO*)_alloca(sizeof(BITMAPINFOHEADER) + (256 * sizeof(RGBQUAD)));
	::ZeroMemory(bmi, sizeof(BITMAPINFOHEADER) + (256 * sizeof(RGBQUAD)));
	bmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	BOOL bRes = ::GetDIBits(hDC, hBmp, 0, bm.bmHeight, NULL, bmi, DIB_RGB_COLORS);
	if (!bRes || bmi->bmiHeader.biBitCount != 32) return;
	LPBYTE pBitData = (LPBYTE) ::LocalAlloc(LPTR, bm.bmWidth * bm.bmHeight * sizeof(DWORD));
	if (pBitData == NULL) return;
	LPBYTE pData = pBitData;
	::GetDIBits(hDC, hBmp, 0, bm.bmHeight, pData, bmi, DIB_RGB_COLORS);
	for (int y = 0; y < bm.bmHeight; y++) {
		for (int x = 0; x < bm.bmWidth; x++) {
			pData[0] = (BYTE)((DWORD)pData[0] * pData[3] / 255);
			pData[1] = (BYTE)((DWORD)pData[1] * pData[3] / 255);
			pData[2] = (BYTE)((DWORD)pData[2] * pData[3] / 255);
			pData += 4;
		}
	}
	::SetDIBits(hDC, hBmp, 0, bm.bmHeight, pBitData, bmi, DIB_RGB_COLORS);
	::LocalFree(pBitData);
}

CTextureViewer::CTextureViewer(void) :
	m_pActiveEntry(nullptr),
	m_bTexturePreviewIsEnabled(false),
	m_eEntryViewerDisplayType(DISPLAYTYPE_SINGLE)
{
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);
}

void				CTextureViewer::reset(void)
{
	removeAllEntries();
	setEntityDataIsCorrupt(false);
	setRenderDataIsReady(false);
}

void				CTextureViewer::loadThreadAndWindow(void)
{
	setWindowIsOpen(true);

	uint32 uiThreadId;
	HANDLE hThread = CreateThread(NULL, 0, &onThreadStarted, this, 0, &uiThreadId);
	setThread(hThread);

	openWindow();
	applyWindowTitle();
}
void				CTextureViewer::unloadThreadAndWindow(void)
{
	removeAllEntries();
	setTexturePreviewEnabled(false);
	CEntryViewer::reset();
	setWindowIsOpen(false);
	//GdiplusShutdown(m_gdiplusToken);
}

void				CTextureViewer::applyWindowTitle(void)
{
	SetWindowText(getWindowHwnd(), CString2::convertStdStringToStdWString(getWindowTitle()).c_str());
}

DWORD WINAPI		CTextureViewer::onThreadStarted(LPVOID lpParam)
{
	CTextureViewer *pTextureViewer = (CTextureViewer*)lpParam;
	for(;;)
	{
		if (pTextureViewer->isWindowOpen())
		{
			pTextureViewer->processWindow();
		}
	}

	/*
	CTextureViewer *pTextureViewer = (CTextureViewer*)lpParam;
	pTextureViewer->reset();
	bool bNotCorrupt = false;
	if (pTextureViewer->getIMGEntry()->isCOLFile())
	{
		CCOLFormat *pCOLFile = CCOLManager::getInstance()->parseViaMemory(pEntryViewerManager->getIMGEntry()->getEntryData());
		//delete pCOLFile;
		if (pCOLFile->doesHaveError())
		{
			bNotCorrupt = false;
		}
		else
		{
			pEntryViewerManager->getCollisionViewer()->setCOLFile(pCOLFile);
			pEntryViewerManager->getCollisionViewer()->setCOLFileName(pEntryViewerManager->getIMGEntry()->getEntryName());
			pEntryViewerManager->getCollisionViewer()->prepareRenderData();
			bNotCorrupt = true;
		}
		return 0;
	}
	else
	{
		pTextureViewer->prepareRenderData();
	}
	if (bNotCorrupt)
	{
		pEntryViewerManager->openWindow();
		pEntryViewerManager->updateWindowTitle();
		pEntryViewerManager->processWindow();
	}
	else
	{
		pEntryViewerManager->setWindowOpen(false);
		TerminateThread(pEntryViewerManager->getEntryViewerThread(), 0);
	}
	*/
	return 0;
}

void				CTextureViewer::processWindow(void)
{
	MSG Msg;
	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
}

void				CTextureViewer::prepareRenderData(void)
{
	bPremultipledAlphaApplied = false;
	if (getIMGEntry()->isTXDFile())
	{
		prepareRenderData_TXD();
	}
	else if (getIMGEntry()->isWTDFile())
	{
		prepareRenderData_WTD();
	}
	else
	{
		setEntityDataIsCorrupt(true);
	}
}

void				CTextureViewer::prepareRenderData_TXD(void)
{
	CTXDFormat *pTXDFile = CTXDManager::getInstance()->parseViaMemory(getIMGEntry()->getEntryData());
	if (pTXDFile->doesHaveError())
	{
		//string a = pTXDFile->getCorruptReason();
		setEntityDataIsCorrupt(true);
		return;
	}

	vector<CRWSection_TextureNative*> vecTextures = pTXDFile->getTextures();
	uint32 uiTextureIndex = 0;
	for (auto pTexture : vecTextures)
	{
		CTextureViewerTextureData *pTextureData = new CTextureViewerTextureData;

		if (pTexture->getEntryCount() == 0)
		{
			// the texture does not have a mipmap
			pTextureData->m_uiIndex = uiTextureIndex;
			pTextureData->m_bTextureContainsNoMipmaps = true;
		}
		else
		{
			CRWEntry_TextureNative_MipMap *pMipmap = pTexture->getMipMaps().getEntryByIndex(0);
			string strBMPImageDataStr = pMipmap->getRasterDataBGRA32();
			const char *pBmpImageData = strBMPImageDataStr.c_str();

			HBITMAP hBitmap = CreateBitmap(pMipmap->getImageSize().m_x, pMipmap->getImageSize().m_y, 1, 32, pBmpImageData);

			//HDC memDC = CreateCompatibleDC(NULL);
			//HBITMAP hBitmap = CreateCompatibleBitmap(NULL, pMipmap->getImageSize(true), pMipmap->getImageSize(false));

			//tagBITMAPFILEHEADER bfh = *(tagBITMAPFILEHEADER*)pBuffer;
			//tagBITMAPINFOHEADER bih = *(tagBITMAPINFOHEADER*)(pBuffer + sizeof(tagBITMAPFILEHEADER));
			//RGBQUAD             rgb = *(RGBQUAD*)(pBuffer + sizeof(tagBITMAPFILEHEADER) + sizeof(tagBITMAPINFOHEADER));

			/*
			HWND hwnd = getWindowHwnd();
			HDC hdc = GetDC(hwnd);
			HDC MemDC = CreateCompatibleDC(hdc);
			HBITMAP hBitmap = CreateCompatibleBitmap(hdc, pMipmap->getImageSize(true), pMipmap->getImageSize(false));
			SelectObject(MemDC, hBitmap);
			BitBlt(hdc, 0, 0, pMipmap->getImageSize(true), pMipmap->getImageSize(false), MemDC, 0, 0, SRCCOPY); //Screen turns black
			//DeleteObject(hBit);
			//ReleaseDC(HWND_DESKTOP, hdc);
			//ReleaseDC(NULL, MemDC);
			//DeleteDC(MemDC);
			//DeleteDC(hdc);
			*/

			

			/*
			BITMAPINFOHEADER bmih;
			bmih.biSize = sizeof(BITMAPINFOHEADER);
			bmih.biWidth = pMipmap->getImageSize(true);
			bmih.biHeight = -((signed int)pMipmap->getImageSize(false)); // top-down
			bmih.biPlanes = 1;
			bmih.biBitCount = 32;
			bmih.biCompression = BI_RGB;
			bmih.biSizeImage = 0;
			bmih.biXPelsPerMeter = 10;
			bmih.biYPelsPerMeter = 10;
			bmih.biClrUsed = 0;
			bmih.biClrImportant = 0;

			BITMAPINFO bmi;
			memset(&bmi, 0, sizeof(BITMAPINFO));
			bmi.bmiHeader = bmih;
			bmi.bmiColors->rgbBlue = 0;
			bmi.bmiColors->rgbGreen = 0;
			bmi.bmiColors->rgbRed = 0;
			bmi.bmiColors->rgbReserved = 0;

			HWND hwnd = getWindowHwnd();
			HDC hdc = GetDC(hwnd);

			HBITMAP hBitmap = CreateDIBitmap(hdc, &bmih, CBM_INIT, pBmpImageData, &bmi, DIB_RGB_COLORS);
			if (hBitmap == NULL)
			{
				int a;
				a = 5;
			}
			*/

			//HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (void**)&pBmpImageData, NULL, 0);
			//SetDIBits(hdc, hBitmap, 0, bmi.bmiHeader.biHeight, pBmpImageData, &bmi, DIB_RGB_COLORS);
			//*/

			//HBITMAP hBitmap2;
			//GetObject(hBitmap, sizeof(BITMAP), &hBitmap2);

			/*
			HDC hDC = GetDC(NULL);
			HDC hdc2 = CreateCompatibleDC(hDC);

			BITMAPINFO bmi;
			memset(&bmi, 0, sizeof(BITMAPINFO));
			bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			bmi.bmiHeader.biWidth = pMipmap->getImageSize(true);
			bmi.bmiHeader.biHeight = -((signed int)pMipmap->getImageSize(false)); // top-down
			bmi.bmiHeader.biPlanes = 1;
			bmi.bmiHeader.biBitCount = 32;
			bmi.bmiHeader.biCompression = BI_RGB;
			HBITMAP hBitmap2 = CreateDIBSection(hDC, &bmi, DIB_RGB_COLORS, (void**)&pBmpImageData, NULL, NULL);
			SelectObject(hdc2, hBitmap2);
			HBITMAP hBitmap = CreateCompatibleBitmap(hdc2, pMipmap->getImageSize(true), pMipmap->getImageSize(false));
			ReleaseDC(NULL, hDC);
			*/


			pTextureData->m_uiIndex = uiTextureIndex;
			pTextureData->m_hBitmap = hBitmap;
			pTextureData->m_uiWidth = pTexture->getImageSize().m_x;
			pTextureData->m_uiHeight = pTexture->getImageSize().m_y;
			pTextureData->m_strDiffuseName = pTexture->getDiffuseName();
			pTextureData->m_strAlphaName = pTexture->getAlphaName();
			pTextureData->m_ucBPP = pTexture->getOriginalBPP() == 0 ? pTexture->getBPP() : pTexture->getOriginalBPP();
			pTextureData->m_strTextureFormat = CTXDManager::getTXDRasterFormatText(pTexture->getTXDRasterDataFormat(), pTexture->getDXTCompressionType());
		}

		addEntry(pTextureData);
		uiTextureIndex++;
	}

	if (getEntryCount() > 0)
	{
		setActiveEntry(getEntryByIndex(0));
	}

	pTXDFile->unload();
	delete pTXDFile;

	//uint32 uiImagePaddingBottom = 10;
	//uint32 uiTotalHeight = (m_vecEntryViewerImagesData.size() * (128 + 20 + 20 + uiImagePaddingBottom)) + 50;
	//setMaxYPosition(uiTotalHeight);

	setRenderDataIsReady(true);
}

void				CTextureViewer::prepareRenderData_WTD(void)
{
	CWTDFormat *pWTDFile = CWTDManager::getInstance()->parseViaMemory(getIMGEntry()->getEntryData());
	if (pWTDFile->doesHaveError())
	{
		setEntityDataIsCorrupt(true);
		return;
	}

	uint32 uiTextureIndex = 0;
	vector<CWTDEntry*> vecWTDEntries = pWTDFile->getEntries();

	for (auto pWTDEntry : vecWTDEntries)
	{
		CTextureViewerTextureData *pTextureData = new CTextureViewerTextureData;

		if (pWTDEntry->getEntryCount() == 0)
		{
			// the texture does not have a mipmap
			pTextureData->m_uiIndex = uiTextureIndex;
			pTextureData->m_bTextureContainsNoMipmaps = true;
		}
		else
		{
			CWTDMipmap *pMipmap = pWTDEntry->getEntryByIndex(0);
			string strBMPImageDataStr = pMipmap->getRasterDataBGRA32();
			const char *pBmpImageData = strBMPImageDataStr.c_str();

			HBITMAP hBitmap = CreateBitmap(pWTDEntry->getImageSize(true), pWTDEntry->getImageSize(false), 1, 32, pBmpImageData);

			/*
			BITMAPINFOHEADER bmih;
			bmih.biSize = sizeof(BITMAPINFOHEADER);
			bmih.biWidth = pMipmap->getImageSize(true);
			bmih.biHeight = -((signed int)pMipmap->getImageSize(false)); // top-down
			bmih.biPlanes = 1;
			bmih.biBitCount = 32;
			bmih.biCompression = BI_RGB;
			bmih.biSizeImage = 0;
			bmih.biXPelsPerMeter = 10;
			bmih.biYPelsPerMeter = 10;
			bmih.biClrUsed = 0;
			bmih.biClrImportant = 0;

			BITMAPINFO bmi;
			memset(&bmi, 0, sizeof(BITMAPINFO));
			bmi.bmiHeader = bmih;
			bmi.bmiColors->rgbBlue = 0;
			bmi.bmiColors->rgbGreen = 0;
			bmi.bmiColors->rgbRed = 0;
			bmi.bmiColors->rgbReserved = 0;

			HWND hwnd = getWindowHwnd();
			HDC hdc = GetDC(hwnd);

			HBITMAP hBitmap = CreateDIBitmap(hdc, &bmih, CBM_INIT, pBmpImageData, &bmi, DIB_RGB_COLORS);
			*/

			pTextureData->m_uiIndex = uiTextureIndex;
			pTextureData->m_hBitmap = hBitmap;
			pTextureData->m_uiWidth = pWTDEntry->getImageSize(true);
			pTextureData->m_uiHeight = pWTDEntry->getImageSize(false);
			pTextureData->m_strDiffuseName = pWTDEntry->getEntryName();
			pTextureData->m_strAlphaName = "";
			pTextureData->m_ucBPP = 32;
			pTextureData->m_strTextureFormat = CImageManager::getD3DFormatText(pWTDEntry->getD3DFormat());
		}

		addEntry(pTextureData);
		uiTextureIndex++;
	}

	if (getEntryCount() > 0)
	{
		setActiveEntry(getEntryByIndex(0));
	}

	pWTDFile->unload();
	delete pWTDFile;

	setRenderDataIsReady(true);
}


void				CTextureViewer::openWindow(void)
{
	// init settings
	setZoomLevel(1.0f);

	// calculate window position and size
	//RECT rect;
	//GetWindowRect(getIMGF()->getDialog()->GetSafeHwnd(), &rect);

	RECT screenRect;
	GetWindowRect(GetDesktopWindow(), &screenRect);

	uint32 uiEntryViewerWindowX = (screenRect.right / 2) - (uiEntryViewerWindowWidth / 2);
	uint32 uiEntryViewerWindowY = (screenRect.bottom / 2) - (uiEntryViewerWindowWidth / 2);

	// register the window
	WNDCLASSEX wc = { 0 };
	HWND hwndEntryViewerWindow;

	wchar_t *szClassName = L"IMGF_EntryViewer";
	HINSTANCE hInstance = GetModuleHandle(NULL);

	wc.cbSize = sizeof(wc);
	wc.style = 0;
	wc.lpfnWndProc = WndProc_EntryViewer;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	if (!RegisterClassEx(&wc))
	{
		DWORD uiError = GetLastError();
		mcore::CGUIManager::showMessage(CLocalizationManager::getInstance()->getTranslatedFormattedText("TextPopup_52", uiError), CLocalizationManager::getInstance()->getTranslatedText("TextPopup_Title52"), MB_OK);
		return;
	}

	// create the window
	hwndEntryViewerWindow = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		szClassName,
		CLocalizationManager::getInstance()->getTranslatedTextW("Window_EntryViewer_Title").c_str(),
		WS_OVERLAPPEDWINDOW | WS_VSCROLL,
		uiEntryViewerWindowX, uiEntryViewerWindowY, uiEntryViewerWindowWidth, uiEntryViewerWindowHeight,
		NULL, NULL, hInstance, NULL);
	if (hwndEntryViewerWindow == NULL)
	{
		mcore::CGUIManager::showMessage(CLocalizationManager::getInstance()->getTranslatedText("TextPopup_53"), CLocalizationManager::getInstance()->getTranslatedText("TextPopup_Title52"), MB_OK);
		return;
	}
	setWindowHwnd(hwndEntryViewerWindow);

	// initialize the window's vertical scrollbar
	// 1000 is just an initial value, the actual value is set in OnPaint()
	SCROLLINFO si;
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_RANGE;
	si.nMin = 0;
	si.nMax = 1000;
	SetScrollInfo(hwndEntryViewerWindow, SB_VERT, &si, true);
	setWindowScrollbarMaxRange(1000);

	// initialize the window's horizontal scrollbar for display type Single
	// 100 is just an initial value, the actual value is set in OnPaint()
	if (getDisplayType() == DISPLAYTYPE_SINGLE)
	{
		initDisplayType();
	}
	uiSingleDisplayTypeTopScrollbarXCurrentScroll = 0;
	setSingleDisplayTypeTopScrollbarMaxXPosition(100);

	// initialize menu
	HMENU hMenubar = CreateMenu();
	HMENU hMenu_View = CreateMenu();
	HMENU hMenu_View_DisplayType = CreateMenu();
	setViewMenu(hMenu_View);
	setDisplayTypeMenu(hMenu_View_DisplayType);

	AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hMenu_View, CLocalizationManager::getInstance()->getTranslatedTextW("EntryViewerMenu_View").c_str());
	AppendMenu(hMenu_View, MF_STRING | MF_POPUP, (UINT_PTR)hMenu_View_DisplayType, CLocalizationManager::getInstance()->getTranslatedTextW("EntryViewerMenu_DisplayType").c_str());
	AppendMenu(hMenu_View_DisplayType, MF_STRING, 1000, CLocalizationManager::getInstance()->getTranslatedTextW("EntryViewerMenu_DisplayType_Float").c_str());
	AppendMenu(hMenu_View_DisplayType, MF_STRING | MF_CHECKED, 1001, CLocalizationManager::getInstance()->getTranslatedTextW("EntryViewerMenu_DisplayType_Single").c_str());
	AppendMenu(hMenu_View, MF_STRING, 1020, CLocalizationManager::getInstance()->getTranslatedTextW("EntryViewerMenu_PreviewTextures").c_str());

	::SetMenu(hwndEntryViewerWindow, hMenubar);

	// show the window
	ShowWindow(hwndEntryViewerWindow, SW_RESTORE);
	UpdateWindow(hwndEntryViewerWindow);

	// restore focus to the main window (as the focus will be automatically changed to the entry viewer window)
	//SetForegroundWindow(getIMGF()->getDialog()->GetSafeHwnd());
}

void				CTextureViewer::closeWindow(void)
{
	setWindowIsOpen(false);
	DestroyWindow(getWindowHwnd());
	UnregisterClass(L"IMGF_EntryViewer", (HINSTANCE)GetModuleHandle(NULL));
	reset();
	TerminateThread(getThread(), 0);
}

void				CTextureViewer::repositionWindow(void)
{
	/*
	todo

	RECT rect;
	GetWindowRect(getIMGF()->getDialog()->GetSafeHwnd(), &rect);

	uint32 uiEntryViewerWindowX = rect.right + 1;
	uint32 uiEntryViewerWindowY = rect.top;

	SetWindowPos(getWindowHwnd(), HWND_TOP, uiEntryViewerWindowX, uiEntryViewerWindowY, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
	*/
}

/*
todo
LRESULT CALLBACK WndProc_ComboBox(
	HWND      hWnd,
	UINT      uMsg,
	WPARAM    wParam,
	LPARAM    lParam,
	UINT_PTR  uIdSubclass,
	DWORD_PTR dwRefData
)
{
	if (uMsg == WM_COMMAND)
	{
		int iCurSel = ((CComboBox*)CWnd::FromHandle(hWndComboBox))->GetCurSel();
		getIMGF()->getEntryViewerManager()->getTextureViewer()->setZoomLevel((float32)uiZoomLevels[iCurSel] / 100.0f);
		getIMGF()->getEntryViewerManager()->getTextureViewer()->forceRender();
	}

	return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}
*/

/*
WNDPROC prevWndProc;

LRESULT CALLBACK WndProc_ComboBox(
	HWND      hWnd,
	UINT      uMsg,
	WPARAM    wParam,
	LPARAM    lParam
	)
{
	if ((HWND)lParam == hWndComboBox)
	{
		mcore::CGUIManager::showMessage("T", "D");
	}
	if ((uMsg == WM_COMMAND) && (HIWORD(wParam) == BN_CLICKED))
	{
		if ((HWND)lParam == hWndComboBox)
		{
			int iCurSel = ((CComboBox*)CWnd::FromHandle(hWndComboBox))->GetCurSel();
			getIMGF()->getEntryViewerManager()->setZoomLevel((float32)uiZoomLevels[iCurSel] / 100.0f);
			getIMGF()->getEntryViewerManager()->redrawWindow();
		}
	}

	return CallWindowProc(prevWndProc, hWnd, uMsg, wParam, lParam);
}
*/

void				CTextureViewer::setDisplayType(eEntryViewerDisplayType eEntryViewerDisplayTypeValue)
{
	uninitDisplayType();
	m_eEntryViewerDisplayType = eEntryViewerDisplayTypeValue;
	initDisplayType();
}
void				CTextureViewer::initDisplayType(void)
{
	if (getDisplayType() == DISPLAYTYPE_SINGLE)
	{
		/*
		todo
		int xpos = g_uiLeftPanelWidth + 50; // Horizontal position of the window.
		int ypos = 7;            // Vertical position of the window.
		int nwidth = 200;          // Width of the window
		int nheight = 200;         // Height of the window
		HWND hwndParent = getWindowHwnd(); // Handle to the parent window

		hWndComboBox = CreateWindow(WC_COMBOBOX, TEXT(""),
			CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
			xpos, ypos, nwidth, nheight, hwndParent, NULL, GetModuleHandle(NULL),
			NULL);
		//prevWndProc = (WNDPROC)SetWindowLongPtr(hWndComboBox, GWLP_WNDPROC, (LONG_PTR)&WndProc_ComboBox);
		SetWindowSubclass(hWndComboBox, &WndProc_ComboBox, 0, 0);

		for (uint32 i = 0, j = 20; i < j; i++)
		{
			((CComboBox*)CWnd::FromHandle(hWndComboBox))->InsertString(i, CString2::convertStdStringToStdWString(CString2::toString(uiZoomLevels[i]) + "%").c_str());
		}
		((CComboBox*)CWnd::FromHandle(hWndComboBox))->SetCurSel(3);
		*/

		/*
		return;

		RECT horizontalScrollbarRect;
		if (false)
		{
		horizontalScrollbarRect.left = 0;
		horizontalScrollbarRect.top = 128 + 20 + 20 + 5;
		horizontalScrollbarRect.right = uiEntryViewerWindowWidth;
		horizontalScrollbarRect.bottom = uiEntryViewerWindowHeight;

		HWND hSingleDisplayType_TopHorizontalScrollbarHwnd = CreateWindowEx(
		0,                      // no extended styles
		L"SCROLLBAR",           // scroll bar control class
		(PTSTR)NULL,           // no window text
		WS_CHILD | WS_VISIBLE   // window styles
		| SBS_HORZ,         // horizontal scroll bar style
		horizontalScrollbarRect.left,              // horizontal position
		horizontalScrollbarRect.top, // vertical position
		uiEntryViewerWindowWidth - 37,             // width of the scroll bar
		16,               // height of the scroll bar
		getEntryViewerWindow(),             // handle to main window
		(HMENU)NULL,           // no menu
		GetModuleHandle(NULL),                // instance owning this window
		(PVOID)NULL            // pointer not needed
		);
		setSingleDisplayTypeTopScrollbarHwnd(hSingleDisplayType_TopHorizontalScrollbarHwnd);
		}
		else
		{
		horizontalScrollbarRect.left = 128;
		horizontalScrollbarRect.top = 0;
		horizontalScrollbarRect.right = 128+30;
		horizontalScrollbarRect.bottom = uiEntryViewerWindowHeight;

		HWND hSingleDisplayType_LeftVerticalScrollbarHwnd = CreateWindowEx(
		0,                      // no extended styles
		L"SCROLLBAR",           // scroll bar control class
		(PTSTR)NULL,           // no window text
		WS_CHILD | WS_VISIBLE   // window styles
		| SBS_VERT,         // horizontal scroll bar style
		horizontalScrollbarRect.left,              // horizontal position
		horizontalScrollbarRect.top, // vertical position
		16,             // width of the scroll bar
		uiEntryViewerWindowHeight - 37,               // height of the scroll bar
		getEntryViewerWindow(),             // handle to main window
		(HMENU)NULL,           // no menu
		GetModuleHandle(NULL),                // instance owning this window
		(PVOID)NULL            // pointer not needed
		);
		setSingleDisplayTypeTopScrollbarHwnd(hSingleDisplayType_LeftVerticalScrollbarHwnd);
		}
		*/
	}
}

void				CTextureViewer::uninitDisplayType(void)
{
	if (getDisplayType() == DISPLAYTYPE_SINGLE)
	{
		DestroyWindow(hWndComboBox);

		/*
		return;

		DestroyWindow(getSingleDisplayTypeTopScrollbarHwnd());
		*/
	}
}

LRESULT CALLBACK	WndProc_EntryViewer(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	CTextureViewer *pTextureViewer = getIMGF()->getEntryViewerManager()->getTextureViewer();

	// vertical scrollbar variables
	SCROLLINFO si;

	// single dfisplay type top horizontal scrollbar variables
	static int uiSingleDisplayTypeTopScrollbarXMinScroll;
	static int uiSingleDisplayTypeTopScrollbarXMaxScroll;

	// process message
	switch (msg)
	{
	case WM_CREATE:
		hdcScreen = CreateDC(L"DISPLAY", (PCTSTR)NULL,
			(PCTSTR)NULL, (CONST DEVMODE *) NULL);
		hdcScreenCompat = CreateCompatibleDC(hdcScreen);

		fBlt = FALSE;
		fScroll = FALSE;
		fSize = FALSE;

		break;
	case WM_CLOSE:
		if (pTextureViewer->isWindowOpen())
		{
			pTextureViewer->closeWindow();
		}
		break;
	case WM_DESTROY:
		if (pTextureViewer->isWindowOpen())
		{
			pTextureViewer->closeWindow();
		}
		break;
	case WM_LBUTTONDOWN:
	{
		CTextureViewerTextureData *pActiveImageData = nullptr;
		uint32 uiActiveImageIndex;
		uint32 i = 0;
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		y += yCurrentScroll;
		for (auto pImageData : pTextureViewer->getEntries())
		{
			if (x >= pImageData->m_rect.left
				&& y >= pImageData->m_rect.top
				&& x <= pImageData->m_rect.right
				&& y <= pImageData->m_rect.bottom)
			{
				uiActiveImageIndex = i;
				pActiveImageData = pImageData;
				break;
			}
			i++;
		}
		if (pActiveImageData != nullptr)
		{
			pTextureViewer->setActiveEntry(pActiveImageData);
			pTextureViewer->forceRender();
		}
		break;
	}
	case WM_MOUSEWHEEL:
	{
		int xDelta = 0;
		int yDelta;     // yDelta = new_pos - current_pos 
		int yNewPos;    // new position 

		int iDelta = GET_WHEEL_DELTA_WPARAM(wParam); // / WHEEL_DELTA;
		//yCurrentScroll += 0;
		yNewPos = yCurrentScroll - iDelta;

		// New position must be between 0 and the screen height. 
		yNewPos = max(0, yNewPos);
		yNewPos = min(yMaxScroll, yNewPos);

		// If the current position does not change, do not scroll.
		if (yNewPos == yCurrentScroll)
			break;

		// Set the scroll flag to TRUE. 
		fScroll = TRUE;

		// Determine the amount scrolled (in pixels). 
		yDelta = yNewPos - yCurrentScroll;

		// Reset the current scroll position. 
		yCurrentScroll = yNewPos;
		if (yCurrentScroll < 0)
		{
			yCurrentScroll = 0;
		}

		// Scroll the window. (The system repaints most of the 
		// client area when ScrollWindowEx is called; however, it is 
		// necessary to call UpdateWindow in order to repaint the 
		// rectangle of pixels that were invalidated.) 
		//ScrollWindowEx(hwnd, -xDelta, -yDelta, (CONST RECT *) NULL,
		//	(CONST RECT *) NULL, (HRGN)NULL, (PRECT)NULL,
		//	SW_INVALIDATE);
		//UpdateWindow(hwnd);
		pTextureViewer->forceRender();

		/*
		// Reset the scroll bar.
		si.cbSize = sizeof(si);
		si.fMask = SIF_POS;
		si.nPos = yCurrentScroll;
		SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
		*/
		RECT rect;
		GetClientRect(pTextureViewer->getWindowHwnd(), &rect);
		int yNewSize = rect.bottom;

		yMaxScroll = max(pTextureViewer->getWindowScrollbarMaxRange() - yNewSize, 0);
		yCurrentScroll = min(yCurrentScroll, yMaxScroll);
		if (yCurrentScroll < 0)
		{
			yCurrentScroll = 0;
		}
		si.cbSize = sizeof(si);
		si.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
		si.nMin = yMinScroll;
		si.nMax = pTextureViewer->getWindowScrollbarMaxRange();
		si.nPage = yNewSize;
		si.nPos = yCurrentScroll;
		SetScrollInfo(hwnd, SB_VERT, &si, TRUE);

		break;
	}
	case WM_SIZE:
	{
		/*
		todo
		if (pTextureViewer->isRenderDataReady())
		{
			CWnd *pWnd = CWnd::FromHandle(pTextureViewer->getWindowHwnd());
			pWnd->Invalidate(true);
			UpdateWindow(pTextureViewer->getWindowHwnd());
		}
		*/

		// apply scroll range
		int xNewSize = LOWORD(lParam);
		int yNewSize = HIWORD(lParam);

		if (fBlt)
			fSize = TRUE;

		// The vertical scrolling range is defined by 
		// (bitmap_height) - (client_height). The current vertical 
		// scroll value remains within the vertical scrolling range.
		yMaxScroll = max(pTextureViewer->getWindowScrollbarMaxRange() - yNewSize, 0);
		yCurrentScroll = min(yCurrentScroll, yMaxScroll);
		if (yCurrentScroll < 0)
		{
			yCurrentScroll = 0;
		}
		si.cbSize = sizeof(si);
		si.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
		si.nMin = yMinScroll;
		si.nMax = pTextureViewer->getWindowScrollbarMaxRange();
		si.nPage = yNewSize;
		si.nPos = yCurrentScroll;
		SetScrollInfo(hwnd, SB_VERT, &si, TRUE);

		// resize the horizontal scrollbar for display type Single
		RECT clientRect;
		GetClientRect(hwnd, &clientRect);
		if (false)
		{
			SetWindowPos(pTextureViewer->getSingleDisplayTypeTopScrollbarHwnd(), NULL, 0, 0, clientRect.right, 16, SWP_NOMOVE);
		}
		else
		{
			//SetWindowPos(getIMGF()->getEntryViewerManager()->getSingleDisplayTypeTopScrollbarHwnd(), NULL, 0, 0, 16, clientRect.bottom, SWP_NOMOVE);
		}

		//RECT clientRect2;
		//GetClientRect(getIMGF()->getEntryViewerManager()->getEntryViewerWindow(), &clientRect2);
		//InvalidateRect(getIMGF()->getEntryViewerManager()->getEntryViewerWindow(), &clientRect2, true);

		/*
		// set seek position of the horizontal scrollbar for display type Single
		SCROLLINFO si2;
		uiSingleDisplayTypeTopScrollbarXMaxScroll = max(getIMGF()->getEntryViewerManager()->getSingleDisplayTypeTopScrollbarMaxXPosition() - xNewSize, 0);
		uiSingleDisplayTypeTopScrollbarXCurrentScroll = min(uiSingleDisplayTypeTopScrollbarXCurrentScroll, uiSingleDisplayTypeTopScrollbarXMaxScroll);
		si2.cbSize = sizeof(si2);
		si2.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
		si2.nMin = uiSingleDisplayTypeTopScrollbarXMinScroll;
		si2.nMax = getIMGF()->getEntryViewerManager()->getSingleDisplayTypeTopScrollbarMaxXPosition();
		si2.nPage = xNewSize;
		si2.nPos = uiSingleDisplayTypeTopScrollbarXCurrentScroll;
		SetScrollInfo(getIMGF()->getEntryViewerManager()->getSingleDisplayTypeTopScrollbarHwnd(), SB_HORZ, &si2, TRUE);
		*/

		break;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 1000: // display type: Float
			pTextureViewer->setDisplayType(DISPLAYTYPE_FLOAT);
			CheckMenuItem(pTextureViewer->getDisplayTypeMenu(), 1000, MF_CHECKED);
			CheckMenuItem(pTextureViewer->getDisplayTypeMenu(), 1001, MF_UNCHECKED);
			pTextureViewer->forceRender();
			break;
		case 1001: // display type: Single
			pTextureViewer->setDisplayType(DISPLAYTYPE_SINGLE);
			CheckMenuItem(pTextureViewer->getDisplayTypeMenu(), 1000, MF_UNCHECKED);
			CheckMenuItem(pTextureViewer->getDisplayTypeMenu(), 1001, MF_CHECKED);
			pTextureViewer->forceRender();
			break;
		case 1020: // Preview Textures
			if (pTextureViewer->isTexturePreviewEnabled())
			{
				CheckMenuItem(pTextureViewer->getViewMenu(), 1020, MF_UNCHECKED);
				pTextureViewer->setTexturePreviewEnabled(false);
			}
			else
			{
				CheckMenuItem(pTextureViewer->getViewMenu(), 1020, MF_CHECKED);
				pTextureViewer->setTexturePreviewEnabled(true);
			}
			pTextureViewer->forceRender();
			break;
		}
		break;
	case WM_VSCROLL:
	{
		int xDelta = 0;
		int yDelta;     // yDelta = new_pos - current_pos 
		int yNewPos;    // new position 

		switch (LOWORD(wParam))
		{
			// User clicked the scroll bar shaft above the scroll box. 
		case SB_PAGEUP:
			yNewPos = yCurrentScroll - 50;
			break;

			// User clicked the scroll bar shaft below the scroll box. 
		case SB_PAGEDOWN:
			yNewPos = yCurrentScroll + 50;
			break;

			// User clicked the top arrow. 
		case SB_LINEUP:
			yNewPos = yCurrentScroll - 5;
			break;

			// User clicked the bottom arrow. 
		case SB_LINEDOWN:
			yNewPos = yCurrentScroll + 5;
			break;

			// User dragged the scroll box. 
		case SB_THUMBPOSITION:
			yNewPos = HIWORD(wParam);
			break;

		case SB_TOP:
			yNewPos = 0;
			break;

		case SB_BOTTOM:
			yNewPos = yMaxScroll;
			break;

		default:
			yNewPos = yCurrentScroll;
		}

		// New position must be between 0 and the screen height. 
		yNewPos = max(0, yNewPos);
		yNewPos = min(yMaxScroll, yNewPos);

		// If the current position does not change, do not scroll.
		if (yNewPos == yCurrentScroll)
			break;

		// Set the scroll flag to TRUE. 
		fScroll = TRUE;

		// Determine the amount scrolled (in pixels). 
		yDelta = yNewPos - yCurrentScroll;

		// Reset the current scroll position. 
		yCurrentScroll = yNewPos;
		if (yCurrentScroll < 0)
		{
			yCurrentScroll = 0;
		}

		// Scroll the window. (The system repaints most of the 
		// client area when ScrollWindowEx is called; however, it is 
		// necessary to call UpdateWindow in order to repaint the 
		// rectangle of pixels that were invalidated.) 
		//ScrollWindowEx(hwnd, -xDelta, -yDelta, (CONST RECT *) NULL,
		//	(CONST RECT *) NULL, (HRGN)NULL, (PRECT)NULL,
		//	SW_INVALIDATE);
		//UpdateWindow(hwnd);
		pTextureViewer->forceRender();

		/*
		// Reset the scroll bar.
		si.cbSize = sizeof(si);
		si.fMask = SIF_POS;
		si.nPos = yCurrentScroll;
		SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
		*/

		// The vertical scrolling range is defined by 
		// (bitmap_height) - (client_height). The current vertical 
		// scroll value remains within the vertical scrolling range.

		RECT rect;
		GetClientRect(pTextureViewer->getWindowHwnd(), &rect);
		int yNewSize = rect.bottom;

		yMaxScroll = max(pTextureViewer->getWindowScrollbarMaxRange() - yNewSize, 0);
		yCurrentScroll = min(yCurrentScroll, yMaxScroll);
		if (yCurrentScroll < 0)
		{
			yCurrentScroll = 0;
		}
		si.cbSize = sizeof(si);
		si.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
		si.nMin = yMinScroll;
		si.nMax = pTextureViewer->getWindowScrollbarMaxRange();
		si.nPage = yNewSize;
		si.nPos = yCurrentScroll;
		SetScrollInfo(hwnd, SB_VERT, &si, TRUE);

		break;
	}
	case WM_HSCROLL:
	{
		int xDelta; // xDelta = new_pos - current_pos 
		int yDelta = 0;
		int xNewPos;    // new position 

		switch (LOWORD(wParam))
		{
			// User clicked the scroll bar shaft above the scroll box. 
		case SB_PAGEUP:
			xNewPos = uiSingleDisplayTypeTopScrollbarXCurrentScroll - 50;
			break;

			// User clicked the scroll bar shaft below the scroll box. 
		case SB_PAGEDOWN:
			xNewPos = uiSingleDisplayTypeTopScrollbarXCurrentScroll + 50;
			break;

			// User clicked the top arrow. 
		case SB_LINEUP:
			xNewPos = uiSingleDisplayTypeTopScrollbarXCurrentScroll - 5;
			break;

			// User clicked the bottom arrow. 
		case SB_LINEDOWN:
			xNewPos = uiSingleDisplayTypeTopScrollbarXCurrentScroll + 5;
			break;

			// User dragged the scroll box. 
		case SB_THUMBPOSITION:
			xNewPos = HIWORD(wParam);
			break;

		case SB_TOP:
			xNewPos = 0;
			break;

		case SB_BOTTOM:
			xNewPos = uiSingleDisplayTypeTopScrollbarXMaxScroll;
			break;

		default:
			xNewPos = uiSingleDisplayTypeTopScrollbarXCurrentScroll;
		}

		// New position must be between 0 and the screen height. 
		xNewPos = max(0, xNewPos);
		xNewPos = min(uiSingleDisplayTypeTopScrollbarXMaxScroll, xNewPos);

		// If the current position does not change, do not scroll.
		if (xNewPos == uiSingleDisplayTypeTopScrollbarXCurrentScroll)
			break;

		// Set the scroll flag to TRUE. 
		fScroll = TRUE;

		// Determine the amount scrolled (in pixels). 
		xDelta = xNewPos - uiSingleDisplayTypeTopScrollbarXCurrentScroll;

		// Reset the current scroll position. 
		uiSingleDisplayTypeTopScrollbarXCurrentScroll = xNewPos;

		// Scroll the window. (The system repaints most of the 
		// client area when ScrollWindowEx is called; however, it is 
		// necessary to call UpdateWindow in order to repaint the 
		// rectangle of pixels that were invalidated.) 
		/*
		ScrollWindowEx(hwnd, -xDelta, -yDelta, (CONST RECT *) NULL,
		(CONST RECT *) NULL, (HRGN)NULL, (PRECT)NULL,
		SW_INVALIDATE);
		UpdateWindow(hwnd);
		*/

		// Reset the scroll bar. 
		si.cbSize = sizeof(si);
		si.fMask = SIF_POS;
		si.nPos = uiSingleDisplayTypeTopScrollbarXCurrentScroll;
		SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);

		break;
	}
	case WM_KEYDOWN:
	{
		WORD wScrollNotify = 0xFFFF;

		uint32 uiMinTextureIndex = 0;
		uint32 uiMaxTextureIndex = pTextureViewer->getEntryCount() - 1;
		int32 iNextTextureIndex;

		CTextureViewerTextureData *pTexData;

		switch (wParam)
		{
		case VK_PRIOR:
			iNextTextureIndex = pTextureViewer->getActiveEntry()->m_uiIndex - 5;
			if (iNextTextureIndex < 0)
			{
				iNextTextureIndex = 0;
			}
			pTexData = pTextureViewer->getEntryByIndex(iNextTextureIndex);
			pTextureViewer->setActiveEntry(pTexData);
			if (!pTexData->isCompletelyDisplayed())
			{
				yCurrentScroll -= ((pTexData->m_rect.bottom - pTexData->m_rect.top) + 1) * 5;
				if (yCurrentScroll < 0)
				{
					yCurrentScroll = 0;
				}
			}
			pTextureViewer->forceRender();
			break;

		case VK_NEXT:
			iNextTextureIndex = pTextureViewer->getActiveEntry()->m_uiIndex + 5;
			if (iNextTextureIndex > uiMaxTextureIndex)
			{
				iNextTextureIndex = uiMaxTextureIndex;
			}
			pTexData = pTextureViewer->getEntryByIndex(iNextTextureIndex);
			pTextureViewer->setActiveEntry(pTexData);
			if (!pTexData->isCompletelyDisplayed())
			{
				yCurrentScroll += ((pTexData->m_rect.bottom - pTexData->m_rect.top) + 1) * 5;
			}
			pTextureViewer->forceRender();
			return 0;
			break;

		case VK_UP:
			iNextTextureIndex = ((int32) pTextureViewer->getActiveEntry()->m_uiIndex) - 1;
			if (iNextTextureIndex >= 0)
			{
				pTexData = pTextureViewer->getEntryByIndex(iNextTextureIndex);
				pTextureViewer->setActiveEntry(pTexData);
				if (!pTexData->isCompletelyDisplayed())
				{
					yCurrentScroll -= (pTexData->m_rect.bottom - pTexData->m_rect.top) + 1;
					if (yCurrentScroll < 0)
					{
						yCurrentScroll = 0;
					}
				}
				pTextureViewer->forceRender();
			}
			break;

		case VK_DOWN:
			iNextTextureIndex = pTextureViewer->getActiveEntry()->m_uiIndex + 1;
			if (iNextTextureIndex <= uiMaxTextureIndex)
			{
				pTexData = pTextureViewer->getEntryByIndex(iNextTextureIndex);
				pTextureViewer->setActiveEntry(pTexData);
				if (!pTexData->isCompletelyDisplayed())
				{
					yCurrentScroll += (pTexData->m_rect.bottom - pTexData->m_rect.top) + 1;
				}
				pTextureViewer->forceRender();
			}
			break;

		case VK_HOME:
			if (pTextureViewer->getEntryCount() > 0)
			{
				pTextureViewer->setActiveEntry(pTextureViewer->getEntryByIndex(0));
				pTextureViewer->forceRender();
			}
			wScrollNotify = SB_TOP;
			break;

		case VK_END:
			if (pTextureViewer->getEntryCount() > 0)
			{
				pTextureViewer->setActiveEntry(pTextureViewer->getLastEntry());
				pTextureViewer->forceRender();
			}
			wScrollNotify = SB_BOTTOM;
			break;
		}

		if (wScrollNotify != -1)
			SendMessage(hwnd, WM_VSCROLL, MAKELONG(wScrollNotify, 0), 0L);

		break;
	}
	case WM_PAINT:
		onPaint(hwnd);
		break;
	case WM_ERASEBKGND:
		pTextureViewer->clearWindowBackground((HDC)wParam);
		return 1;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

void			CTextureViewer::forceRender(void)
{
	RECT rect;
	GetClientRect(getIMGF()->getEntryViewerManager()->getTextureViewer()->getWindowHwnd(), &rect);

	//CWnd *pWnd = CWnd::FromHandle(getIMGF()->getEntryViewerManager()->getEntryViewerWindow());
	//pWnd->Invalidate(true);
	//UpdateWindow(getIMGF()->getEntryViewerManager()->getEntryViewerWindow());
	RedrawWindow(getIMGF()->getEntryViewerManager()->getTextureViewer()->getWindowHwnd(), NULL, NULL, RDW_INVALIDATE | RDW_INTERNALPAINT);

	SendMessage(getIMGF()->getEntryViewerManager()->getTextureViewer()->getWindowHwnd(), WM_SIZE, 0L, 0L); // this function call is here to trigger redrawing and the scrollbar displaying

	int yNewSize = rect.bottom;

	yMaxScroll = max(getIMGF()->getEntryViewerManager()->getTextureViewer()->getWindowScrollbarMaxRange() - yNewSize, 0);
	yCurrentScroll = min(yCurrentScroll, yMaxScroll);
	if (yCurrentScroll < 0)
	{
		yCurrentScroll = 0;
	}
	SCROLLINFO si;
	si.cbSize = sizeof(si);
	si.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
	si.nMin = yMinScroll;
	si.nMax = getIMGF()->getEntryViewerManager()->getTextureViewer()->getWindowScrollbarMaxRange();
	si.nPage = yNewSize;
	si.nPos = yCurrentScroll;
	SetScrollInfo(getIMGF()->getEntryViewerManager()->getTextureViewer()->getWindowHwnd(), SB_VERT, &si, TRUE);
}

void				CTextureViewer::clearWindowBackground(HDC hdc)
{
	RECT clientRect;
	GetClientRect(getWindowHwnd(), &clientRect);

	if (getDisplayType() == DISPLAYTYPE_SINGLE)
	{
		//bkgBrush = CreateSolidBrush(RGB(223, 223, 223));

		/*
		ID2D1LinearGradientBrush *m_pLinearGradientBrush;

		// Create an array of gradient stops to put in the gradient stop
		// collection that will be used in the gradient brush.
		ID2D1GradientStopCollection *pGradientStops = NULL;

		D2D1_GRADIENT_STOP gradientStops[2];
		gradientStops[0].color = D2D1::ColorF(D2D1::ColorF::Yellow, 1);
		gradientStops[0].position = 0.0f;
		gradientStops[1].color = D2D1::ColorF(D2D1::ColorF::ForestGreen, 1);
		gradientStops[1].position = 1.0f;
		// Create the ID2D1GradientStopCollection from a previously
		// declared array of D2D1_GRADIENT_STOP structs.
		hr = m_pRenderTarget->CreateGradientStopCollection(
		gradientStops,
		2,
		D2D1_GAMMA_2_2,
		D2D1_EXTEND_MODE_CLAMP,
		&pGradientStops
		);

		hr = m_pRenderTarget->CreateLinearGradientBrush(
		D2D1::LinearGradientBrushProperties(
		D2D1::Point2F(0, 0),
		D2D1::Point2F(150, 150)),
		pGradientStops,
		&m_pLinearGradientBrush
		);
		*/

		/*
		Color *rgb1 = new Color(255, 0, 0);
		Color *rgb2 = new Color(0, 0, 0);
		Point *point1 = new Point(0.5, 0);
		Point *point2 = new Point(0.5, 1);
		*/

		/*
		Color rgb1(255, 0, 0);
		Color rgb2(255, 255, 0);
		Point point1(0.5, 0);
		Point point2(0.5, 1);
		Graphics gc(hdc);
		LinearGradientBrush *gradientBrush = new  LinearGradientBrush(point1, point2, rgb1, rgb2);
		Rect clientRect2;
		//ScreenToClient(getEntryViewerWindow(), clientRect);
		clientRect2.X = clientRect.left;
		clientRect2.Y = clientRect.top;
		clientRect2.Width = clientRect.right - clientRect.left;
		clientRect2.Height = 100;// clientRect.bottom - clientRect.top;
		gc.FillRectangle(gradientBrush, clientRect2);
		//bkgBrush = *gradientBrush;
		//gradientBrush->
		*/

		/*
		int r1 = 44, g1 = 73, b1 = 89; //Any start color
		int r2 = 36, g2 = 76, b2 = 122; //Any stop color
		*/
		int r1 = 223, g1 = 227, b1 = 236; //Any start color
		int r2 = 209, g2 = 214, b2 = 224; //Any stop color
		uint32 uiWidth = clientRect.right - clientRect.left;
		uint32 uiHeight = clientRect.bottom - clientRect.top;

		/*
		todo
		CDC *pDC = CDC::FromHandle(hdc);
		for (int i = 0; i<uiHeight; i++)
		{
			int r, g, b;
			r = r1 + (i * (float32)(r2 - r1) / uiHeight);
			g = g1 + (i * (float32)(g2 - g1) / uiHeight);
			b = b1 + (i * (float32)(b2 - b1) / uiHeight);
			pDC->FillSolidRect(0, i, uiWidth, 1, RGB(r, g, b));
		}

		RECT leftPanelRect;
		leftPanelRect.left = 0;
		leftPanelRect.top = 0;
		leftPanelRect.right = g_uiLeftPanelWidth;
		leftPanelRect.bottom = clientRect.bottom;
		HBRUSH bkgBrush = CreateSolidBrush(RGB(229, 234, 245));
		FillRect(hdc, &leftPanelRect, bkgBrush);
		DeleteObject(bkgBrush);
		*/
	}
	else if (getDisplayType() == DISPLAYTYPE_FLOAT)
	{
		HBRUSH bkgBrush = nullptr;
		bkgBrush = CreateSolidBrush(RGB(255, 255, 255));
		FillRect(hdc, &clientRect, bkgBrush);
		DeleteObject(bkgBrush);
	}
}

void			onPaint(HWND hwnd)
{
	getIMGF()->getEntryViewerManager()->getTextureViewer()->render();
}

void			CTextureViewer::render(void)
{
	// display textures (images + text)
	if (getIMGF()->getEntryViewerManager()->getTextureViewer()->getDisplayType() == DISPLAYTYPE_SINGLE)
	{
		renderDisplayType_Single();
	}
	else if (getIMGF()->getEntryViewerManager()->getTextureViewer()->getDisplayType() == DISPLAYTYPE_FLOAT)
	{
		renderDisplayType_Float();
	}

	/*
	if (fScroll)
	{
	PRECT prect = &ps.rcPaint;

	BitBlt(ps.hdc,
	prect->left, prect->top,
	(prect->right - prect->left),
	(prect->bottom - prect->top),
	hdcScreenCompat,
	prect->left + 0,
	prect->top + yCurrentScroll,
	SRCCOPY);

	fScroll = FALSE;
	}
	*/
}

void			CTextureViewer::renderDisplayType_Single(void)
{
	HWND hwnd = getWindowHwnd();

	HDC memDC, hdc;
	HGDIOBJ old = nullptr;
	PAINTSTRUCT ps;
	RECT clientRect;
	int width, height;

	hdc = BeginPaint(hwnd, &ps);

	if (!bPremultipledAlphaApplied)
	{
		for (auto pImageData : getIMGF()->getEntryViewerManager()->getTextureViewer()->getEntries())
		{
			PremultiplyBitmapAlpha(hdc, pImageData->m_hBitmap);
		}
		bPremultipledAlphaApplied = true;
	}

	if (fSize)
	{
		BitBlt(ps.hdc,
			0, 0,
			800, getIMGF()->getEntryViewerManager()->getTextureViewer()->getWindowScrollbarMaxRange(),
			hdcScreenCompat,
			0, yCurrentScroll,
			SRCCOPY);

		fSize = FALSE;
	}

	getIMGF()->getEntryViewerManager()->getTextureViewer()->clearWindowBackground(hdc);

	GetClientRect(hwnd, &clientRect);
	width = clientRect.right - clientRect.left;
	height = clientRect.bottom - clientRect.top;

	memDC = CreateCompatibleDC(NULL);

	Graphics graphics(hdc);





	// display type: Single
	const uint32
		uiImagePaddingRight = 10,
		uiImagePaddingBottom = 10,
		uiEntryViewerWindowClientAreaWidth = 494;
	uint32
		uiImageX = 0,// uiSingleDisplayTypeTopScrollbarXCurrentScroll,
		uiImageY = 0,
		uiHighestImageInRow = 0,
		uiCalculatedWidth,
		uiTextureIndex = 0;
	CTextureViewerTextureData
		*pActiveImageData = getIMGF()->getEntryViewerManager()->getTextureViewer()->getActiveEntry();
	for (auto pImageData : getIMGF()->getEntryViewerManager()->getTextureViewer()->getEntries())
	{
		uint32 uiTop = uiImageY == 0 ? 0 : (uiImageY - 5);
		if (getIMGF()->getEntryViewerManager()->getTextureViewer()->isTexturePreviewEnabled())
		{
			pImageData->m_rect.left = 0;
			pImageData->m_rect.top = (uiImageY - 5) + 1;
			pImageData->m_rect.right = g_uiLeftPanelWidth;
			pImageData->m_rect.bottom = uiImageY + 45 + 128 + 5;
		}
		else
		{
			/*
			pImageData->m_rect.left = 0;
			pImageData->m_rect.top = uiTop;
			pImageData->m_rect.right = g_uiLeftPanelWidth;
			pImageData->m_rect.bottom = (uiImageY + 15 + 15 + 15 + 10) - 5;
			*/
			pImageData->m_rect.left = 0;
			pImageData->m_rect.top = (uiImageY - 5) + 1;
			pImageData->m_rect.right = g_uiLeftPanelWidth;
			pImageData->m_rect.bottom = uiImageY + 45 + 5;
		}

		if (false)
		{
			uiCalculatedWidth = 0;
			old = (HBITMAP)SelectObject(memDC, pImageData->m_hBitmap);

			// calculate max width out of: image, diffuse text and alpha text
			SIZE textSize;
			GetTextExtentPoint32(hdc, CString2::convertStdStringToStdWString(pImageData->m_strDiffuseName).c_str(), pImageData->m_strDiffuseName.length(), &textSize);
			uiCalculatedWidth = textSize.cx;

			SIZE textSize2;
			GetTextExtentPoint32(hdc, CString2::convertStdStringToStdWString(pImageData->m_strAlphaName).c_str(), pImageData->m_strAlphaName.length(), &textSize2);
			if (textSize2.cx > uiCalculatedWidth)
			{
				uiCalculatedWidth = textSize2.cx;
			}

			if (pImageData->m_uiWidth > uiCalculatedWidth)
			{
				uiCalculatedWidth = pImageData->m_uiWidth;
			}
			//CDebugger::log("IMAGE X = " + CString2::toString(uiImageX));

			// draw texture diffuse name
			SetTextColor(hdc, RGB(255, 255, 255));
			SetBkMode(hdc, TRANSPARENT);
			RECT rect;
			rect.left = uiImageX;
			rect.top = uiImageY + 0 - yCurrentScroll;
			rect.right = 8000;
			rect.bottom = 8000;
			DrawText(hdc, CString2::convertStdStringToStdWString(pImageData->m_strDiffuseName).c_str(), pImageData->m_strDiffuseName.length(), &rect, DT_NOPREFIX);

			// draw texture alpha name
			SetTextColor(hdc, RGB(255, 255, 255));
			SetBkMode(hdc, TRANSPARENT);
			rect.left = uiImageX;
			rect.top = uiImageY + 20 - yCurrentScroll;
			rect.right = 8000;
			rect.bottom = 8000;
			DrawText(hdc, CString2::convertStdStringToStdWString(pImageData->m_strAlphaName).c_str(), pImageData->m_strAlphaName.length(), &rect, DT_NOPREFIX);

			// draw texture image
			//byte alpha = 255;
			//BLENDFUNCTION bf = { AC_SRC_OVER, 0, alpha, AC_SRC_ALPHA };
			//AlphaBlend(hdc, 0, 0, width, height, memDC, 0, 0, width, height, bf);
			// try the below instead of AlphaBlend - they each rely on the fact I've resized the
			// client area to the same size as the image I'll draw on it.
			//BitBlt(hdc, 0,0, clientRect.right,clientRect.bottom, memDC, 0,0, SRCCOPY);
			//BitBlt(hdc, 0, 0, width, height, memDC, 0, 0, BLACKNESS);
			BitBlt(hdc, uiImageX, uiImageY + 40 - yCurrentScroll, width, height, memDC, 0, 0, SRCCOPY);

			// texture calculations 2
			uiImageX += uiCalculatedWidth + uiImagePaddingRight;
			/*
			if (pImageData->m_uiWidth > uiLongestImageInRow)
			{
			uiLongestImageInRow = pImageData->m_uiWidth;
			}
			*/
		}
		else
		{
			uiCalculatedWidth = 0;

			// calculate max width out of: image, diffuse text and alpha text
			SIZE textSize;
			GetTextExtentPoint32(hdc, CString2::convertStdStringToStdWString(pImageData->m_strDiffuseName).c_str(), pImageData->m_strDiffuseName.length(), &textSize);
			uiCalculatedWidth = textSize.cx;

			SIZE textSize2;
			GetTextExtentPoint32(hdc, CString2::convertStdStringToStdWString(pImageData->m_strAlphaName).c_str(), pImageData->m_strAlphaName.length(), &textSize2);
			if (textSize2.cx > uiCalculatedWidth)
			{
				uiCalculatedWidth = textSize2.cx;
			}

			if (pImageData->m_uiWidth > uiCalculatedWidth)
			{
				uiCalculatedWidth = pImageData->m_uiWidth;
			}

			// draw active texture background colour
			if (pImageData == getIMGF()->getEntryViewerManager()->getTextureViewer()->getActiveEntry())
			{
				RECT rect2 = pImageData->m_rect;
				rect2.top -= yCurrentScroll;
				rect2.bottom -= yCurrentScroll;
				HBRUSH bkgBrush = CreateSolidBrush(RGB(255, 255, 0));
				FillRect(hdc, &rect2, bkgBrush);
				DeleteObject(bkgBrush);

				/*
				HDC tempHdc = CreateCompatibleDC(hdc);
				int width = pImageData->m_rect.right - pImageData->m_rect.left;
				int height = pImageData->m_rect.bottom - pImageData->m_rect.top;
				HBITMAP canvas = CreateCompatibleBitmap(hdc, width, height);
				// select new bitmap into context, don't forget to save old bitmap handle
				HBITMAP oldBmp = (HBITMAP) SelectObject(tempHdc, canvas);

				SetDCPenColor(tempHdc, RGB(255, 255, 0));
				SetDCBrushColor(tempHdc, RGB(255, 255, 0));
				Rectangle(tempHdc, pImageData->m_rect.left, pImageData->m_rect.top, pImageData->m_rect.right, pImageData->m_rect.bottom);
				BLENDFUNCTION blend = { AC_SRC_OVER, 0, 127, AC_SRC_ALPHA };
				AlphaBlend(hdc, pImageData->m_rect.left, pImageData->m_rect.top, pImageData->m_rect.right - pImageData->m_rect.left, pImageData->m_rect.bottom - pImageData->m_rect.top, tempHdc, 0, 0, pImageData->m_rect.right - pImageData->m_rect.left, pImageData->m_rect.bottom - pImageData->m_rect.top, blend);
				*/
			}

			// draw texture number
			HFONT hFont = CreateFont(22, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
				CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Verdana"));
			old = SelectObject(hdc, hFont);

			SetTextColor(hdc, RGB(0, 0, 0));
			SetBkMode(hdc, TRANSPARENT);

			RECT rect;

			rect.left = uiImageX + 5;
			rect.top = uiImageY + 10 - yCurrentScroll;
			rect.right = 8000;
			rect.bottom = 8000;
			string strText = CString2::toString(uiTextureIndex + 1);
			DrawText(hdc, CString2::convertStdStringToStdWString(strText).c_str(), strText.length(), &rect, DT_NOPREFIX);

			// draw texture diffuse name
			HFONT hFont2 = CreateFont(13, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
				CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Verdana"));
			old = SelectObject(hdc, hFont2);

			uint32 uiXOffset1 = 50;

			rect.left = uiImageX + uiXOffset1;
			rect.top = uiImageY - yCurrentScroll;
			rect.right = 8000;
			rect.bottom = 8000;
			DrawText(hdc, CString2::convertStdStringToStdWString(pImageData->m_strDiffuseName).c_str(), pImageData->m_strDiffuseName.length(), &rect, DT_NOPREFIX);
			uiImageY += 15;

			// draw texture alpha name
			if (pImageData->m_strAlphaName != "")
			{
				rect.left = uiImageX + uiXOffset1;
				rect.top = uiImageY - yCurrentScroll;
				rect.right = 8000;
				rect.bottom = 8000;
				DrawText(hdc, CString2::convertStdStringToStdWString(pImageData->m_strAlphaName).c_str(), pImageData->m_strAlphaName.length(), &rect, DT_NOPREFIX);
				uiImageY += 15;
			}

			// draw texture size
			rect.left = uiImageX + uiXOffset1;
			rect.top = uiImageY - yCurrentScroll;
			rect.right = 8000;
			rect.bottom = 8000;
			strText = CString2::toString(pImageData->m_uiWidth) + " x " + CString2::toString(pImageData->m_uiHeight);
			DrawText(hdc, CString2::convertStdStringToStdWString(strText).c_str(), strText.length(), &rect, DT_NOPREFIX); // size

			// draw texture BPP
			rect.left = uiImageX + uiXOffset1 + 85;
			rect.top = uiImageY - yCurrentScroll;
			rect.right = 8000;
			rect.bottom = 8000;
			strText = CLocalizationManager::getInstance()->getTranslatedFormattedText("Window_TextureViewer_BPP", pImageData->m_ucBPP);
			DrawText(hdc, CString2::convertStdStringToStdWString(strText).c_str(), strText.length(), &rect, DT_NOPREFIX); // BPP

			// draw texture raster format
			rect.left = uiImageX + uiXOffset1 + 85 + 55;
			rect.top = uiImageY - yCurrentScroll;
			rect.right = 8000;
			rect.bottom = 8000;
			strText = pImageData->m_strTextureFormat;
			DrawText(hdc, CString2::convertStdStringToStdWString(strText).c_str(), strText.length(), &rect, DT_NOPREFIX); // raster format

			uiImageY += 15;
			if (pImageData->m_strAlphaName == "")
			{
				uiImageY += 15;
			}
			SelectObject(hdc, old);
			DeleteObject(hFont);
			DeleteObject(hFont2);

			// draw texture image preview
			if (getIMGF()->getEntryViewerManager()->getTextureViewer()->isTexturePreviewEnabled())
			{
				old = (HBITMAP)SelectObject(memDC, pImageData->m_hBitmap);

				uint32 uiImageWidthWhenHeightIs128 = ((float32)128.0f / (float32)pImageData->m_uiHeight) * pImageData->m_uiWidth;
				uint32 uiImageHeightWhenWidthIs128 = ((float32)128.0f / (float32)pImageData->m_uiWidth) * pImageData->m_uiHeight;

				uint32 uiDestWidth;
				uint32 uiDestHeight;
				if (uiImageWidthWhenHeightIs128 > uiImageHeightWhenWidthIs128)
				{
					uiDestWidth = 128;
					uiDestHeight = uiImageHeightWhenWidthIs128;
				}
				else
				{
					uiDestWidth = uiImageWidthWhenHeightIs128;
					uiDestHeight = 128;
				}

				//StretchBlt(hdc, uiImageX + 20, uiImageY - yCurrentScroll, uiDestWidth, uiDestHeight, memDC, 0, 0, pImageData->m_uiWidth, pImageData->m_uiHeight, SRCCOPY);
				uint32 uiAlpha = 255;
				BLENDFUNCTION bf = { AC_SRC_OVER, 0, uiAlpha, AC_SRC_ALPHA };
				AlphaBlend(hdc, uiImageX + 20, uiImageY - yCurrentScroll, uiDestWidth, uiDestHeight, memDC, 0, 0, pImageData->m_uiWidth, pImageData->m_uiHeight, bf);
				uiImageY += 128;
			}

			/*
			pImageData->m_rect.left = uiImageX + 20;
			pImageData->m_rect.top = uiImageY;
			pImageData->m_rect.right = uiImageX + 20 + 128;
			pImageData->m_rect.bottom = uiImageY + 128 + 20 + 20;
			*/

			uiImageY += 10;

			//uint32 uiItemHeight = 128 + 20 + 20 + uiImagePaddingBottom;


			// texture calculations 2
			//uint32 uiImageDisplayedHeight = 128;
			//uiImageY += pImageData->m_uiHeight + 20 + 20 + uiImagePaddingBottom;
			//uiImageY += uiItemHeight;

			/*
			if (pImageData->m_uiWidth > uiLongestImageInRow)
			{
			uiLongestImageInRow = pImageData->m_uiWidth;
			}
			*/

			// horizontal line below texture image
			Pen      pen(Color(255, 0, 0, 0));
			graphics.DrawLine(&pen, 0, uiImageY - (uiImagePaddingBottom / 2) - yCurrentScroll, g_uiLeftPanelWidth, uiImageY - (uiImagePaddingBottom / 2) - yCurrentScroll);
		}

		uiTextureIndex++;
	}

	// zoom text
	HFONT hFont = CreateFont(15, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Verdana"));
	old = SelectObject(hdc, hFont);

	SetTextColor(hdc, RGB(0, 0, 0));
	SetBkMode(hdc, TRANSPARENT);

	RECT rect;
	rect.left = g_uiLeftPanelWidth + 5;
	rect.top = 10;
	rect.right = 8000;
	rect.bottom = 8000;
	string strText = CLocalizationManager::getInstance()->getTranslatedText("Window_TextureViewer_Zoom");
	DrawText(hdc, CString2::convertStdStringToStdWString(strText).c_str(), strText.length(), &rect, DT_NOPREFIX);

	// vertical line next to textures list
	Pen      pen(Color(255, 0, 0, 0));
	//graphics.DrawLine(&pen, 180, 0, 180, clientRect.bottom);

	// horizontal line above active image
	graphics.DrawLine(&pen, g_uiLeftPanelWidth, 50, clientRect.right, 50);

	// active texture image
	old = (HBITMAP)SelectObject(memDC, pActiveImageData->m_hBitmap);
	//float32 fZoom = 4.0;
	//uint32 uiDestinationWidth = ((float32)pActiveImageData->m_uiWidth) * fZoom;
	//uint32 uiDestinationHeight = ((float32)pActiveImageData->m_uiHeight) * fZoom;
	uint32 uiDestinationWidth = (float32)pActiveImageData->m_uiWidth * getIMGF()->getEntryViewerManager()->getTextureViewer()->getZoomLevel();
	uint32 uiDestinationHeight = (float32)pActiveImageData->m_uiHeight * getIMGF()->getEntryViewerManager()->getTextureViewer()->getZoomLevel();

	//BitBlt(hdc, g_uiLeftPanelWidth, 50 + 1, uiDestinationWidth, uiDestinationHeight, memDC, 0, 0, SRCCOPY);
	//StretchBlt(hdc, g_uiLeftPanelWidth, 50 + 1, uiDestinationWidth, uiDestinationHeight, memDC, 0, 0, pActiveImageData->m_uiWidth, pActiveImageData->m_uiHeight, SRCCOPY);

	uint32 uiAlpha = 255;
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, uiAlpha, AC_SRC_ALPHA };
	AlphaBlend(hdc, g_uiLeftPanelWidth, 50 + 1, uiDestinationWidth, uiDestinationHeight, memDC, 0, 0, pActiveImageData->m_uiWidth, pActiveImageData->m_uiHeight, bf);

	//TransparentBlt(hdc, g_uiLeftPanelWidth, 50 + 1, uiDestinationWidth, uiDestinationHeight, memDC, 0, 0, pActiveImageData->m_uiWidth, pActiveImageData->m_uiHeight, RGB(255,255,255));

	//SelectObject(memDC, pActiveImageData->m_hBitmap);
	//StretchBlt(hdc, g_uiLeftPanelWidth, 50 + 1, uiDestinationWidth, uiDestinationHeight, memDC, 0, 0, pActiveImageData->m_uiWidth, pActiveImageData->m_uiHeight, SRCAND);

	//SelectObject(memDC, pActiveImageData->m_hBitmap);
	//StretchBlt(hdc, g_uiLeftPanelWidth, 50 + 1, uiDestinationWidth, uiDestinationHeight, memDC, 0, 0, pActiveImageData->m_uiWidth, pActiveImageData->m_uiHeight, SRCPAINT);

	// active texture text
	/*
	RECT rect;
	rect.left = g_uiLeftPanelWidth + 5;
	rect.top = 6;
	rect.right = 8000;
	rect.bottom = 8000;
	DrawText(hdc, CString2::convertStdStringToStdWString(pActiveImageData->m_strDiffuseName).c_str(), pActiveImageData->m_strDiffuseName.length(), &rect, DT_NOPREFIX); // diffuse name

	rect.left = g_uiLeftPanelWidth + 5;
	rect.top = 25;
	rect.right = 8000;
	rect.bottom = 8000;
	DrawText(hdc, CString2::convertStdStringToStdWString(pActiveImageData->m_strAlphaName).c_str(), pActiveImageData->m_strAlphaName.length(), &rect, DT_NOPREFIX); // alpha name

	rect.left = g_uiLeftPanelWidth + 120 + 5;
	rect.top = 6;
	rect.right = 8000;
	rect.bottom = 8000;
	string strText = CString2::toString(pActiveImageData->m_uiWidth) + " x " + CString2::toString(pActiveImageData->m_uiHeight);
	DrawText(hdc, CString2::convertStdStringToStdWString(strText).c_str(), strText.length(), &rect, DT_NOPREFIX); // size

	rect.left = g_uiLeftPanelWidth + 120 + 5;
	rect.top = 25;
	rect.right = 8000;
	rect.bottom = 8000;
	strText = CLocalizationManager::getInstance()->getTranslatedFormattedText("Window_TextureViewer_BPP", pActiveImageData->m_ucBPP);
	DrawText(hdc, CString2::convertStdStringToStdWString(strText).c_str(), strText.length(), &rect, DT_NOPREFIX); // BPP

	rect.left = g_uiLeftPanelWidth + 145 + 5;
	rect.top = 6;
	rect.right = 8000;
	rect.bottom = 8000;
	strText = "0x" + CString2::toStringHex(pActiveImageData->m_uiRasterFormat);
	DrawText(hdc, CString2::convertStdStringToStdWString(strText).c_str(), strText.length(), &rect, DT_NOPREFIX); // raster format
	*/

	SelectObject(hdc, old);
	DeleteObject(hFont);
	
	getIMGF()->getEntryViewerManager()->getTextureViewer()->setWindowScrollbarMaxRange(uiImageY + 200);

	if (false)
	{
		uint32 uiMaxXPosition = uiImageX + uiCalculatedWidth + uiImagePaddingRight;
		if (clientRect.bottom > uiMaxXPosition)
		{
			uiMaxXPosition = clientRect.bottom;
		}
		uiMaxXPosition += 100;
		getIMGF()->getEntryViewerManager()->getTextureViewer()->setSingleDisplayTypeTopScrollbarMaxXPosition(uiMaxXPosition);
	}




	SelectObject(memDC, old);
	DeleteDC(memDC);
	EndPaint(hwnd, &ps);
}

void			CTextureViewer::renderDisplayType_Float(void)
{
	HWND hwnd = getWindowHwnd();

	HDC memDC, hdc;
	HGDIOBJ old = nullptr;
	PAINTSTRUCT ps;
	RECT clientRect;
	int width, height;

	hdc = BeginPaint(hwnd, &ps);

	if (!bPremultipledAlphaApplied)
	{
		for (auto pImageData : getIMGF()->getEntryViewerManager()->getTextureViewer()->getEntries())
		{
			PremultiplyBitmapAlpha(hdc, pImageData->m_hBitmap);
		}
		bPremultipledAlphaApplied = true;
	}

	if (fSize)
	{
		BitBlt(ps.hdc,
			0, 0,
			800, getIMGF()->getEntryViewerManager()->getTextureViewer()->getWindowScrollbarMaxRange(),
			hdcScreenCompat,
			0, yCurrentScroll,
			SRCCOPY);

		fSize = FALSE;
	}

	getIMGF()->getEntryViewerManager()->getTextureViewer()->clearWindowBackground(hdc);

	GetClientRect(hwnd, &clientRect);
	width = clientRect.right - clientRect.left;
	height = clientRect.bottom - clientRect.top;

	memDC = CreateCompatibleDC(NULL);

	Graphics graphics(hdc);





	// display type: Float
	const uint32
		uiImagePaddingRight = 10,
		uiImagePaddingBottom = 10,
		uiEntryViewerWindowClientAreaWidth = 494;
	uint32
		uiImageX = 0,
		uiImageY = 0,
		uiHighestImageInRow = 0,
		uiCalculatedWidth;
	for (auto pImageData : getIMGF()->getEntryViewerManager()->getTextureViewer()->getEntries())
	{
		uiCalculatedWidth = 0;
		old = (HBITMAP)SelectObject(memDC, pImageData->m_hBitmap);

		// calculate max width out of: image, diffuse text and alpha text
		SIZE textSize;
		GetTextExtentPoint32(hdc, CString2::convertStdStringToStdWString(pImageData->m_strDiffuseName).c_str(), pImageData->m_strDiffuseName.length(), &textSize);
		uiCalculatedWidth = textSize.cx;

		SIZE textSize2;
		GetTextExtentPoint32(hdc, CString2::convertStdStringToStdWString(pImageData->m_strAlphaName).c_str(), pImageData->m_strAlphaName.length(), &textSize2);
		if (textSize2.cx > uiCalculatedWidth)
		{
			uiCalculatedWidth = textSize2.cx;
		}

		if (pImageData->m_uiWidth > uiCalculatedWidth)
		{
			uiCalculatedWidth = pImageData->m_uiWidth;
		}

		// texture calculations 1
		if ((uiImageX + uiCalculatedWidth /*+ uiImagePaddingRight*/) > clientRect.right/*uiEntryViewerWindowClientAreaWidth*/)
		{
			uiImageX = 0;
			uiImageY += uiHighestImageInRow + 40 + uiImagePaddingBottom;
			uiHighestImageInRow = 0;
		}

		HFONT hFont = CreateFont(16, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Verdana"));
		old = SelectObject(hdc, hFont);

		// draw texture diffuse name
		SetTextColor(hdc, RGB(0, 0, 0));
		SetBkMode(hdc, TRANSPARENT);
		RECT rect;
		rect.left = uiImageX;
		rect.top = uiImageY + 0 - yCurrentScroll;
		rect.right = 8000;
		rect.bottom = 8000;
		DrawText(hdc, CString2::convertStdStringToStdWString(pImageData->m_strDiffuseName).c_str(), pImageData->m_strDiffuseName.length(), &rect, DT_NOPREFIX);

		// draw texture alpha name
		SetTextColor(hdc, RGB(0, 0, 0));
		SetBkMode(hdc, TRANSPARENT);
		rect.left = uiImageX;
		rect.top = uiImageY + 20 - yCurrentScroll;
		rect.right = 8000;
		rect.bottom = 8000;
		DrawText(hdc, CString2::convertStdStringToStdWString(pImageData->m_strAlphaName).c_str(), pImageData->m_strAlphaName.length(), &rect, DT_NOPREFIX);

		// draw texture image
		//byte alpha = 255;
		//BLENDFUNCTION bf = { AC_SRC_OVER, 0, alpha, AC_SRC_ALPHA };
		//AlphaBlend(hdc, 0, 0, width, height, memDC, 0, 0, width, height, bf);
		// try the below instead of AlphaBlend - they each rely on the fact I've resized the
		// client area to the same size as the image I'll draw on it.
		//BitBlt(hdc, 0,0, clientRect.right,clientRect.bottom, memDC, 0,0, SRCCOPY);
		//BitBlt(hdc, 0, 0, width, height, memDC, 0, 0, BLACKNESS);

		//BitBlt(hdc, uiImageX, uiImageY + 40 - yCurrentScroll, width, height, memDC, 0, 0, SRCCOPY);
		uint32 uiAlpha = 255;
		BLENDFUNCTION bf = { AC_SRC_OVER, 0, uiAlpha, AC_SRC_ALPHA };
		AlphaBlend(hdc, uiImageX, uiImageY + 40 - yCurrentScroll, pImageData->m_uiWidth, pImageData->m_uiHeight, memDC, 0, 0, pImageData->m_uiWidth, pImageData->m_uiHeight, bf);

		// texture calculations 2
		uiImageX += uiCalculatedWidth + uiImagePaddingRight;
		if (pImageData->m_uiHeight > uiHighestImageInRow)
		{
			uiHighestImageInRow = pImageData->m_uiHeight;
		}

		DeleteObject(hFont);
	}

	uint32 uiMaxYPosition = uiImageY + uiHighestImageInRow + uiImagePaddingBottom;
	if (clientRect.bottom > uiMaxYPosition)
	{
		uiMaxYPosition = clientRect.bottom;
	}
	uiMaxYPosition += 100;
	getIMGF()->getEntryViewerManager()->getTextureViewer()->setWindowScrollbarMaxRange(uiMaxYPosition);




	SelectObject(memDC, old);
	DeleteDC(memDC);
	EndPaint(hwnd, &ps);
}