#include "CInputManager.h"
#include "GUI/Input/EInputItem.h"
#include "Controls/CButton.h"
#include "Controls/Entries/CMenuItem.h"
#include "Globals.h"
#include "IMGF.h"
#include "GUI/Window/CWindowManager.h"
#include "GUI/Windows/CMainWindow.h"
#include "GUI/Layer/ELayer.h"
#include "GUI/Layer/EMainMenuType.h"
#include "Task/CTaskManager.h"
#include "Task/CTaskDispatchManager.h"

using namespace bxgx;
using namespace bxgx::control::events;
using namespace imgf;
using namespace imgf::layers;
using namespace imgf::mainLayer::input;
using namespace imgf::mainLayer::mainMenuType;

// main interface
void					CInputManager::init(void)
{
	m_pMainWindow = g_pIMGF->getWindowManager()->getMainWindow();
	m_pTaskDispatchManager = g_pIMGF->getTaskManager()->getDispatch();

	bindEvents();
}

// bind events
void					CInputManager::bindEvents(void)
{
	bindEvent(PRESS_BUTTON, &CInputManager::onPressButton);
	bindEvent(PRESS_MENU_ITEM, &CInputManager::onPressMenuItem);
}

// forward button press
void					CInputManager::onPressButton(CButton *pButton)
{
	switch (pButton->getId())
	{
	case SETTINGS:			return settings();
	}
}

// forward button press
void					CInputManager::onPressMenuItem(CMenuItem *pMenuItem)
{
	switch (pMenuItem->getId())
	{
	case EInputItem::FORMATS:	return formats();
	case EInputItem::UTILITY:	return utility();

	case DAT:				return dat();
	case IMG:				return img();
	case ITEM_DEFINITION:	return itemDefinition();
	case ITEM_PLACEMENT:	return itemPlacement();
	case MODELS:			return models();
	case COLLISIONS:		return collisions();
	case TEXTURES:			return textures();
	case ANIMATIONS:		return animations();
	case RADAR:				return radar();

	case OPEN:				return open();
	case CLOSE:				return close();
	case SAVE:				return save();

	case IMPORT:			return _import();
	case EXPORT:			return _export();
	case QUICK_EXPORT:		return quickExport();
	case RENAME:			return rename();
	case REPLACE:			return replace();
	case REMOVE:			return remove();
	case MERGE:				return merge();
	case SPLIT:				return split();
	case CONVERT:			return convert();
	case SELECT:			return select();
	case SORT:				return sort();
	case LST:				return lst();
	}
}

// button press - menu type menu
void					CInputManager::formats(void)
{
	m_pMainWindow->setMainMenuType(EMainMenuType::FORMATS);
}

void					CInputManager::utility(void)
{
	m_pMainWindow->setMainMenuType(EMainMenuType::UTILITY);
}

// button press - format menu
void					CInputManager::dat(void)
{
}

void					CInputManager::img(void)
{
}

void					CInputManager::itemDefinition(void)
{
}

void					CInputManager::itemPlacement(void)
{
}

void					CInputManager::models(void)
{
}

void					CInputManager::collisions(void)
{
}

void					CInputManager::textures(void)
{
}

void					CInputManager::animations(void)
{
}

void					CInputManager::radar(void)
{
}

// button press - file menu
void					CInputManager::open(void)
{
	m_pTaskDispatchManager->chooseFilesToOpen();
}

void					CInputManager::close(void)
{
	m_pTaskDispatchManager->closeActiveFile();
}

void					CInputManager::save(void)
{
}

// button press - action menu
void					CInputManager::_import(void)
{
}

void					CInputManager::_export(void)
{
}

void					CInputManager::quickExport(void)
{
}

void					CInputManager::rename(void)
{
}

void					CInputManager::replace(void)
{
}

void					CInputManager::remove(void)
{
}

void					CInputManager::merge(void)
{
}

void					CInputManager::split(void)
{
}

void					CInputManager::convert(void)
{
}

void					CInputManager::select(void)
{
}

void					CInputManager::sort(void)
{
}

void					CInputManager::lst(void)
{
}

// settings
void					CInputManager::settings(void)
{
	CLayer *pLayer = m_pMainWindow->getLayerById(SETTINGS_MENU);
	pLayer->setEnabled(!pLayer->isEnabled());
}