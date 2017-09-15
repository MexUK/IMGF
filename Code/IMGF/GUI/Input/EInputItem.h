#pragma once

#include "nsimgf.h"

enum imgf::mainLayer::input::EInputItem
{
	FORMATS,
	UTILITY,

	DAT,
	IMG,
	ITEM_DEFINITION,
	ITEM_PLACEMENT,
	MODELS,
	COLLISIONS,
	TEXTURES,
	ANIMATIONS,
	RADAR,

	NEW,
	OPEN_FILES,
	OPEN_FOLDER,
	OPEN_FOLDER_RECURSIVELY,
	CLOSE_FILE,
	CLOSE_ALL_FILES,
	SAVE_FILE,
	SAVE_FILE_AS,
	SAVE_ALL_FILES,

	IMPORT_BY_FILES,
	IMPORT_BY_SINGLE_FOLDER,
	IMPORT_BY_FOLDER_RECURSIVELY,

	EXPORT_SELECTED,
	EXPORT_ALL,
	EXPORT_BY_INDEX,
	EXPORT_BY_NAME,
	EXPORT_BY_OFFSET,
	EXPORT_BY_SIZE,
	EXPORT_BY_TYPE,
	EXPORT_BY_VERSION,
	EXPORT_ALL_INTO_GROUPED_FOLDERS_BY_TYPE,
	EXPORT_ALL_FROM_ALL_TABS,
	EXPORT_ALL_FROM_ALL_TABS_INTO_GROUPED_FOLDERS_BY_TYPE,
	EXPORT_SELECTION_FROM_ALL_TABS,
	EXPORT_BY_IDE,

	RENAME,

	REPLACE_BY_FILES,
	REPLACE_BY_SINGLE_FOLDER,
	REPLACE_BY_FOLDER_RECURSIVELY,
	REPLACE_BY_IDE,

	REMOVE_SELECTED,
	REMOVE_ALL,
	REMOVE_BY_INDEX,
	REMOVE_BY_NAME,
	REMOVE_BY_OFFSET,
	REMOVE_BY_SIZE,
	REMOVE_BY_TYPE,
	REMOVE_BY_VERSION,
	REMOVE_BY_IDE,

	MERGE,
	SPLIT,

	CONVERT_IMG_VERSION,

	SELECT_ALL,
	UNSELECT_ALL,
	SELECT_INVERSE,
	SELECT_BY_INDEX,
	SELECT_BY_NAME,
	SELECT_BY_OFFSET,
	SELECT_BY_SIZE,
	SELECT_BY_TYPE,
	SELECT_BY_VERSION,
	SELECT_BY_IDE,
	UNSELECT_BY_INDEX,
	UNSELECT_BY_NAME,
	UNSELECT_BY_OFFSET,
	UNSELECT_BY_SIZE,
	UNSELECT_BY_TYPE,
	UNSELECT_BY_VERSION,
	UNSELECT_BY_IDE,

	SORT_BY_INDEX_REVERSE,
	SORT_BY_NAME_ASCENDING_09AZ,
	SORT_BY_NAME_ASCENDING_AZ09,
	SORT_BY_NAME_DESCENDING_ZA90,
	SORT_BY_NAME_DESCENDING_90ZA,
	SORT_BY_OFFSET_LOW_HIGH,
	SORT_BY_OFFSET_HIGH_LOW,
	SORT_BY_SIZE_SMALL_BIG,
	SORT_BY_SIZE_BIG_SMALL,
	SORT_BY_TYPE_AZ,
	SORT_BY_TYPE_ZA,
	SORT_BY_VERSION_OLD_NEW,
	SORT_BY_VERSION_NEW_OLD,

	LST,

	SETTINGS
};