#ifndef CDataStream_H
#define CDataStream_H

#include "mcore.h"
#include "Type/Types.h"
#include "eDataStreamType.h"
#include "Unit/Byte/eEndian.h"
#include "Type/Vector/CVector2D.h"
#include "Type/Vector/CVector3D.h"
#include "Type/Vector/CVector4D.h"
#include <string>
#include <vector>
#include <fstream>

/*
Modes:
	Data Direction		Read/Write		(CDataReader/CDataWriter) : CDataStream
	Device				Memory/File		Data already in memory vs data in files.
	Byte Range			Text/Binary		Ascii files with 100% octet range 32-126 are text mode. Maybe other multi byte charsets utilizing octet codes outside this range are text mode too.
										This mode maps to byte vs token processing.
*/

class mcore::CDataStream
{
public:
	// data stream types: memory & file
	CDataStream(void);

	virtual void			reset(void);
	
	void					setStreamType(eDataStreamType eType) { m_eDataStreamType = eType; }
	eDataStreamType			getStreamType(void) { return m_eDataStreamType; }

	void					setEndian(eEndian eEndianValue) { m_eEndian = eEndianValue; }
	eEndian					getEndian(void) { return m_eEndian; }
	
	virtual void			setSeek(uint64 uiByteIndex) = 0;
	virtual uint64			getSeek(void) = 0;
	
	void						setLineTokens(std::vector<std::string>& vecLineTokens) { m_vecLineTokens = vecLineTokens; }
	std::vector<std::string>&	getLineTokens(void) { return m_vecLineTokens; }

	// data stream type: file
	void					setFilePath(std::string& strFilePath) { m_strFilePath = strFilePath; }
	std::string&			getFilePath(void) { return m_strFilePath; }
	
	void					open(bool bBinaryMode);
	void					close(void);
	
	virtual void			openFile(std::string& strFilePath, uint32 uiFlags) = 0;
	virtual bool			isFileOpen(void) = 0;
	virtual void			resetFile(void) = 0;

	// data stream type: memory
	void					setData(std::string& strData) { m_strData_Memory = strData; }
	std::string&			getData(void) { return m_strData_Memory; }
	
protected:
	// data stream type: memory
	void					setSeek_Memory(uint64 uiSeek) { m_uiSeek_Memory = uiSeek; }
	uint64					getSeek_Memory(void) { return m_uiSeek_Memory; }

protected:
	// data stream type: memory & file
	eDataStreamType			m_eDataStreamType;
	eEndian					m_eEndian;
	std::vector<std::string>	m_vecLineTokens;	// only used for byte range type: text

	// data stream type: memory
	uint64					m_uiSeek_Memory;
	std::string				m_strData_Memory;
	
	// data stream type: file
	std::string				m_strFilePath;
};

#endif