#pragma warning(disable : 4005)

#include "CDropTarget.h"
#include "Static/CString2.h"
#include "Globals.h"
#include "CIMGF.h"
#include "GUI/Editors/CIMGEditor.h"
#include "Static/CPath.h"
#include "Static/CInput.h"
#include "Format/IMG/Regular/CIMGEntry.h"
#include "Format/TXD/CTXDManager.h"
#include "Format/TXD/CTXDFormat.h"
#include "Format/DFF/CDFFManager.h"
#include "Format/DFF/CDFFFormat.h"
#include "Format/COL/CCOLManager.h"
#include "Format/COL/CCOLFormat.h"
#include "Format/COL/CCOLVersion.h"
#include "Engine/RW/CRWManager.h"
#include "Engine/RW/CRWVersionManager.h"
#include "CIMGF.h"
#include "GUI/Popups/CPopupGUIManager.h"
#include "Image/CRasterDataFormat.h"
#include "Localization/CLocalizationManager.h"
#include "Static/CDebug.h"
#include <string>

using namespace std;
using namespace bxcf;

