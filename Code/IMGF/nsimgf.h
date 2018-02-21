#pragma once

#include "Type/Types.h"
//#include "GL/glew.h"
//#include "GL/wglew.h"

#include <Windows.h>
#include <unknwn.h>
#include <Gdiplus.h>

#include <algorithm>
namespace Gdiplus
{
	using std::min;
	using std::max;
}

/*
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
*/

namespace imgf
{
	namespace layers
	{
		enum ELayer;
	};

	namespace editor
	{
		namespace items
		{
			enum EEditorItem;
		};
	};

	namespace mainLayer
	{
		namespace input
		{
			enum EInputItem;
		};

		namespace mainMenuType
		{
			enum EMainMenuType;
		};
	};

	namespace task
	{
		enum ETask;
	};

	enum EEvent;

	class DBEntry;
	class DBFormat;
	class DBManager;

	class LSTEntry;
	class LSTFormat;
	class LSTManager;
	class LSTSection;



	enum EEditor;

	class Editor;
	class EditorTab;

	class DATEditor;
	class IMGEditor;
	class ItemDefinitionEditor;
	class ItemPlacementEditor;
	class ModelEditor;
	class CollisionEditor;
	class TextureEditor;
	class AnimationEditor;
	class RadarEditor;
	class MapEditor;
	class CarColsDATEditor;

	class _3DEditorTab;
	class LeftEntryList;

	class DATEditorTab;
	class IMGEditorTab;
	class ItemDefinitionEditorTab;
	class ItemPlacementEditorTab;
	class ModelEditorTab;
	class CollisionEditorTab;
	class TextureEditorTab;
	class AnimationEditorTab;
	class RadarEditorTab;
	class MapEditorTab;
	class CarColsDATEditorTab;

	struct TextureEditorTabEntry;
	struct RadarEditorTabEntry;


	class InputManager;

	class MainLayer;
	class MainLayerNoTabsOpen;

	class IDEInputLayer;
	struct IDEInputWindowResult;
	class IPLInputLayer;
	struct IPLInputWindowResult;
	class SettingsWindowLayer;
	class FormatsWindowLayer;
	class WebsitesWindowLayer;
	class AboutWindowLayer;
	class DumpWindowLayer;
	class SessionManagerWindowLayer;
	class RenamerWindowLayer;
	class TXDBuilderWindowLayer;
	class TXDOrganizerWindowLayer;
	class DATPathsMoverWindowLayer;
	class MapMoverAndIDShifterWindowLayer;
	struct DumpWindowResult;
	struct DATPathsMoverWindowResult;
	struct MapMoverAndIDShifterWindowResult;
	struct TXDOrganizerWindowResult;
	struct TXDBuilderWindowResult;
	struct RenamerWindowResult;

	class WindowManager;

	class MainWindow;

	class Language;
	class LanguageManager;

	class BuildMeta;

	class SettingsManager;

	class AppDataPath;

	class LastUsedValueManager;
	class Tasks;
	class TaskDurationManager;
	class TaskManager;
	class Task;

	class DumpManager;
	
	struct FilterOptions;
	
	class SearchEntry;
	
	class LSTProcessingManager;
	
	class RecentlyOpenEntry;
	class RecentlyOpenManager;

	struct RenamedIMGEntry;

	class FileGroup;
	class FileGroupManager;

	class SortManager;
	class SortMenuItem;
	class SortMenuItems;
	class SortPriorities;
	class SortPriority;
	class SortType;
	class SortTypes;
	enum ESortType;

	class UpdateConnection;
	class UpdateConnectionManager;
	class UpdateManager;
	class ExeBuild;

	class IMGF;
};