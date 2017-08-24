#ifndef CDATLoaderFormat_H
#define CDATLoaderFormat_H

#include "bxgi.h"
#include "Format/CFormat.h"
#include "Pool/CVectorPool.h"
#include "eDATLoaderEntryType.h"
#include <string>
#include <vector>

class bxgi::CDATLoaderEntry;
class bxgi::CIMGFormat;
class bxgi::CIDEFormat;
class bxgi::CIPLFormat;

class bxgi::CDATLoaderFormat : public bxcf::CFormat, public bxcf::CVectorPool<bxgi::CDATLoaderEntry*>
{
public:
	CDATLoaderFormat(void) : CFormat(false) {};
	
	void									unload(void);

	std::vector<std::string>				getRelativeIDEPaths(void);
	std::vector<std::string>				getRelativeIPLPaths(void);

	std::vector<bxgi::CIMGFormat*>				parseIMGFiles(std::string strGameDirectoryPath);
	std::vector<bxgi::CIDEFormat*>				parseIDEFiles(std::string strGameDirectoryPath);
	std::vector<bxgi::CIPLFormat*>				parseIPLFiles(std::string strGameDirectoryPath);

	template<class ManagerClass, class FormatClass>
	std::vector<FormatClass*>				parseFiles(std::string strGameDirectoryPath, bxgi::eDATLoaderEntryType eType1, bxgi::eDATLoaderEntryType eType2 = DAT_LOADER_UNKNOWN);

private:
	void									unserialize(void);
	void									serialize(void) {}; // todo

	void									unserializeLine(void);
};

#endif