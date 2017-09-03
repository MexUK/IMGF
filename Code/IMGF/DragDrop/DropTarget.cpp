#pragma warning(disable : 4005)

#include "DropTarget.h"
#include "Static/String2.h"
#include "Globals.h"
#include "IMGF.h"
#include "GUI/Editors/IMGEditor.h"
#include "Static/Path.h"
#include "Static/Input.h"
#include "Format/IMG/Regular/IMGEntry.h"
#include "Format/TXD/TXDManager.h"
#include "Format/TXD/TXDFormat.h"
#include "Format/DFF/DFFManager.h"
#include "Format/DFF/DFFFormat.h"
#include "Format/COL/COLManager.h"
#include "Format/COL/COLFormat.h"
#include "Format/COL/COLVersion.h"
#include "Engine/RW/RWManager.h"
#include "Engine/RW/RWVersionManager.h"
#include "IMGF.h"
#include "GUI/Popups/PopupGUIManager.h"
#include "Image/RasterDataFormat.h"
#include "Localization/LocalizationManager.h"
#include "Static/Debug.h"
#include <string>

using namespace std;
using namespace bxcf;
using namespace imgf;

