#ifndef CFormat_H
#define CFormat_H

#include "BXA.h"
#include "Type/Types.h"
#include "Unit/Byte/eEndian.h"
#include <string>
#include <vector>

class bxa::CFormat
{
public:
	CFormat(bool bEntityUsesBinaryFile, bxa::eEndian eBinaryDataByteEndian = bxa::LITTLE_ENDIAN);

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
	
private:
	uint8						m_ucErrorCode;
	bxa::eEndian						m_eEndian;							// only used for byte interpretation type: binary
	std::string					m_strFilePath;						// only used for data stream type: file
	uint8						m_bFormatUsesBinaryData	: 1;
};

#endif