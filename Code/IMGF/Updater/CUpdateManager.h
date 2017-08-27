#pragma once

#include "nsimgf.h"
#include "Type/Types.h"
#include "Object/CManager.h"
#include <string>

class imgf::CUpdateConnectionManager;

class imgf::CExeBuild
{
public:
	std::string						getBuild(void);

private:
	float32							m_fVersion;
	uint32							m_uiBuild;
	uint8							m_bIsAlpha : 1;
};

class imgf::CUpdateManager : public bxcf::CManager
{
public:
	CUpdateManager(void);
	~CUpdateManager(void);

	void							init(void);
	void							uninit(void);

	CUpdateConnectionManager*		getUpdateConnectionManager(void) { return m_pUpdateConnectionManager; }
	
	void							processUpdate(void);

private:
	CExeBuild*						getLatestBuildData(void);

private:
	CUpdateConnectionManager*		m_pUpdateConnectionManager;
};