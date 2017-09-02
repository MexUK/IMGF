#include "UpdateManager.h"
#include "UpdateConnectionManager.h"

using namespace bxcf;
using namespace imgf;

UpdateManager::UpdateManager(void)
{
	m_pUpdateConnectionManager = new UpdateConnectionManager;
}
UpdateManager::~UpdateManager(void)
{
	delete m_pUpdateConnectionManager;
}

void		UpdateManager::init(void)
{
	m_pUpdateConnectionManager->init();
}
void		UpdateManager::uninit(void)
{
	m_pUpdateConnectionManager->uninit();
}