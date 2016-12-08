#ifndef CDataWriter_H
#define CDataWriter_H

#include "mcore.h"
#include "CDataStream.h"
#include "Object/CIndexedInstance.h"
#include "Type/Types.h"
#include "eDataStreamType.h"
#include "Unit/Byte/eEndian.h"
#include "Type/Vector/CVector2D.h"
#include "Type/Vector/CVector3D.h"
#include "Type/Vector/CVector4D.h"
#include "Type/Vector/CVector2ui8.h"
#include "Type/Vector/CVector2ui32.h"
#include "Type/Vector/CVector3ui8.h"
#include "Type/Vector/CVector3ui32.h"
#include "Type/Vector/CVector4ui8.h"
#include "Type/Vector/CVector4ui16.h"
#include "Type/Vector/CPoint2D.h"
#include "Type/Vector/CSize2D.h"
#include "Pool/CVectorPool.h"
#include <string>
#include <vector>
#include <fstream>

class mcore::CDataWriter;

class mcore::CDataWriter : public mcore::CDataStream, public mcore::CIndexedInstance<mcore::CDataWriter>
{
public:
	CDataWriter(void);

	// reset
	void					close(bool bHasError = false);
	void					reset(bool bHasError = false);
	void					resetData(void);

	// file processing
	void					openFile(std::string& strFilePath, uint32 uiFlags);
	bool					isFileOpen(void);
	void					resetFile(void);

	// write string
	void					writeStringRef(std::string& strData);
	void					writeStringRef(std::string& strData, uint32 uiTotalByteCountPadded);
	void					writeString(std::string strData);
	void					writeString(std::string strData, uint32 uiTotalByteCountPadded);
	void					writeString(uint32 uiZeroByteCount);
	void					writeStringWithLengthRef(std::string& strData);
	void					writeStringWithLength(std::string strData);
	void					writeCString(char *pData, uint32 uiByteCount);

	// write int
	void					writeUint8(uint8 uiInt);
	void					writeUint16(uint16 uiInt);
	void					writeUint32(uint32 uiInt);
	void					writeUint64(uint64 uiInt);
	void					writeInt8(int8 iInt);
	void					writeInt16(int16 iInt);
	void					writeInt32(int32 iInt);
	void					writeInt64(int64 iInt);
	void					writePoint2D(mcore::CPoint2D& vecPoint);
	void					writeVector2i32(mcore::CVector2i32& vecUints);
	void					writeSize2D(mcore::CSize2D& vecSize);
	void					writeVector2ui8(mcore::CVector2ui8& vecUints);
	void					writeVector2ui32(mcore::CVector2ui32& vecUints);
	void					writeVector3ui8(mcore::CVector3ui8& vecUints);
	void					writeVector3ui32(mcore::CVector3ui32& vecUints);
	void					writeVector4ui8(mcore::CVector4ui8& vecUints);
	void					writeStdVectorUint32(std::vector<uint32>& vecUints);
	void					writeStdVector4ui8(std::vector<mcore::CVector4ui8>& vecVectors);
	void					writeStdVector4ui16(std::vector<CVector4ui16>& vecVectors);

	// write float
	void					writeFloat32(float32 fFloat);
	void					writeFloat64(float64 fFloat);
	void					writeVector2D(mcore::CVector2D& vecVector);
	void					writeVector3D(mcore::CVector3D& vecVector);
	void					writeVector4D(mcore::CVector4D& vecVector);
	void					writeStdVector2D(std::vector<mcore::CVector2D>& vecVectors);
	void					writeStdVector3D(std::vector<mcore::CVector3D>& vecVectors);
	void					writeStdVector4D(std::vector<mcore::CVector4D>& vecVectors);

