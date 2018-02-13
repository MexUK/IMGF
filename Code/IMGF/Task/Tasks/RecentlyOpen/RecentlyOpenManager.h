#pragma once

#include "nsimgf.h"
#include "Object/Manager.h"
#include "RecentlyOpenEntry.h"
#include "Pool/VectorPool.h"
#include "Event/EventBindable.h"
#include <string>
#include <unordered_map>

class imgf::RecentlyOpenManager : public bxcf::Manager, public bxcf::EventBindable
{
public:
	void					init(void);
	void					uninit(void);

	void					onToolReady(void);

	void					loadRecentlyOpenEntries(EEditor uiEditor);
	void					unloadRecentlyOpenEntries(EEditor uiEditor);

	RecentlyOpenEntry*		addRecentlyOpenEntry(EEditor uiEditor, std::string strName);
	void					removeRecentlyOpenedEntries(EEditor uiEditor);
	void					removeRecentlyOpenEntry(EEditor uiEditor, RecentlyOpenEntry *pRecentlyOpenEntry);
	uint32					getRecentlyOpenedFileIndex(EEditor uiEditor, std::string strIMGPath);
	RecentlyOpenEntry*		getRecentlyOpenEntryByPath(EEditor uiEditor, std::string strPath);
	bool					doesRecentlyOpenEntryExist(EEditor uiEditor, std::string strPath);
	std::string				getLastOpenEntry(EEditor uiEditor);
	void					moveRecentlyOpenEntryToTop(EEditor uiEditor, std::string strPath);
	
	std::unordered_map<uint32, std::string>&		getRecentlyOpenedFilesContainer(void) { return m_umapRecentlyOpenedFiles; }
	
private:
	std::unordered_map<EEditor, bxcf::VectorPool<RecentlyOpenEntry*>>		m_umapFilePaths;
	std::unordered_map<uint32, std::string>									m_umapRecentlyOpenedFiles;
};