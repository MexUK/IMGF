#pragma once

#include "nsimgf.h"
#include "Object/Manager.h"
#include "UpdateConnection.h"
#include "Pool/VectorPool.h"
#include <string>

class imgf::UpdateConnectionManager : public bxcf::Manager, public bxcf::VectorPool<UpdateConnection*>
{
public:
	void							init(void);
	void							uninit(void);

	UpdateConnection*				addConnection(std::string strLatestVersionURL, std::string strBuildsFolderURL);

private:
	void							initUpdateConnections(void);
	void							uninitUpdateConnections(void);
};