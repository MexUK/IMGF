#ifndef CInstallationMeta_H
#define CInstallationMeta_H

#include "Type/Types.h"
#include <string>

class CInstallationMeta
{
public:
	std::string					getProgramFilesPath(void);
	std::string					getLocalAppPath(void);
};

#endif