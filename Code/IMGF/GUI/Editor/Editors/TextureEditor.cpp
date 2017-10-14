#include "TextureEditor.h"
#include "GUI/Window/Windows/MainWindow/MainWindow.h"
#include "BXGX.h"
#include "GraphicsLibrary/Base/GraphicsLibrary.h"
#include "Style/Parts/EStyleStatus.h"

using namespace bxcf;
using namespace bxgx;
using namespace bxgx::styles::statuses;
using namespace bxgx::events;
using namespace imgf;

TextureEditor::TextureEditor(void) :
	m_pActiveTexture(nullptr)
{
}

void						TextureEditor::init(void)
{
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

	bindEvent(RENDER, &TextureEditor::render);
}

void						TextureEditor::render(void)
{
	GraphicsLibrary *pGFX = BXGX::get()->getGraphicsLibrary();
	
	if (BXGX::get()->getEventWindow() != m_pMainWindow)
	{
		return;
	}

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
}