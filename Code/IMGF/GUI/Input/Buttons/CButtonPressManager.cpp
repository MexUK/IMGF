#include "CButtonPressManager.h"
#include "GUI/Input/Buttons/EButtons.h"
#include "Controls/CButtonControl.h"
#include "Globals.h"
#include "CIMGF.h"
#include "GUI/Window/CWindowManager.h"
#include "GUI/Windows/CMainWindow.h"
#include "GUI/Layer/ELayers.h"
#include "GUI/Layer/EMainMenuType.h"
#include "Task/CTaskManager.h"
#include "Task/CTaskDispatchManager.h"

using namespace bxgx::control::events;
using namespace imgf::layers;
using namespace imgf::mainLayer::buttons;
using namespace imgf::mainLayer::mainMenuType;

// main interface
void					CButtonPressManager::init(void)
{
	m_pMainWindow = g_pIMGF->getWindowManager()->getMainWindow();
	m_pTaskDispatchManager = g_pIMGF->getTaskManager()->getDispatch();

	bindEvents();
}

// bind events
void					CButtonPressManager::bindEvents(void)
{
	bindEvent(PRESS_BUTTON, &CButtonPressManager::onPressButton);
}

// forward button press
void					CButtonPressManager::onPressButton(CButtonControl *pButton)
{
	switch (pButton->getId())
	{
	case EButtons::FORMATS:	return formats();
	case EButtons::UTILITY:	return utility();

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

	case SETTINGS:			return settings();
	}
}

// button press - menu type menu
void					CButtonPressManager::formats(void)
{
	m_pMainWindow->setMainMenuType(EMainMenuType::FORMATS);
}

void					CButtonPressManager::utility(void)
{
	m_pMainWindow->setMainMenuType(EMainMenuType::UTILITY);
}

// button press - format menu
void					CButtonPressManager::dat(void)
{
}

void					CButtonPressManager::img(void)
{
}

void					CButtonPressManager::itemDefinition(void)
{
}

void					CButtonPressManager::itemPlacement(void)
{
}

void					CButtonPressManager::models(void)
{
}

void					CButtonPressManager::collisions(void)
{
}

void					CButtonPressManager::textures(void)
{
}

void					CButtonPressManager::animations(void)
{
}

void					CButtonPressManager::radar(void)
{
}

// button press - file menu
void					CButtonPressManager::open(void)
{
	m_pTaskDispatchManager->chooseFilesToOpen();
}

void					CButtonPressManager::close(void)
{
}

void					CButtonPressManager::save(void)
{
}

// button press - action menu
void					CButtonPressManager::_import(void)
{
}

void					CButtonPressManager::_export(void)
{
}

void					CButtonPressManager::quickExport(void)
{
}

void					CButtonPressManager::rename(void)
{
}

void					CButtonPressManager::replace(void)
{
}

void					CButtonPressManager::remove(void)
{
}

void					CButtonPressManager::merge(void)
{
}

void					CButtonPressManager::split(void)
{
}

void					CButtonPressManager::convert(void)
{
}

void					CButtonPressManager::select(void)
{
}

void					CButtonPressManager::sort(void)
{
}

void					CButtonPressManager::lst(void)
{
}

// settings
void					CButtonPressManager::settings(void)
{
	CGUILayer *pLayer = m_pMainWindow->getLayerById(SETTINGS_MENU);
	pLayer->setEnabled(!pLayer->isEnabled());
}