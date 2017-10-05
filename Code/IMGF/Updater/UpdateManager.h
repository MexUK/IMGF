#pragma once

#include "nsimgf.h"
#include "Type/Types.h"
#include "Object/Manager.h"
#include <string>

class imgf::UpdateConnectionManager;

class imgf::ExeBuild
{
public:
	std::string						getBuild(void);

private:
	float32							m_fVersion;
	uint32							m_uiBuild;
	uint8							m_bIsAlpha : 1;
};

class imgf::UpdateManager : public bxcf::Manager
{
public:
	UpdateManager(void);
	~UpdateManager(void);

	void							init(void);
	void							uninit(void);

	void							checkForUpdate(void);

	UpdateConnectionManager*		getUpdateConnectionManager(void) { return m_pUpdateConnectionManager; }
	
	void							processUpdate(void);

private:
	ExeBuild*						getLatestBuildData(void);

private:
	UpdateConnectionManager*		m_pUpdateConnectionManager;
};