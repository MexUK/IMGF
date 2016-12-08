#ifndef CDATLoaderFormat_H
#define CDATLoaderFormat_H

#include "mcore.h"
#include "Format/CFormat.h"
#include "Pool/CVectorPool.h"
#include "eDATLoaderEntryType.h"
#include <string>
#include <vector>

class mcore::CDATLoaderEntry;
class mcore::CIMGFormat;
class mcore::CIDEFormat;
class mcore::CIPLFormat;

class mcore::CDATLoaderFormat : public mcore::CFormat, public mcore::CVectorPool<mcore::CDATLoaderEntry*>
{
public:
	CDATLoaderFormat(void) : CFormat(false) {};
	
	void									unload(void);

	std::vector<std::string>				getRelativeIDEPaths(void);
	std::vector<std::string>				getRelativeIPLPaths(void);

	std::vector<mcore::CIMGFormat*>				parseIMGFiles(std::string strGameDirectoryPath);
	std::vector<mcore::CIDEFormat*>				parseIDEFiles(std::string strGameDirectoryPath);
	std::vector<mcore::CIPLFormat*>				parseIPLFiles(std::string strGameDirectoryPath);

	template<class ManagerClass, class FormatClass>
	std::vector<FormatClass*>				parseFiles(std::string strGameDirectoryPath, mcore::eDATLoaderEntryType eType1, mcore::eDATLoaderEntryType eType2 = DAT_LOADER_UNKNOWN);

private:
	void									unserialize(void);
	void									serialize(void) {}; // todo

	void									unserializeLine(void);
};

#endif