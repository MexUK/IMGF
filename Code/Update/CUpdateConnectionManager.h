#ifndef CUpdateConnectionManager_H
#define CUpdateConnectionManager_H

#include "Object/CManager.h"
#include "CUpdateConnection.h"
#include "Pool/CVectorPool.h"

class CUpdateConnectionManager : public mcore::CManager, public mcore::CVectorPool<CUpdateConnection*>
{
public:
	void							init(void);
	void							uninit(void);

private:
	void							initUpdateConnections(void);
	void							uninitUpdateConnections(void);
};

#endif