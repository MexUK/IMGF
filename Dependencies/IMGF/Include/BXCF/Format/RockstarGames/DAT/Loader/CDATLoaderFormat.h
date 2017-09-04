#ifndef CDATLoaderFormat_H
#define CDATLoaderFormat_H

#include "bxcf.h"
#include "Format/CFormat.h"
#include "Pool/CVectorPool.h"
#include "eDATLoaderEntryType.h"
#include <string>
#include <vector>

class bxcf::CDATLoaderEntry;
class bxcf::CIMGFormat;
class bxcf::CIDEFormat;
class bxcf::CIPLFormat;

class bxcf::CDATLoaderFormat : public bxcf::CFormat, public bxcf::CVectorPool<bxcf::CDATLoaderEntry*>
{
public:
	CDATLoaderFormat(void) : CFormat(false) {};
	
	void									unload(void);

	std::vector<std::string>				getRelativeIDEPaths(void);
	std::vector<std::string>				getRelativeIPLPaths(void);

	std::vector<bxcf::CIMGFormat*>				parseIMGFiles(std::string strGameDirectoryPath);
	std::vector<bxcf::CIDEFormat*>				parseIDEFiles(std::string strGameDirectoryPath);
	std::vector<bxcf::CIPLFormat*>				parseIPLFiles(std::string strGameDirectoryPath);

	template<class ManagerClass, class FormatClass>
	std::vector<FormatClass*>				parseFiles(std::string strGameDirectoryPath, bxcf::eDATLoaderEntryType eType1, bxcf::eDATLoaderEntryType eType2 = DAT_LOADER_UNKNOWN);

private:
	void									unserialize(void);
	void									serialize(void) {}; // todo

	void									unserializeLine(void);
};

#endif