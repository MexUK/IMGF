#pragma once

#include "nsimgf.h"
#include <Windows.h>
#include "nsbxgi.h"
#include "EntryViewer.h"
#include "Pool/VectorPool.h"
#include "EEntryViewerDisplayType.h"
#include "TextureViewerTextureData.h"

class bxgi::IMGEntry;

LRESULT CALLBACK				WndProc_EntryViewer(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

class imgf::TextureViewer : public EntryViewer, public bxcf::VectorPool<TextureViewerTextureData*>
{
public:
	TextureViewer(void);

	void						reset(void);
	void						prepareRenderData(void);
	void						render(void);
	void						openWindow(void);
	void						closeWindow(void);

	void						setIMGEntry(bxgi::IMGEntry *pIMGEntry) { m_pIMGEntry = pIMGEntry; }
	bxgi::IMGEntry*			getIMGEntry(void) { return m_pIMGEntry; }

	void						setWindowHwnd(HWND hwndEntryViewerWindow) { m_hwndEntryViewerWindow = hwndEntryViewerWindow; }
	HWND						getWindowHwnd(void) { return m_hwndEntryViewerWindow; }

	void						setActiveEntry(TextureViewerTextureData *pActiveEntry) { m_pActiveEntry = pActiveEntry; }
	TextureViewerTextureData*	getActiveEntry(void) { return m_pActiveEntry; }

	void						setDisplayType(EEntryViewerDisplayType EEntryViewerDisplayTypeValue);
	EEntryViewerDisplayType		getDisplayType(void) { return m_EEntryViewerDisplayType; }
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
	bxgi::IMGEntry*					m_pIMGEntry;
	HWND						m_hwndEntryViewerWindow;
	TextureViewerTextureData*	m_pActiveEntry;
	float32						m_fZoomLevel;
	EEntryViewerDisplayType		m_EEntryViewerDisplayType;
	HMENU						m_hViewMenu;
	HMENU						m_hDisplayTypeMenu;
	uint32						m_uiWindowScrollbarMaxRange;
	HWND						m_hSingleDisplayTypeTopScrollbarHwnd;
	uint32						m_uiSingleDisplayTypeTopScrollbarMaxXPosition;
	ULONG_PTR					m_gdiplusToken;
	uint8						m_bTexturePreviewIsEnabled : 1;
};