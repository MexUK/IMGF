#pragma once

#include "nsimgf.h"
#include <Windows.h>
#include "Object/CManager.h"
#include "Format/TXD/ETXDRasterDataFormat.h"
#include "Image/EDXTCompressionType.h"
#include "d3d9.h"

LRESULT CALLBACK	WndProc_EntryViewer(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void				onPaint(HWND hwnd);

class bxgi::CIMGEntry;
class imgf::CTextureViewer;
class imgf::CCollisionViewer;

class imgf::CEntryViewerManager : public bxcf::CManager
{
public:
	CEntryViewerManager(void);
	~CEntryViewerManager(void);

	void									init(void);
	void									uninit(void);

	CTextureViewer*							getTextureViewer(void) { return m_pTextureViewer; }
	CCollisionViewer*						getCollisionViewer(void) { return m_pCollisionViewer; }

private:
	CTextureViewer*							m_pTextureViewer;
	CCollisionViewer*						m_pCollisionViewer;
};