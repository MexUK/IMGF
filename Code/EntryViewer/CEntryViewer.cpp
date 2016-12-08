#include "mcore.h"
#include "CEntryViewer.h"

using namespace mcore;

CEntryViewer::CEntryViewer(void) :
	m_bWindowIsOpen(false),
	m_bEntityDataIsCorrupt(false),
	m_bRenderDataIsReady(false)
{
}

void			CEntryViewer::reset(void)
{
	setWindowIsOpen(false);
	setEntityDataIsCorrupt(false);
	setRenderDataIsReady(false);
}