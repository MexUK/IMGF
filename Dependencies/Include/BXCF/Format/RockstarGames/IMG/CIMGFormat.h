#ifndef CIMGFormat_H
#define CIMGFormat_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Format/CFormat.h"
#include "Pool/CVectorPool.h"
#include "eIMGVersion.h"
#include "Format/RenderWare/Helper/BinaryStream/eRWVersion.h"
#include "CIMGPeekData.h"
#include "Compression/eCompressionAlgorithm.h"
#include "Format/RockstarGames/IMG/Fastman92/eIMGVersionFastman92CompressionAlgorithm.h"
#include "Format/RockstarGames/COL/eCOLVersion.h"
#include "CIMGEntry.h"
#include "Platform/Hardware/ePlatform.h"
#include "Stream/CDataReader.h"
#include <string>
#include <vector>
#include <unordered_map>

class bxcf::CIMGFormat : public bxcf::CFormat, public bxcf::CVectorPool<bxcf::CIMGEntry*>
{
public:
	CIMGFormat(void);
	CIMGFormat(bxcf::CDataReader& reader, std::string& strFilePath);

	void											unload(void) {}

	void											readMetaData(void);

	bool											unserialize2(void);

	void											setVersion(bxcf::eIMGVersion eIMGVersion) { m_eIMGVersion = eIMGVersion; }
	bxcf::eIMGVersion								getVersion(void);

	void											unserializeRWVersions(void);
	void											unserializeResourceTypes(void);

	void											setEncrypted(bool bEncrypted) { m_bEncrypted = bEncrypted; }
	bool											isEncrypted(void) { return m_bEncrypted; }

	void											setGameType(uint8 ucGameType) { m_ucGameType = ucGameType; }
	uint8											getGameType(void) { return m_ucGameType; }

	void											setPlatform(bxcf::ePlatform ePlatformValue) { m_ePlatform = ePlatformValue; }
	bxcf::ePlatform										getPlatform(void) { return m_ePlatform; }

	std::vector<std::string>						getEntryExtensions(void);
	uint32											getEntryExtensionCount(std::string strEntryExtension);
	std::vector<std::string>						getEntryVersions(std::vector<bxcf::eCOLVersion>& vecCOLVersions, std::vector<bxcf::eRWVersion>& vecRWVersions);

	static bxcf::eCompressionAlgorithm					getCompressionAlgorithmIdFromFastman92CompressionAlgorithmId(eIMGVersionFastman92CompressionAlgorithm eFastman92CompressionAlgorithmId);

	bxcf::CIMGEntry*										addEntryViaFile(std::string& strEntryFilePath, std::string strEntryName = "");
	bxcf::CIMGEntry*										addEntryViaData(std::string& strEntryName, std::string& strEntryData);
	void											addEntry(bxcf::CIMGEntry *pIMGEntry);
	void											addEntries(std::vector<std::string>& vecEntryFilePaths);
	void											addAllEntriesInFolder(std::string& strFolderPath);
	void											removeEntry(bxcf::CIMGEntry *pIMGEntry);
	bxcf::CIMGEntry*										replaceEntryViaFile(std::string& strEntryName, std::string& strEntryFilePath, std::string strNewEntryName = "");
	bxcf::CIMGEntry*										replaceEntryViaData(std::string& strEntryName, std::string& strEntryData, std::string strNewEntryName = "");
	uint32											replaceEntries(std::vector<std::string>& vecPaths, std::vector<std::string>& vecReplacedEntryNames, std::vector<CIMGEntry*>& vecReplacedEntries);
	bxcf::CIMGEntry*										addOrReplaceEntryViaFile(std::string& strEntryFilePath, std::string strEntryName = "");
	bxcf::CIMGEntry*										addOrReplaceEntryViaData(std::string& strEntryName, std::string& strEntryData);
	std::unordered_map<bxcf::CIMGEntry*, std::string>		getAllEntriesData(void); // not recommended to be used, may use too much memory, better to iterate pIMGFile->getEntries()
	std::unordered_map<bxcf::CIMGEntry*, std::string>		getEntriesData(std::vector<bxcf::CIMGEntry*>& vecEntries); // not recommended to be used, may use too much memory, better to iterate pIMGFile->getEntries()
	uint32											getNextEntryOffset(void); // in bytes
	std::vector<bxcf::CIMGEntry*>							getEntriesByExtension(std::string strExtension);
	bxcf::CIMGEntry*										getEntryByName(std::string& strEntryName); // case-insensitive
	bxcf::CIMGEntry*										getEntryByNameWithoutExtension(std::string& strEntryNameWithoutExtension); // case-insensitive
	std::vector<std::string>						getEntryNames(void);
	bxcf::CIMGEntry*										getEntryByHighestOffset(void);
	uint32											getEntryCountForName(std::string& strEntryName); // case-insensitive
	uint32											getEntryCountForCompressionType(bxcf::eCompressionAlgorithm eCompressionAlgorithmValue);

	static uint32									getEntryPaddedSize(uint32 uiDataLength);
	void											unsetNewAndReplacedFlagForAllEntries(void);

	uint32											merge(std::string& strSecondIMGPath, std::vector<std::string>& vecImportedEntryNames);
	void											split(std::vector<bxcf::CIMGEntry*>& vecIMGEntries, std::string& strOutPath, eIMGVersion eIMGVersion);
	CIMGFormat*										clone(std::string& strClonedIMGPath);

	void											exportSingle(bxcf::CIMGEntry *pIMGEntry, std::string& strFolderPath);
	void											exportMultiple(std::vector<bxcf::CIMGEntry*>& vecIMGEntries, std::string strFolderPath);
	void											exportAll(std::string& strFolderPath);

	bool											doesContainEntryWithUnknownRWVersion(void); // for IMG versions 1 and 2 - todo - should it be changed to without RW to match function below - check func bodys
	std::vector<bxcf::CIMGEntry*>							getUnknownVersionEntries(void); // for IMG versions 1 and 2

private:
	void											unserialize(void);
	void											serialize(void);

	void											unserializeHeaderComponents(void);
	void											unserializeBodyComponents(void);

	void											serializeHeaderAndBodyComponents(void);

	bxcf::CIMGPeekData									peekIMGData(void);
	
	void											unserializeVersion1(void);
	void											unserializeVersion2(void);
	void											unserializeVersion3_Encrypted(void);
	void											unserializeVersion3_Unencrypted(void);
	void											unserializeVersionFastman92(void);

	void											serializeVersion1(void);
	void											serializeVersion2(void);
	void											serializeVersion3_Encrypted(void);
	void											serializeVersion3_Unencrypted(void);
	void											serializeVersionFastman92(void);

	uint32											getVersion3NamesLength(void);

private:
	void											addEntryExtensionCount(std::string strEntryExtension);
	void											removeEntryExtensionCount(std::string strEntryExtension);
	void											loadEntryExtensionCounts(void);

private:
	bxcf::eIMGVersion										m_eIMGVersion;
	bxcf::ePlatform										m_ePlatform;
	std::unordered_map<std::string, uint32>			m_umapExtensionCounts;
	uint8											m_ucGameType;
	uint8											m_bEncrypted : 1;
};

#endif