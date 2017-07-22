#ifndef CRageResourceTypeManager_H
#define CRageResourceTypeManager_H

#include "BXA.h"
#include "Type/Types.h"
#include "Object/CManager.h"
#include "CRageResourceType.h"
#include "Pool/CVectorPool.h"
#include <string>
#include <vector>
#include <unordered_map>

class bxa::CRageResourceTypeManager : public bxa::CManager, public bxa::CVectorPool<bxa::CRageResourceType*>
{
public:
	void											init(void);
	void											uninit(void);

	bxa::CRageResourceType*								getResourceTypeByIdentifierOrFileExtension(uint32 uiResourceIdentifer, std::string strFileExtension);
	bxa::CRageResourceType*								getResourceTypeByIdentifier(uint32 uiResourceIdentifer);
	bxa::CRageResourceType*								getResourceTypeByFileExtension(std::string strFileExtension);

private:
	void											initRageResourceTypes(void);
};

#endif