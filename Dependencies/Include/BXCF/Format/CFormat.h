#ifndef CFormat_H
#define CFormat_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Unit/Byte/eEndian.h"
#include <string>

class bxcf::CFormat
{
public:
	CFormat(bool bEntityUsesBinaryFile, bxcf::eEndian eBinaryDataByteEndian = bxcf::LITTLE_ENDIAN);
	CFormat(std::string& strFilePath, bool bEntityUsesBinaryFile, bxcf::eEndian eBinaryDataByteEndian = bxcf::LITTLE_ENDIAN);
	CFormat(bxcf::CDataReader& reader, bool bEntityUsesBinaryFile, bxcf::eEndian eBinaryDataByteEndian = bxcf::LITTLE_ENDIAN);
	~CFormat(void);

	bool						open(void);
	void						close(void);
	bool						isOpen(void);

	void						checkMetaDataIsLoaded(void);

	virtual void				readMetaData(void) {} // todo - make pure

	void						unserialize2(void);

	static std::string			getFileTypeText(bxcf::fileType::EFileType uiFileType);
	static std::string			getFileTypeName(bxcf::fileType::EFileType uiFileType);
	static std::string			getFileTypeExtensions(bxcf::fileType::EFileType uiFileType);




	void						unserializeViaMemory(std::string& strData);
	void						unserializeViaFile(std::string& strFilePath);

	std::string					serializeViaMemory(void);
	void						serializeViaFile(void);
	void						serializeViaFile(std::string& strFilePath);

	std::string					storeViaMemory(void) { return serializeViaMemory(); }
	void						storeViaFile(std::string& strFilePath) { serializeViaFile(strFilePath); }

	void						setErrorCode(uint8 ucErrorCode) { m_ucErrorCode = ucErrorCode; }
	uint8						getErrorCode(void) { return m_ucErrorCode; }
	bool						doesHaveError(void) { return m_ucErrorCode != 0; }

	std::string					getErrorReason(uint8 uiErrorCode = -1);

	void						setFormatUsesBinaryData(bool bState) { m_bFormatUsesBinaryData = bState; }
	bool						doesFormatUseBinaryData(void) { return m_bFormatUsesBinaryData; }

	// file only
	void						setFilePath(std::string& strFilePath) { m_strFilePath = strFilePath; }
	std::string&				getFilePath(void) { return m_strFilePath; }

	std::string&				getOriginalFilePath(void);

private:
	void						_unserialize(void);					// wraps the pure virtual unserialize(),                          with a try catch, applying error code.
	void						_unserializeWithOpenClose(void);	// wraps the pure virtual unserialize() and file IO open & close, with a try catch, applying error code.
	void						_serialize(void);					// wraps the pure virtual serialize(),                            with a try catch, applying error code.
	void						_serializeWithOpenClose(void);		// wraps the pure virtual serialize() and file IO open & close,   with a try catch, applying error code.
	
	virtual void				unserialize(void) = 0;				// overridden by derived CFormat
	virtual void				serialize(void) = 0;				// overridden by derived CFormat
	
public:
	uint32						m_uiEntryCount;

protected:
	std::string					m_strFilePath;						// only used for data stream type: file
	bxcf::CDataReader&			m_reader;
	uint8						m_bFormatUsesBinaryData : 1;

private:
	uint8						m_ucErrorCode;
	bxcf::eEndian				m_eEndian;							// only used for byte interpretation type: binary
	uint8						m_bMetaDataIsLoaded		: 1;
};

#endif