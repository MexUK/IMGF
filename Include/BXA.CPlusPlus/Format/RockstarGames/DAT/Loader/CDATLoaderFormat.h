#ifndef CDATLoaderFormat_H
#define CDATLoaderFormat_H

#include "BXA.h"
#include "Format/CFormat.h"
#include "Pool/CVectorPool.h"
#include "eDATLoaderEntryType.h"
#include <string>
#include <vector>

class bxa::CDATLoaderEntry;
class bxa::CIMGFormat;
class bxa::CIDEFormat;
class bxa::CIPLFormat;

class bxa::CDATLoaderFormat : public bxa::CFormat, public bxa::CVectorPool<bxa::CDATLoaderEntry*>
{
public:
	CDATLoaderFormat(void) : CFormat(false) {};
	
	void									unload(void);

	std::vector<std::string>				getRelativeIDEPaths(void);
	std::vector<std::string>				getRelativeIPLPaths(void);

	std::vector<bxa::CIMGFormat*>				parseIMGFiles(std::string strGameDirectoryPath);
	std::vector<bxa::CIDEFormat*>				parseIDEFiles(std::string strGameDirectoryPath);
	std::vector<bxa::CIPLFormat*>				parseIPLFiles(std::string strGameDirectoryPath);

	template<class ManagerClass, class FormatClass>
	std::vector<FormatClass*>				parseFiles(std::string strGameDirectoryPath, bxa::eDATLoaderEntryType eType1, bxa::eDATLoaderEntryType eType2 = DAT_LOADER_UNKNOWN);

private:
	void									unserialize(void);
	void									serialize(void) {}; // todo

	void									unserializeLine(void);
};

#endif