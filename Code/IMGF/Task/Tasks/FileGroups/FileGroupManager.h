#pragma once

#include "nsimgf.h"
#include "Object/Manager.h"
#include "FileGroup.h"
#include "Pool/VectorPool.h"
#include "Event/EventBindable.h"
#include "GUI/Editor/EEditor.h"
#include <string>
#include <vector>
#include <unordered_map>

class imgf::FileGroupManager : public bxcf::Manager, public bxcf::VectorPool<FileGroup*>, public bxcf::EventBindable
{
public:
	void			init(void);
	void			uninit(void);
	
	void			onToolReady(void);

	void			loadFileGroups(EEditor uiEditor);
	void			unloadFileGroups(EEditor uiEditor);

	FileGroup*		addFileGroup(EEditor uiEditor, std::string strSessionName, std::vector<std::string>& vecPaths);
	void			removeFileGroup(EEditor uiEditor, FileGroup *pSession);
	FileGroup*		getFileGroupByName(EEditor uiEditor, std::string strSessionName);
	
	std::unordered_map<uint32, std::string>&		getFileGroupsContainer(void) { return m_umapFileGroups; }
	
private:
	std::unordered_map<uint32, std::string>			m_umapFileGroups;
};