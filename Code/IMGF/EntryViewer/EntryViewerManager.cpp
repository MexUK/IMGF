#include "EntryViewerManager.h"
#include "TextureViewer.h"
#include "CollisionViewer.h"

using namespace bxcf;
using namespace imgf;

EntryViewerManager::EntryViewerManager(void)
{
	m_pTextureViewer	= new TextureViewer;
	m_pCollisionViewer	= new CollisionViewer;
}
EntryViewerManager::~EntryViewerManager(void)
{
	delete m_pTextureViewer;
	delete m_pCollisionViewer;
}

void				EntryViewerManager::init(void)
{
	//m_pTextureViewer->init();
	m_pCollisionViewer->init();
}
void				EntryViewerManager::uninit(void)
{
	//m_pTextureViewer->uninit();
	m_pCollisionViewer->uninit();
}