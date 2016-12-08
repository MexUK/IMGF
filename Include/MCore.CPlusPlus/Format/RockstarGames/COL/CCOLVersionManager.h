#ifndef CCOLVersionManager_H
#define CCOLVersionManager_H

#include "mcore.h"
#include "Object/CManager.h"
#include "eCOLVersion.h"
#include "Pool/CVectorPool.h"

class mcore::CCOLVersion;

class mcore::CCOLVersionManager : public mcore::CManager, public mcore::CVectorPool<mcore::CCOLVersion*>
{
public:
	void			init(void);
	void			uninit(void);

	mcore::CCOLVersion*	getEntryByVersionId(mcore::eCOLVersion eCOLVersionValue);

private:
	void			initCOLVersions(void);
	void			uninitCOLVersions(void);
};

#endif