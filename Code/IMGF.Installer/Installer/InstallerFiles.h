#pragma once

#include <string>
#include "Pool/VectorPool.h"

class InstallerFile;

class InstallerFiles
{
public:
	bxcf::VectorPool<InstallerFile*>&	getFiles(void) { return m_vecFiles; }

	void								load(void);

private:
	void								addFile(std::string strRelativeFilePath);

private:
	bxcf::VectorPool<InstallerFile*>	m_vecFiles;
};