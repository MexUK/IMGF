#pragma once

#include "nsimgf.h"
#include "Object/Manager.h"
#include "RecentlyOpenEntry.h"
#include "Pool/VectorPool.h"
#include <string>
#include <unordered_map>

class imgf::RecentlyOpenManager : public bxcf::Manager, public bxcf::VectorPool<RecentlyOpenEntry*>
{
public:
	void					init(void);
	void					uninit(void);

	void					loadRecentlyOpenEntries(void);
	void					unloadRecentlyOpenEntries(void);

	RecentlyOpenEntry*		addRecentlyOpenEntry(std::string strName);
	void					removeRecentlyOpenedEntries(void);
	void					removeRecentlyOpenEntry(RecentlyOpenEntry *pRecentlyOpenEntry);
	uint32					getRecentlyOpenedFileIndex(std::string strIMGPath);
	RecentlyOpenEntry*		getRecentlyOpenEntryByPath(std::string strPath);
	bool					doesRecentlyOpenEntryExist(std::string strPath);
	std::string				getLastOpenEntry(void);
	void					moveRecentlyOpenEntryToTop(std::string strPath);
	
	std::unordered_map<uint32, std::string>&		getRecentlyOpenedFilesContainer(void) { return m_umapRecentlyOpenedFiles; }
	
private:
	std::unordered_map<uint32, std::string>			m_umapRecentlyOpenedFiles;
};