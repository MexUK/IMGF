#ifndef CIMGFormat_H
#define CIMGFormat_H

#include "bxa.h"
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
#include <string>
#include <vector>
#include <unordered_map>

class bxa::CDataReader;

class bxa::CIMGFormat : public bxa::CFormat, public bxa::CVectorPool<bxa::CIMGEntry*>
{
public:
	CIMGFormat(void);

	void											unload(void) {}

	void											unserializeRWVersions(void);
	void											unserializeResourceTypes(void);

	void											setIMGVersion(bxa::eIMGVersion eIMGVersion) { m_eIMGVersion = eIMGVersion; }
	bxa::eIMGVersion										getIMGVersion(void) { return m_eIMGVersion; }

	void											setEncrypted(bool bEncrypted) { m_bEncrypted = bEncrypted; }
	bool											isEncrypted(void) { return m_bEncrypted; }

	void											setGameType(uint8 ucGameType) { m_ucGameType = ucGameType; }
	uint8											getGameType(void) { return m_ucGameType; }

	void											setPlatform(bxa::ePlatform ePlatformValue) { m_ePlatform = ePlatformValue; }
	bxa::ePlatform										getPlatform(void) { return m_ePlatform; }

	std::vector<std::string>						getEntryExtensions(void);
	uint32											getEntryExtensionCount(std::string strEntryExtension);
	std::vector<std::string>						getEntryVersions(std::vector<bxa::eCOLVersion>& vecCOLVersions, std::vector<bxa::eRWVersion>& vecRWVersions);

	static bxa::eCompressionAlgorithm					getCompressionAlgorithmIdFromFastman92CompressionAlgorithmId(eIMGVersionFastman92CompressionAlgorithm eFastman92CompressionAlgorithmId);

	bxa::CIMGEntry*										addEntryViaFile(std::string& strEntryFilePath, std::string strEntryName = "");
	bxa::CIMGEntry*										addEntryViaData(std::string& strEntryName, std::string& strEntryData);
	void											addEntry(bxa::CIMGEntry *pIMGEntry);
	void											addEntries(std::vector<std::string>& vecEntryFilePaths);
	void											addAllEntriesInFolder(std::string& strFolderPath);
	void											removeEntry(bxa::CIMGEntry *pIMGEntry);
	bxa::CIMGEntry*										replaceEntryViaFile(std::string& strEntryName, std::string& strEntryFilePath, std::string strNewEntryName = "");
	bxa::CIMGEntry*										replaceEntryViaData(std::string& strEntryName, std::string& strEntryData, std::string strNewEntryName = "");
	uint32											replaceEntries(std::vector<std::string>& vecPaths, std::vector<std::string>& vecReplacedEntryNames, std::vector<CIMGEntry*>& vecReplacedEntries);
	bxa::CIMGEntry*										addOrReplaceEntryViaFile(std::string& strEntryFilePath, std::string strEntryName = "");
	bxa::CIMGEntry*										addOrReplaceEntryViaData(std::string& strEntryName, std::string& strEntryData);
	std::unordered_map<bxa::CIMGEntry*, std::string>		getAllEntriesData(void); // not recommended to be used, may use too much memory, better to iterate pIMGFile->getEntries()
	std::unordered_map<bxa::CIMGEntry*, std::string>		getEntriesData(std::vector<bxa::CIMGEntry*>& vecEntries); // not recommended to be used, may use too much memory, better to iterate pIMGFile->getEntries()
	uint32											getNextEntryOffset(void); // in bytes
	std::vector<bxa::CIMGEntry*>							getEntriesByExtension(std::string strExtension);
	bxa::CIMGEntry*										getEntryByName(std::string& strEntryName); // case-insensitive
	bxa::CIMGEntry*										getEntryByNameWithoutExtension(std::string& strEntryNameWithoutExtension); // case-insensitive
	std::vector<std::string>						getEntryNames(void);
	bxa::CIMGEntry*										getEntryByHighestOffset(void);
	uint32											getEntryCountForName(std::string& strEntryName); // case-insensitive
	uint32											getEntryCountForCompressionType(bxa::eCompressionAlgorithm eCompressionAlgorithmValue);

	static uint32									getEntryPaddedSize(uint32 uiDataLength);
	void											unsetNewAndReplacedFlagForAllEntries(void);

	uint32											merge(std::string& strSecondIMGPath, std::vector<std::string>& vecImportedEntryNames);
	void											split(std::vector<bxa::CIMGEntry*>& vecIMGEntries, std::string& strOutPath, eIMGVersion eIMGVersion);
	CIMGFormat*										clone(std::string& strClonedIMGPath);

	void											exportSingle(bxa::CIMGEntry *pIMGEntry, std::string& strFolderPath);
	void											exportMultiple(std::vector<bxa::CIMGEntry*>& vecIMGEntries, std::string strFolderPath);
	void											exportAll(std::string& strFolderPath);

	bool											doesContainEntryWithUnknownRWVersion(void); // for IMG versions 1 and 2 - todo - should it be changed to without RW to match function below - check func bodys
	std::vector<bxa::CIMGEntry*>							getUnknownVersionEntries(void); // for IMG versions 1 and 2

private:
	void											unserialize(void);
	void											serialize(void);

	void											unserializeHeaderComponents(void);
	void											unserializeBodyComponents(void);

	void											serializeHeaderAndBodyComponents(void);

	bxa::CIMGPeekData									peekIMGData(void);
	
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
	bxa::eIMGVersion										m_eIMGVersion;
	bxa::ePlatform										m_ePlatform;
	std::unordered_map<std::string, uint32>			m_umapExtensionCounts;
	uint8											m_ucGameType;
	uint8											m_bEncrypted : 1;
};

#endif