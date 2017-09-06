#include "InputManager.h"
#include "GUI/Input/EInputItem.h"
#include "Control/Controls/Button.h"
#include "Control/Entries/MenuItem.h"
#include "Globals.h"
#include "IMGF.h"
#include "GUI/Window/WindowManager.h"
#include "GUI/Window/Windows/MainWindow/MainWindow.h"
#include "GUI/Layer/Layers/ELayer.h"
#include "GUI/Layer/Layers/MainMenu/EMainMenuType.h"
#include "Task/TaskManager.h"
#include "Task/Tasks/Tasks.h"

using namespace bxgx;
using namespace bxgx::events;
using namespace imgf;
using namespace imgf::layers;
using namespace imgf::mainLayer::input;
using namespace imgf::mainLayer::mainMenuType;

// main interface
void					InputManager::init(void)
{
	m_pMainWindow = g_pIMGF->getWindowManager()->getMainWindow();
	m_pTasks = g_pIMGF->getTaskManager()->getDispatch();

	bindEvents();
}

// bind events
void					InputManager::bindEvents(void)
{
	bindEvent(PRESS_BUTTON, &InputManager::onPressButton);
	bindEvent(PRESS_MENU_ITEM, &InputManager::onPressMenuItem);
}

// forward button press
void					InputManager::onPressButton(Button *pButton)
{
	switch (pButton->getId())
	{
	case SETTINGS:			return settings();
	}
}

// forward button press
void					InputManager::onPressMenuItem(MenuItem *pMenuItem)
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

	case SELECT_ALL:		return selectAll();
	case UNSELECT_ALL:		return unselectAll();
	case SELECT_INVERSE:	return selectInverse();
	}
}

// button press - menu type menu
void					InputManager::formats(void)
{
	m_pMainWindow->setMainMenuType(EMainMenuType::FORMATS);
}

void					InputManager::utility(void)
{
	m_pMainWindow->setMainMenuType(EMainMenuType::UTILITY);
}

// button press - format menu
void					InputManager::dat(void)
{
}

void					InputManager::img(void)
{
}

void					InputManager::itemDefinition(void)
{
}

void					InputManager::itemPlacement(void)
{
}

void					InputManager::models(void)
{
}

void					InputManager::collisions(void)
{
}

void					InputManager::textures(void)
{
}

void					InputManager::animations(void)
{
}

void					InputManager::radar(void)
{
}

// button press - file menu
void					InputManager::open(void)
{
	m_pTasks->chooseFilesToOpen();
}

void					InputManager::close(void)
{
	m_pTasks->closeActiveFile();
}

void					InputManager::save(void)
{
}

// button press - action menu
void					InputManager::_import(void)
{
}

void					InputManager::_export(void)
{
}

void					InputManager::quickExport(void)
{
}

void					InputManager::rename(void)
{
}

void					InputManager::replace(void)
{
}

void					InputManager::remove(void)
{
}

void					InputManager::merge(void)
{
}

void					InputManager::split(void)
{
}

void					InputManager::convert(void)
{
}

void					InputManager::selectAll(void)
{
	m_pTasks->selectAll();
}

void					InputManager::unselectAll(void)
{
	m_pTasks->unselectAll();
}

void					InputManager::selectInverse(void)
{
	m_pTasks->selectInverse();
}

void					InputManager::sort(void)
{
}

void					InputManager::lst(void)
{
}

// settings
void					InputManager::settings(void)
{
	Layer *pLayer = m_pMainWindow->getLayerById(SETTINGS_MENU);
	pLayer->setEnabled(!pLayer->isEnabled());
}