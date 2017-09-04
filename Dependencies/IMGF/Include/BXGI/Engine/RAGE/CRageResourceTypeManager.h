#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Object/CManager.h"
#include "CRageResourceType.h"
#include "Pool/CVectorPool.h"
#include <string>

class bxgi::CRageResourceTypeManager : public bxcf::CManager, public bxcf::CVectorPool<bxgi::CRageResourceType*>
{
public:
	void											init(void);
	void											uninit(void);

	bxgi::CRageResourceType*						getResourceTypeByIdentifierOrFileExtension(uint32 uiResourceIdentifer, std::string strFileExtension);
	bxgi::CRageResourceType*						getResourceTypeByIdentifier(uint32 uiResourceIdentifer);
	bxgi::CRageResourceType*						getResourceTypeByFileExtension(std::string strFileExtension);

private:
	void											initRageResourceTypes(void);
};