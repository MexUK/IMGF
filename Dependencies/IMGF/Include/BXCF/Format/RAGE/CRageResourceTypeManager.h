#ifndef CRageResourceTypeManager_H
#define CRageResourceTypeManager_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Object/CManager.h"
#include "CRageResourceType.h"
#include "Pool/CVectorPool.h"
#include <string>
#include <vector>
#include <unordered_map>

class bxcf::CRageResourceTypeManager : public bxcf::CManager, public bxcf::CVectorPool<bxcf::CRageResourceType*>
{
public:
	void											init(void);
	void											uninit(void);

	bxcf::CRageResourceType*								getResourceTypeByIdentifierOrFileExtension(uint32 uiResourceIdentifer, std::string strFileExtension);
	bxcf::CRageResourceType*								getResourceTypeByIdentifier(uint32 uiResourceIdentifer);
	bxcf::CRageResourceType*								getResourceTypeByFileExtension(std::string strFileExtension);

private:
	void											initRageResourceTypes(void);
};

#endif