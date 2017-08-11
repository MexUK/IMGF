#include "CThemeDesignerTab_Save.h"
#include "Math/CMath.h" // todo - check if all these includes are needed
#include "Event/CEventManager.h"
#include "Event/eEvent.h"
#include "Input/CInputManager.h"
#include "Styles/CGUIStyles.h"
#include "Shapes/CRectangleShape.h"
#include "Shapes/Geometries/CGUIShapeGeometry_1xPoint_1x1DSize.h"
#include "Shapes/Geometries/CGUIShapeGeometry_1xPoint_1x2DSize.h"
#include "Shapes/Geometries/CGUIShapeGeometry_2xPoints.h" // todo - rename Point to Points
#include "Shapes/Geometries/CGUIShapeGeometry_3xPoints.h" // todo - rename Point to Points
#include "Shapes/Geometries/CGUIShapeGeometry_NxPoints.h" // todo - rename Point to Points
#include "Controls/CCheckControl.h"
#include "Controls/CProgressControl.h"
#include "Controls/CRadioControl.h"
#include "Controls/CDropControl.h"
#include "GUI/ThemeDesigner/CThemeDesigner.h"
#include "Type/Colour/CColour.h"
#include "CIMGF.h"
#include "GUI/ThemeDesigner/CThemeDesigner.h"
#include "Input/CInputManager.h"
#include "File/CFileManager.h"
#include "Controls/CButtonControl.h"
#include "Controls/CTextBoxControl.h"
#include "Stream/CDataWriter.h"

using namespace std;
using namespace bxcf;

auto pOnPressButton		= [](void *pThemeDesigner, void *pTriggerArg) { ((CThemeDesignerTab_Save*) pThemeDesigner)->onPressButton((CButtonControl*) pTriggerArg); };

CThemeDesignerTab_Save::CThemeDesignerTab_Save(CThemeDesigner *pThemeDesigner) :
	CThemeDesignerTab(pThemeDesigner)
{
}

// event binding
void									CThemeDesignerTab_Save::bindEvents(void)
{
	CThemeDesigner *pThemeDesigner = getThemeDesigner();

	pThemeDesigner->getWindow()->bindEvent(EVENT_onPressButton, pOnPressButton, this);
}

// input
void									CThemeDesignerTab_Save::onPressButton(CButtonControl *pButton)
{
	if (pButton)
	{
		string strInitialDir = "";
		string strExtensionFilter = "imgf-theme";
		string strDefaultFileName = ((CTextBoxControl*)pButton->getLayer()->getControlById(10))->getTextLines()[0] + "." + strExtensionFilter;
		string strFilePath = bxcf::CInputManager::saveFileDialog(strInitialDir, strExtensionFilter, strDefaultFileName);
		if (strFilePath == "")
		{
			return;
		}

		CWindow *pMainWindow = bxgx::CGUIManager::get()->getEntryByIndex(1);
		pMainWindow->serialize();

		CFileManager::storeFile(strFilePath, CDataWriter::get()->getData(), false, true);
	}
}

// design
void									CThemeDesignerTab_Save::initDesign(void)
{
	/*
	CThemeDesigner *pThemeDesigner = getThemeDesigner();

	CGUILayer *pLayer = pThemeDesigner->addLayer("save", false);

	CGUIStyles
		*pStyles_GoldBorder = bxgx::CGUIManager::createStyles(),
		*pStyles_GoldText = bxgx::CGUIManager::createStyles(),
		*pStyles_SaveButton = bxgx::CGUIManager::createStyles();

	pStyles_GoldBorder->setStyle("border-colour", CColour(230, 223, 12));
	pStyles_GoldText->setStyle("text-colour", CColour(230, 223, 12));

	//pStyles_SaveButton->setStyle("text-align-x", "center");
	//pStyles_SaveButton->setStyle("text-align-y", "center");
	pStyles_SaveButton->setStyle("border-colour", CColour(230, 223, 12));
	pStyles_SaveButton->setStyle("text-colour", CColour(230, 223, 12));

	CGUIControl *pControl = nullptr;
	pControl = (CGUIControl*) pLayer->addText(Vec2i((int32) 20, 50), Vec2u(150, 30), "Theme Name", pStyles_GoldText);
	pControl = (CGUIControl*) pLayer->addTextBox(Vec2i((int32) 20, 80), Vec2u(400, 30), "", false, pStyles_GoldBorder);
	pControl->setControlId(10);
	pControl = (CGUIControl*) pLayer->addButton(Vec2i((int32) 20, 400), Vec2u(80, 30), "Save", pStyles_SaveButton);
	*/
}