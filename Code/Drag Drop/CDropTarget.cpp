#pragma warning(disable : 4005)

#include "CDropTarget.h"
#include "Type/String/CString2.h"
#include "Globals.h"
#include "CIMGF.h"
#include "GUI/Editors/CIMGEditor.h"
#include "Path/CPathManager.h"
#include "GUI/CGUIManager.h"
#include "Format/RockstarGames/IMG/CIMGEntry.h"
#include "Format/RockstarGames/TXD/CTXDManager.h"
#include "Format/RockstarGames/TXD/CTXDFormat.h"
#include "Format/RockstarGames/DFF/CDFFManager.h"
#include "Format/RockstarGames/DFF/CDFFFormat.h"
#include "Format/RockstarGames/COL/CCOLManager.h"
#include "Format/RockstarGames/COL/CCOLFormat.h"
#include "Format/RockstarGames/COL/CCOLVersion.h"
#include "Format/RenderWare/Helper/BinaryStream/CRWManager.h"
#include "Format/RenderWare/Helper/BinaryStream/CRWVersionManager.h"
#include "CIMGF.h"
#include "CPopupGUIManager.h"
#include "Image/CRasterDataFormat.h"
#include "Localization/CLocalizationManager.h"
#include "Debug/CDebug.h"
#include <string>

using namespace std;
using namespace mcore;

