#ifndef CEntryViewerManager_H
#define CEntryViewerManager_H

#include <Windows.h>
#include "Object/CManager.h"
#include "Format/RockstarGames/TXD/eTXDRasterDataFormat.h"
#include "Image/eDXTCompressionType.h"
#include "d3d9.h"
#include <string>
#include <vector>

LRESULT CALLBACK	WndProc_EntryViewer(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void				onPaint(HWND hwnd);

class mcore::CIMGEntry;
class CTextureViewer;
class CCollisionViewer;

class CEntryViewerManager : public mcore::CManager
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

#endif