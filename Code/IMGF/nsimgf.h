#pragma once

#include "Type/Types.h"

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

	class AutomatedTesting;
	
	class DragDrop;
	struct DraggableFile;
	class DragListCtrl;
	class DropSource;
	class DropTarget;

	class CollisionViewer;
	class EntryViewer;
	class EntryViewerManager;
	class TextureViewer;
	struct TextureViewerTextureData;
	enum EEntryViewerDisplayType;

	enum EEvent;

	class DBEntry;
	class DBFormat;
	class DBManager;

	class LSTEntry;
	class LSTFormat;
	class LSTManager;
	class LSTSection;

	class EditorTab;
	class Editor;

	class IMGEditorTab;
	class IMGEditor;
	class TextureEditor;

	class InputManager;

	class MainLayer;
	class MainLayerNoTabsOpen;

	class IDEInputLayer;
	struct IDEInputWindowResult;
	class IPLInputLayer;
	struct IPLInputWindowResult;

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

	class DumpManager;
	
	struct FilterOptions;
	
	class SearchEntry;
	
	class LSTProcessingManager;
	
	class RecentlyOpenEntry;
	class RecentlyOpenManager;

	struct RenamedIMGEntry;

	class Session;
	class SessionManager;

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