#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"
#include "Object/Manager.h"
#include "RageResourceType.h"
#include "Pool/VectorPool.h"
#include <string>

class bxgi::RageResourceTypeManager : public bxcf::Manager, public bxcf::VectorPool<bxgi::RageResourceType*>
{
public:
	void											init(void);
	void											uninit(void);

	bxgi::RageResourceType*						getResourceTypeByIdentifierOrFileExtension(uint32 uiResourceIdentifer, std::string strFileExtension);
	bxgi::RageResourceType*						getResourceTypeByIdentifier(uint32 uiResourceIdentifer);
	bxgi::RageResourceType*						getResourceTypeByFileExtension(std::string strFileExtension);

private:
	void											initRageResourceTypes(void);
};