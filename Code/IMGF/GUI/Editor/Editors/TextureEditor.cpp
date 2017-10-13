#include "TextureEditor.h"
#include "GUI/Window/Windows/MainWindow/MainWindow.h"
#include "BXGX.h"
#include "GraphicsLibrary/Base/GraphicsLibrary.h"
#include "Style/Parts/EStyleStatus.h"

using namespace bxcf;
using namespace bxgx;
using namespace bxgx::styles::statuses;
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

	// add horizontal lines for texture preview panel
	uint32
		uiTexturePanelBoxHeight = 100,
		uiDisplayedTextureCount = (m_pMainWindow->getSize().y - starty) / uiTexturePanelBoxHeight;

	y = starty;
	y2 = y;

	addRectangle(startx, starty, 250, uiDisplayedTextureCount * 55, "itemList");

	void *pTexture;
	for (uint32 i = 0; i < uiDisplayedTextureCount; i++)
	{
		pTexture = nullptr;
		/*
		if (pTexture == m_pActiveTexture)
		{
			setRenderingStyleStatus(ACTIVE);
		}
		else
		{
			setRenderingStyleStatus(DEFAULT_STYLE_STATUS);
		}
		*/

		x = startx;
		x2 = startx + 250;

		addLine(x, y, x2, y2);

		addText(x, y + (55 / 2), 50, 25, String::toString(i + 1));

		y += uiTexturePanelBoxHeight;
		y2 += uiTexturePanelBoxHeight;
	}

	/*
	// add vertical line for texture preview panel
	x = startx + 150;
	y = starty;

	x2 = x;
	y2 = m_pMainWindow->getSize().y;

	addLine(x, y, x2, y2);
	*/
}

void						TextureEditor::render(void)
{
	GraphicsLibrary *pGFX = BXGX::get()->getGraphicsLibrary();

	/*
	todo

	int32 x, y, x2, y2;
	
	// draw right line
	x = 139 + 139;
	y = 162 + 30;

	x2 = x;
	y2 = m_pMainWindow->getSize().y - y;

	pGFX->drawLine(Vec2i(x, y), Vec2i(x2, y2));
	*/
}