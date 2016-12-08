#ifndef CRageResourceTypeManager_H
#define CRageResourceTypeManager_H

#include "mcore.h"
#include "Type/Types.h"
#include "Object/CManager.h"
#include "CRageResourceType.h"
#include "Pool/CVectorPool.h"
#include <string>
#include <vector>
#include <unordered_map>

class mcore::CRageResourceTypeManager : public mcore::CManager, public mcore::CVectorPool<mcore::CRageResourceType*>
{
public:
	void											init(void);
	void											uninit(void);

	mcore::CRageResourceType*								getResourceTypeByIdentifierOrFileExtension(uint32 uiResourceIdentifer, std::string strFileExtension);
	mcore::CRageResourceType*								getResourceTypeByIdentifier(uint32 uiResourceIdentifer);
	mcore::CRageResourceType*								getResourceTypeByFileExtension(std::string strFileExtension);

private:
	void											initRageResourceTypes(void);
};

#endif