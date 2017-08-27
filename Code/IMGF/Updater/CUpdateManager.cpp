#include "CUpdateManager.h"
#include "CUpdateConnectionManager.h"

using namespace bxcf;
using namespace imgf;

CUpdateManager::CUpdateManager(void)
{
	m_pUpdateConnectionManager = new CUpdateConnectionManager;
}
CUpdateManager::~CUpdateManager(void)
{
	delete m_pUpdateConnectionManager;
}

void		CUpdateManager::init(void)
{
	m_pUpdateConnectionManager->init();
}
void		CUpdateManager::uninit(void)
{
	m_pUpdateConnectionManager->uninit();
}