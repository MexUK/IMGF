#include "TextureEditor.h"
#include "GUI/Window/WindowManager.h"
#include "GUI/Window/Windows/MainWindow/MainWindow.h"
#include "GUI/Editor/Editors/Tab/TextureEditorTab.h"
#include "GUI/Layer/Layers/MainLayer/MainLayer.h"
#include "GUI/Layer/Layers/MainLayer/MainLayerNoTabsOpen.h"
#include "BXGX.h"
#include "GraphicsLibrary/Base/GraphicsLibrary.h"
#include "Style/Parts/EStyleStatus.h"
#include "Format/TXD/TXDManager.h"
#include "Format/TXD/TXDFormat.h"
#include "Static/Path.h"
#include "IMGF.h"

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace bxgx::styles::statuses;
using namespace bxgx::events;
using namespace bxgi;
using namespace imgf;

TextureEditor::TextureEditor(void) :
	m_pActiveTexture(nullptr)
{
	setEditorFileFormats({ "TXD" });
}

// initialization
void						TextureEditor::init(void)
{
	Editor::init();

	int32 startx, starty, x, y, x2, y2;
	uint32 uiLogWidth = 335;

	startx = 139 + 139;
	starty = 162 + 30;

	// add top horizontal line
	x = startx;
	y = starty;

	x2 = x + (m_pMainWindow->getSize().x - uiLogWidth - startx);
	y2 = y;

	addLine(x, y, x2, y2);

	/*
	// add vertical line for texture preview panel
	x = startx + 150;
	y = starty;

	x2 = x;
	y2 = m_pMainWindow->getSize().y;

	addLine(x, y, x2, y2);
	*/
}

// events
void						TextureEditor::bindEvents(void)
{
	bindEvent(BEFORE_RENDER, &TextureEditor::renderBefore);

	Editor::bindEvents();
	Layer::bindEvents();

	if (m_pActiveEditorTab)
	{
		m_pActiveEditorTab->bindEvents();
	}
}

void						TextureEditor::unbindEvents(void)
{
	unbindEvent(BEFORE_RENDER, &TextureEditor::renderBefore);

	Editor::unbindEvents();
	Layer::unbindEvents();

	if (m_pActiveEditorTab)
	{
		m_pActiveEditorTab->unbindEvents();
	}
}

// render
void						TextureEditor::renderBefore(void)
{
	GraphicsLibrary *pGFX = BXGX::get()->getGraphicsLibrary();
	
	if (m_pMainWindow->getActiveEditor() != m_pMainWindow->getTextureEditor() || BXGX::get()->getEventWindow() != m_pMainWindow)
	{
		return;
	}

	m_pWindow->resetRenderingStyleGroups();
	m_pWindow->resetRenderingControlComponent();
	m_pWindow->resetRenderingStyleFragment();
	m_pWindow->resetRenderingStyleStatus();

	/*
	int32 startx, starty, x, y, x2, y2;
	uint32 uiLogWidth = 335;

	startx = 139 + 139;
	starty = 162 + 30;

	// add horizontal lines for texture preview panel
	uint32
		uiTexturePanelBoxWidth = 250,
		uiTexturePanelBoxHeight = 55,
		uiDisplayedTextureCount = (m_pMainWindow->getSize().y - starty) / uiTexturePanelBoxHeight;

	y = starty;
	y2 = y;

	
	// draw item list
	setRenderingStyleGroups("itemList");
	StyleManager::get()->m_pRenderingEventUtilizer = nullptr;
	setRenderingStyleStatus(DEFAULT_STYLE_STATUS);
	pGFX->drawRectangle(Vec2i(startx, starty), Vec2u(uiTexturePanelBoxWidth, uiDisplayedTextureCount * uiTexturePanelBoxHeight));

	void *pTexture;
	for (uint32 i = 0; i < uiDisplayedTextureCount; i++)
	{
		pTexture = nullptr;

		x = startx;
		x2 = startx + 250;

		if (pTexture == m_pActiveTexture)
		{
			setRenderingStyleStatus(ACTIVE);
			pGFX->drawRectangle(Vec2i(x, y), Vec2u(uiTexturePanelBoxWidth, uiTexturePanelBoxHeight));
		}
		else
		{
			setRenderingStyleStatus(DEFAULT_STYLE_STATUS);
		}

		pGFX->drawLine(Vec2i(x, y), Vec2i(x2, y2));

		pGFX->drawText(Vec2i(x, y + (uiTexturePanelBoxHeight / 2)), Vec2u(50, 25), String::toString(i + 1));

		y += uiTexturePanelBoxHeight;
		y2 += uiTexturePanelBoxHeight;
	}
	*/

	if (m_pActiveEditorTab)
	{
		((TextureEditorTab*)m_pActiveEditorTab)->renderDisplayType_Single();
	}
}

// add editor tab
TextureEditorTab*				TextureEditor::addEditorTab(string& strFilePath)
{
	TXDFormat txdFormat(strFilePath);
	if(!txdFormat.readMetaData())
	{
		return nullptr;
	}

	TextureEditorTab *pTextureEditorTab = Editor::addEditorTab<TXDFormat, TextureEditorTab>(strFilePath);

	if (pTextureEditorTab)
	{
		//pTextureEditorTab->setTextureEditor(this);
		//pTextureEditorTab->setTextureFile((TXDFormat*)pTextureEditorTab->getFile());
		pTextureEditorTab->init();
	}
	return pTextureEditorTab;
}