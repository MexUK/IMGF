#ifndef CRegistry_H
#define CRegistry_H

#include "bxcf.h"
#include "Type/Types.h"
#include <string>

class bxcf::CRegistry
{
public:
	static void				setRegistryValueString(std::string strKey1, std::string strKey2, std::string strValue);
	static std::string		getRegistryValueString(std::string strKey1, std::string strKey2);
	static void				setRegistryValueInt(std::string strKey1, std::string strKey2, int iValue);
	static int				getRegistryValueInt(std::string strKey1, std::string strKey2);
	static void				removeRegistryValue(std::string strKey1, std::string strKey2);
	static void				assoicateFileExtension(std::string strFileExtension, std::string strExePath);

	static void				setSoftwareValueString(std::string strKey1, std::string strKey2, std::string strValue);
	static std::string		getSoftwareValueString(std::string strKey1, std::string strKey2);
	static void				setSoftwareValueInt(std::string strKey1, std::string strKey2, int iValue);
	static int				getSoftwareValueInt(std::string strKey1, std::string strKey2);
	static void				removeSoftwareValue(std::string strKey1, std::string strKey2);
};

#endif