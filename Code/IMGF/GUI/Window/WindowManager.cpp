#include "WindowManager.h"
#include "nsbxgx.h"
#include "BXGX.h"
#include "GUI/Window/Windows/MainWindow/MainWindow.h"
#include "GUI/Editor/Editors/IMGEditor.h"
#include "../../Compiler/Projects/IMGF/resource.h"
#include "GUI/Layer/Layers/IDEInputWindow/IDEInputLayer.h"
#include "Control/Controls/Button.h"
#include "Control/Controls/CheckBox.h"
#include "Control/Controls/Text.h"
#include "Static/Input.h"
#include <string>

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace bxgx::events;
using namespace imgf;

WindowManager::WindowManager(void) :
	m_pMainWindow(nullptr),
	m_bWindow2Cancelled(true)
{
	m_ideInputWindowResult = IDEInputWindowResult();
}

// main interface
void					WindowManager::init(void)
{
}

void					WindowManager::uninit(void)
{
}

// window open/close
MainWindow*				WindowManager::openWindow(void)
{
	LPWSTR pIcon = MAKEINTRESOURCE(IDI_ICON1);
	uint32 uiIcon = (uint32) pIcon;

	m_pMainWindow = bxgx::get()->addWindow<MainWindow>(-1, -1, 1300, 700, uiIcon);
	if (!m_pMainWindow)
	{
		return nullptr;
	}

	return m_pMainWindow;
}

// window processing
void					WindowManager::process(void)
{
	bxgx::get()->process();
}

// window input
void					WindowManager::onPressButton_IDEInputWindow(Button *pButton)
{
	Window
		*pWindow1 = BXGX::get()->getEntryByIndex(0),
		*pWindow2 = BXGX::get()->getEntryByIndex(1);

	if (pButton->getId() == 100)
	{
		// Select all
		for (uint32 uiCheckBoxId = 300; uiCheckBoxId <= 500; uiCheckBoxId++)
		{
			LayerItem *pLayerItem = pWindow2->getItemById(uiCheckBoxId);
			if (pLayerItem)
			{
				CheckBox *pCheckBox = (CheckBox*)pLayerItem;
				pCheckBox->setMarked(true);
			}
		}
		return;
	}
	else if (pButton->getId() == 110)
	{
		// Unselect all
		for (uint32 uiCheckBoxId = 300; uiCheckBoxId <= 500; uiCheckBoxId++)
		{
			LayerItem *pLayerItem = pWindow2->getItemById(uiCheckBoxId);
			if (pLayerItem)
			{
				CheckBox *pCheckBox = (CheckBox*)pLayerItem;
				pCheckBox->setMarked(false);
			}
		}
		return;
	}
	else if (pButton->getId() == 200)
	{
		// OK
		bool bAtLeastOneCheckBoxIsMarked = false;
		for (uint32 uiCheckBoxId = 300; uiCheckBoxId <= 500; uiCheckBoxId++)
		{
			LayerItem *pLayerItem = pWindow2->getItemById(uiCheckBoxId);
			if (pLayerItem)
			{
				CheckBox *pCheckBox = (CheckBox*)pLayerItem;
				if (pCheckBox->isMarked())
				{
					bAtLeastOneCheckBoxIsMarked = true;
					break;
				}
			}
		}
		if (!bAtLeastOneCheckBoxIsMarked)
		{
			Input::showMessage("At least one check box must be marked.", "Input Error", MB_OK);
			return;
		}
		else
		{
			m_bWindow2Cancelled = false;

			for (uint32 uiCheckBoxId = 300; uiCheckBoxId <= 500; uiCheckBoxId++)
			{
				LayerItem *pLayerItem = pWindow2->getItemById(uiCheckBoxId);
				if(pLayerItem)
				{
					CheckBox *pCheckBox = (CheckBox*)pLayerItem;
					m_ideInputWindowResult.m_umapCheckBoxStatuses[uiCheckBoxId] = pCheckBox->isMarked();
				}
			}
		}
	}

	BXGX::get()->m_vecWindowsToDestroy.push_back(pWindow2);
}

// windows
IDEInputWindowResult	WindowManager::showIDEInputWindow(string strWindowTitle, string strDisplayedText)
{
	m_bWindow2Cancelled = true;

	Window *pWindow = BXGX::get()->addWindow(500, 460);
	IDEInputLayer *pLayer = pWindow->addLayer<IDEInputLayer>();
	pLayer->init();

	pWindow->addTitleBar(strWindowTitle);
	pLayer->m_pText->setText(strDisplayedText);

	pWindow->render();

	bindEvent(PRESS_BUTTON, &WindowManager::onPressButton_IDEInputWindow);
	while (BXGX::get()->m_vecWindowsToInitialize.size() > 0 || BXGX::get()->getEntryCount() > 1)
	{
		BXGX::get()->process2ndThreadOnce();
	}
	unbindEvent(PRESS_BUTTON, &WindowManager::onPressButton_IDEInputWindow);

	return m_ideInputWindowResult;
}