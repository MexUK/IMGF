#pragma once

#include "nsimgf.h"
#include "Object/CManager.h"
#include "CUpdateConnection.h"
#include "Pool/CVectorPool.h"

class imgf::CUpdateConnectionManager : public bxcf::CManager, public bxcf::CVectorPool<CUpdateConnection*>
{
public:
	void							init(void);
	void							uninit(void);

private:
	void							initUpdateConnections(void);
	void							uninitUpdateConnections(void);
};