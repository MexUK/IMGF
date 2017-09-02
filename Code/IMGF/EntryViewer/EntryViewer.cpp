#include "nsbxcf.h"
#include "EntryViewer.h"

using namespace bxcf;
using namespace imgf;

EntryViewer::EntryViewer(void) :
	m_bWindowIsOpen(false),
	m_bEntityDataIsCorrupt(false),
	m_bRenderDataIsReady(false)
{
}

void			EntryViewer::reset(void)
{
	setWindowIsOpen(false);
	setEntityDataIsCorrupt(false);
	setRenderDataIsReady(false);
}