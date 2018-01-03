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
#include "Format/WTD/WTDManager.h"
#include "Static/Path.h"
#include "IMGF.h"
#include "Engine/RW/RWManager.h"
#include "Engine/RW/RWVersionManager.h"
#include "GUI/Editor/EEditor.h"

using namespace std;
using namespace bxcf;
using namespace bxcf::fileType;
using namespace bxgx;
using namespace bxgx::events;
using namespace bxgx::styles::statuses;
using namespace bxgi;
using namespace imgf;

TextEditor::TextEditor(void) :
	
}