	// write token
	void					writeTokenString(std::string& strString);
	void					writeTokenInt32(int32 iInt);
	void					writeTokenUint32(uint32 uiInt);
	void					writeTokenFloat32(float32 fFloat);
	void					writeTokenVector2D(mcore::CVector2D& vecVector);
	void					writeTokenVector3D(mcore::CVector3D& vecVector);
	void					writeTokenVector4D(mcore::CVector4D& vecVector);

	// write string - type guessed
	void					write(std::string& strData);
	void					write(std::string& strData, uint32 uiTotalByteCountPadded);
	void					write(char *pData, uint32 uiByteCount);

	// write int - type guessed
	void					write(uint8 uiInt);
	void					write(uint16 uiInt);
	void					write(uint32 uiInt);
	void					write(uint64 uiInt);
	void					write(int8 iInt);
	void					write(int16 iInt);
	void					write(int32 iInt);
	void					write(int64 iInt);
	void					write(mcore::CPoint2D& vecPoint);
	void					write(mcore::CSize2D& vecSize);
	void					write(mcore::CVector4ui8& vecUints);
	void					write(std::vector<uint32>& vecUints);
	void					write(std::vector<mcore::CVector2D>& vecVectors);
	void					write(std::vector<mcore::CVector3D>& vecVectors);
	void					write(std::vector<mcore::CVector4ui8>& vecVectors);
	void					write(std::vector<mcore::CVector4ui16>& vecVectors);

	// write float - type guessed
	void					write(float32 fFloat);
	void					write(float64 fFloat);
	void					write(mcore::CVector2D& vecVector);
	void					write(mcore::CVector3D& vecVector);
	void					write(mcore::CVector4D& vecVector);

	// write token - type guessed
	void					writeToken(std::string& strString);
	void					writeToken(int32 iInt);
	void					writeToken(uint32 uiInt);
	void					writeToken(float32 fFloat);
	void					writeToken(mcore::CVector2D& vecVector);
	void					writeToken(mcore::CVector3D& vecVector);
	void					writeToken(mcore::CVector4D& vecVector);

	template <class DerivedFormatClass>
	void					writeLineEntries(mcore::CVectorPool<DerivedFormatClass> *pPool);
	template <class SectionClass, class EntryClass>
	void					writeSectionLineEntries(mcore::CVectorPool<SectionClass> *pPool);

	// write raw struct
	template <class T>
	void					writeStruct(T& object)
	{
		write(&object, sizeof(T));
	}
	
	// seek
	void					setSeek(uint64 uiByteIndex);
	uint64					getSeek(void);

	// file mode only
	std::ofstream&			getFile(void) { return m_file; }

	void					setTemporaryFilePath(std::string& strTemporaryFilePath) { m_strTemporaryFilePath = strTemporaryFilePath; }
	std::string&			getTemporaryFilePath(void) { return m_strTemporaryFilePath; }

	std::string				generateTemporaryFilePath(std::string& strFilePath);

private:
	static std::vector<CDataWriter*>	m_vecDataWriters;
	std::ofstream			m_file;
	std::string				m_strTemporaryFilePath;
};

template<class DerivedFormatClass>
void						mcore::CDataWriter::writeLineEntries(mcore::CVectorPool<DerivedFormatClass> *pPool)
{
	CDataWriter *pDataWriter = CDataWriter::getInstance();

	for (DerivedFormatClass *pEntry : pPool->getEntries())
	{
		pEntry->serialize();
		pDataWriter->writeString("\n");
	}
}

template <class SectionClass, class EntryClass>
void						mcore::CDataWriter::writeSectionLineEntries(mcore::CVectorPool<SectionClass> *pPool)
{
	CDataWriter *pDataWriter = CDataWriter::getInstance();

	for (SectionClass *pSection : pPool->getEntries())
	{
		pSection->serialize();
		pDataWriter->writeString("\n");

		for (EntryClass *pEntry : pSection->getEntries())
		{
			pEntry->serialize();
			pDataWriter->writeString("\n");
		}

		pDataWriter->writeString("end\n");
	}
}

#endif