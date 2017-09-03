#pragma warning(disable : 4005)

#include "DropTarget.h"
#include "Static/String2.h"
#include "Globals.h"
#include "IMGF.h"
#include "GUI/Editors/IMGEditor.h"
#include "Static/Path.h"
#include "Static/Input.h"
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
#include "IMGF.h"
#include "GUI/Popups/PopupGUIManager.h"
#include "Image/RasterDataFormat.h"
#include "Localization/LocalizationManager.h"
#include "Static/Debug.h"
#include <string>

using namespace std;
using namespace bxcf;
using namespace imgf;

