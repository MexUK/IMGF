#pragma once

#include "nsimgf.h"
#include "Type/Types.h"
#include "Object/CManager.h"
#include <string>

class imgf::UpdateConnectionManager;

class imgf::CExeBuild
{
public:
	std::string						getBuild(void);

private:
	float32							m_fVersion;
	uint32							m_uiBuild;
	uint8							m_bIsAlpha : 1;
};

class imgf::UpdateManager : public bxcf::CManager
{
public:
	UpdateManager(void);
	~UpdateManager(void);

	void							init(void);
	void							uninit(void);

	UpdateConnectionManager*		getUpdateConnectionManager(void) { return m_pUpdateConnectionManager; }
	
	void							processUpdate(void);

private:
	CExeBuild*						getLatestBuildData(void);

private:
	UpdateConnectionManager*		m_pUpdateConnectionManager;
};