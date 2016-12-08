#ifndef CTextureViewer_H
#define CTextureViewer_H

#include <Windows.h>
#include "CEntryViewer.h"
#include "Pool/CVectorPool.h"
#include "eEntryViewerDisplayType.h"
#include "CTextureViewerTextureData.h"

class mcore::CIMGEntry;

LRESULT CALLBACK				WndProc_EntryViewer(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

class CTextureViewer : public CEntryViewer, public mcore::CVectorPool<CTextureViewerTextureData*>
{
public:
	CTextureViewer(void);

	void						reset(void);
	void						prepareRenderData(void);
	void						render(void);
	void						openWindow(void);
	void						closeWindow(void);

	void						setIMGEntry(mcore::CIMGEntry *pIMGEntry) { m_pIMGEntry = pIMGEntry; }
	mcore::CIMGEntry*					getIMGEntry(void) { return m_pIMGEntry; }

	void						setWindowHwnd(HWND hwndEntryViewerWindow) { m_hwndEntryViewerWindow = hwndEntryViewerWindow; }
	HWND						getWindowHwnd(void) { return m_hwndEntryViewerWindow; }

	void						setActiveEntry(CTextureViewerTextureData *pActiveEntry) { m_pActiveEntry = pActiveEntry; }
	CTextureViewerTextureData*	getActiveEntry(void) { return m_pActiveEntry; }

	void						setDisplayType(eEntryViewerDisplayType eEntryViewerDisplayTypeValue);
	eEntryViewerDisplayType		getDisplayType(void) { return m_eEntryViewerDisplayType; }
	void						initDisplayType(void);
	void						uninitDisplayType(void);

	void						setTexturePreviewEnabled(bool bTexturePreview) { m_bTexturePreviewIsEnabled = bTexturePreview; }
	bool						isTexturePreviewEnabled(void) { return m_bTexturePreviewIsEnabled; }

	void						setZoomLevel(float32 fZoomLevel) { m_fZoomLevel = fZoomLevel; }
	float32						getZoomLevel(void) { return m_fZoomLevel; }

	void						setViewMenu(HMENU hViewMenu) { m_hViewMenu = hViewMenu; }
	HMENU						getViewMenu(void) { return m_hViewMenu; }

	void						setDisplayTypeMenu(HMENU hDisplayTypeMenu) { m_hDisplayTypeMenu = hDisplayTypeMenu; }
	HMENU						getDisplayTypeMenu(void) { return m_hDisplayTypeMenu; }

	void						setWindowScrollbarMaxRange(uint32 uiWindowScrollbarMaxRange) { m_uiWindowScrollbarMaxRange = uiWindowScrollbarMaxRange; }
	uint32						getWindowScrollbarMaxRange(void) { return m_uiWindowScrollbarMaxRange; }

	void						setSingleDisplayTypeTopScrollbarHwnd(HWND hWnd) { m_hSingleDisplayTypeTopScrollbarHwnd = hWnd; }
	HWND						getSingleDisplayTypeTopScrollbarHwnd(void) { return m_hSingleDisplayTypeTopScrollbarHwnd; }

	void						setSingleDisplayTypeTopScrollbarMaxXPosition(uint32 uiMaxXPosition) { m_uiSingleDisplayTypeTopScrollbarMaxXPosition = uiMaxXPosition; }
	uint32						getSingleDisplayTypeTopScrollbarMaxXPosition(void) { return m_uiSingleDisplayTypeTopScrollbarMaxXPosition; }

	void						loadThreadAndWindow(void);
	void						unloadThreadAndWindow(void);
	static DWORD WINAPI			onThreadStarted(LPVOID lpParam);
	void						processWindow(void);

	void						applyWindowTitle(void);

	void						forceRender(void);
	void						clearWindowBackground(HDC hdc);

	void						repositionWindow(void);

private:
	void						prepareRenderData_TXD(void);
	void						prepareRenderData_WTD(void);

	void						renderDisplayType_Single(void);
	void						renderDisplayType_Float(void);

private:
	mcore::CIMGEntry*					m_pIMGEntry;
	HWND						m_hwndEntryViewerWindow;
	CTextureViewerTextureData*	m_pActiveEntry;
	float32						m_fZoomLevel;
	eEntryViewerDisplayType		m_eEntryViewerDisplayType;
	HMENU						m_hViewMenu;
	HMENU						m_hDisplayTypeMenu;
	uint32						m_uiWindowScrollbarMaxRange;
	HWND						m_hSingleDisplayTypeTopScrollbarHwnd;
	uint32						m_uiSingleDisplayTypeTopScrollbarMaxXPosition;
	ULONG_PTR					m_gdiplusToken;
	uint8						m_bTexturePreviewIsEnabled : 1;
};

#endif