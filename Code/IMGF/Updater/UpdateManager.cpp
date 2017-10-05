#include "UpdateManager.h"
#include "UpdateConnectionManager.h"
#include "IMGF.h"
#include "Task/TaskManager.h"
#include "Task/Tasks/Tasks.h"

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

// initialization
void							UpdateManager::init(void)
{
	m_pUpdateConnectionManager->init();
}

void							UpdateManager::uninit(void)
{
	m_pUpdateConnectionManager->uninit();
}

// update
void							UpdateManager::checkForUpdate(void)
{
	getIMGF()->getTaskManager()->getDispatch()->update(true); // todo - rename getDispatch to getTasks
}