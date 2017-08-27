#pragma once

#include "nsimgf.h"
#include "Object/CManager.h"
#include "CRecentlyOpenEntry.h"
#include "Pool/CVectorPool.h"
#include <string>
#include <unordered_map>

class imgf::CRecentlyOpenManager : public bxcf::CManager, public bxcf::CVectorPool<CRecentlyOpenEntry*>
{
public:
	void					init(void);
	void					uninit(void);

	void					loadRecentlyOpenEntries(void);
	void					unloadRecentlyOpenEntries(void);

	CRecentlyOpenEntry*		addRecentlyOpenEntry(std::string strName);
	void					removeRecentlyOpenedEntries(void);
	void					removeRecentlyOpenEntry(CRecentlyOpenEntry *pRecentlyOpenEntry);
	uint32					getRecentlyOpenedFileIndex(std::string strIMGPath);
	CRecentlyOpenEntry*		getRecentlyOpenEntryByPath(std::string strPath);
	bool					doesRecentlyOpenEntryExist(std::string strPath);
	std::string				getLastOpenEntry(void);
	void					moveRecentlyOpenEntryToTop(std::string strPath);
	
	std::unordered_map<uint32, std::string>&		getRecentlyOpenedFilesContainer(void) { return m_umapRecentlyOpenedFiles; }
	
private:
	std::unordered_map<uint32, std::string>			m_umapRecentlyOpenedFiles;
};