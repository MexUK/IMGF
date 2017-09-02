#pragma once

#include "nsimgf.h"
#include "Object/CManager.h"
#include "UpdateConnection.h"
#include "Pool/CVectorPool.h"

class imgf::UpdateConnectionManager : public bxcf::CManager, public bxcf::CVectorPool<UpdateConnection*>
{
public:
	void							init(void);
	void							uninit(void);

private:
	void							initUpdateConnections(void);
	void							uninitUpdateConnections(void);
};