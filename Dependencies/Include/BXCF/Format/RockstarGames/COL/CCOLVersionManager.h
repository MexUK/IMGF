#ifndef CCOLVersionManager_H
#define CCOLVersionManager_H

#include "bxcf.h"
#include "Object/CManager.h"
#include "eCOLVersion.h"
#include "Pool/CVectorPool.h"

class bxcf::CCOLVersion;

class bxcf::CCOLVersionManager : public bxcf::CManager, public bxcf::CVectorPool<bxcf::CCOLVersion*>
{
public:
	void			init(void);
	void			uninit(void);

	bxcf::CCOLVersion*	getEntryByVersionId(bxcf::eCOLVersion eCOLVersionValue);

private:
	void			initCOLVersions(void);
	void			uninitCOLVersions(void);
};

#endif