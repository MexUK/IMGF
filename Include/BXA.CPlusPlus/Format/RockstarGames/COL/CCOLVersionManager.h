#ifndef CCOLVersionManager_H
#define CCOLVersionManager_H

#include "BXA.h"
#include "Object/CManager.h"
#include "eCOLVersion.h"
#include "Pool/CVectorPool.h"

class bxa::CCOLVersion;

class bxa::CCOLVersionManager : public bxa::CManager, public bxa::CVectorPool<bxa::CCOLVersion*>
{
public:
	void			init(void);
	void			uninit(void);

	bxa::CCOLVersion*	getEntryByVersionId(bxa::eCOLVersion eCOLVersionValue);

private:
	void			initCOLVersions(void);
	void			uninitCOLVersions(void);
};

#endif