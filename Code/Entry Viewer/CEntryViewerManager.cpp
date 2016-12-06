#include "CEntryViewerManager.h"
#include "CTextureViewer.h"
#include "CCollisionViewer.h"

using namespace mcore;

CEntryViewerManager::CEntryViewerManager(void)
{
	m_pTextureViewer	= new CTextureViewer;
	m_pCollisionViewer	= new CCollisionViewer;
}
CEntryViewerManager::~CEntryViewerManager(void)
{
	delete m_pTextureViewer;
	delete m_pCollisionViewer;
}

void				CEntryViewerManager::init(void)
{
	//m_pTextureViewer->init();
	m_pCollisionViewer->init();
}
void				CEntryViewerManager::uninit(void)
{
	//m_pTextureViewer->uninit();
	m_pCollisionViewer->uninit();
}