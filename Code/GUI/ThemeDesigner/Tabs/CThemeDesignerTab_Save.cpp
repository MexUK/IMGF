#include "CThemeDesignerTab_Save.h"
#include "Math/CMath.h" // todo - check if all these includes are needed
#include "Event/CEventManager.h"
#include "Event/eEvent.h"
#include "GUI/CGUIManager.h"
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
#include "Type/Vector/CColour.h"
#include "CIMGF.h"
#include "GUI/ThemeDesigner/CThemeDesigner.h"
#include "GUI/CGUIManager.h"
#include "File/CFileManager.h"
#include "Controls/CButtonControl.h"
#include "Controls/CEditControl.h"
#include "Stream/CDataWriter.h"

using namespace std;
using namespace mcore;

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
		string strDefaultFileName = ((CEditControl*)pButton->getLayer()->getControlById(10))->getTextLines()[0] + "." + strExtensionFilter;
		string strFilePath = mcore::CGUIManager::saveFileDialog(strInitialDir, strExtensionFilter, strDefaultFileName);
		if (strFilePath == "")
		{
			return;
		}

		CWindow *pMainWindow = gui::CGUIManager::getInstance()->getEntryByIndex(1);
		pMainWindow->serialize();

		CFileManager::storeFile(strFilePath, CDataWriter::getInstance()->getData(), false, true);
	}
}

// design
void									CThemeDesignerTab_Save::initDesign(void)
{
	CThemeDesigner *pThemeDesigner = getThemeDesigner();

	CGUILayer *pLayer = pThemeDesigner->addLayer("save", false);

	CGUIStyles
		*pStyles_GoldBorder = gui::CGUIManager::createStyles(),
		*pStyles_GoldText = gui::CGUIManager::createStyles(),
		*pStyles_SaveButton = gui::CGUIManager::createStyles();

	pStyles_GoldBorder->setStyle("border-colour", CColour(230, 223, 12));
	pStyles_GoldText->setStyle("text-colour", CColour(230, 223, 12));

	//pStyles_SaveButton->setStyle("text-align-x", "center");
	//pStyles_SaveButton->setStyle("text-align-y", "center");
	pStyles_SaveButton->setStyle("border-colour", CColour(230, 223, 12));
	pStyles_SaveButton->setStyle("text-colour", CColour(230, 223, 12));

	CGUIControl *pControl = nullptr;
	pControl = (CGUIControl*) pLayer->addText(CPoint2D((int32) 20, 50), CSize2D(150, 30), "Theme Name", pStyles_GoldText);
	pControl = (CGUIControl*) pLayer->addEdit(CPoint2D((int32) 20, 80), CSize2D(400, 30), "", false, pStyles_GoldBorder);
	pControl->setControlId(10);
	pControl = (CGUIControl*) pLayer->addButton(CPoint2D((int32) 20, 400), CSize2D(80, 30), "Save", pStyles_SaveButton);
}