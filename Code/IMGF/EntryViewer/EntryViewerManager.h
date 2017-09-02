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
class imgf::TextureViewer;
class imgf::CollisionViewer;

class imgf::EntryViewerManager : public bxcf::CManager
{
public:
	EntryViewerManager(void);
	~EntryViewerManager(void);

	void									init(void);
	void									uninit(void);

	TextureViewer*							getTextureViewer(void) { return m_pTextureViewer; }
	CollisionViewer*						getCollisionViewer(void) { return m_pCollisionViewer; }

private:
	TextureViewer*							m_pTextureViewer;
	CollisionViewer*						m_pCollisionViewer;
};