#ifndef CUpdateConnectionManager_H
#define CUpdateConnectionManager_H

#include "Object/CManager.h"
#include "CUpdateConnection.h"
#include "Pool/CVectorPool.h"

class CUpdateConnectionManager : public bxa::CManager, public bxa::CVectorPool<CUpdateConnection*>
{
public:
	void							init(void);
	void							uninit(void);

private:
	void							initUpdateConnections(void);
	void							uninitUpdateConnections(void);
};

#endif