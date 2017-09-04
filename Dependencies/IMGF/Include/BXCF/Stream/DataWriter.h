#pragma once

#include "nsbxcf.h"
#include "DataStream.h"
#include "Object/IndexedInstance.h"
#include "Type/Types.h"
#include "EDataStreamType.h"
#include "Unit/Byte/EEndian.h"
#include "Type/Vector/Vec2i.h"
#include "Type/Vector/Vec2u8.h"
#include "Type/Vector/Vec2u.h"
#include "Type/Vector/Vec2f.h"
#include "Type/Vector/Vec3u8.h"
#include "Type/Vector/Vec3u.h"
#include "Type/Vector/Vec3f.h"
#include "Type/Vector/Vec4u8.h"
#include "Type/Vector/Vec4u16.h"
#include "Type/Vector/Vec4f.h"
#include "Pool/VectorPool.h"
#include <string>
#include <vector>
#include <fstream>

class bxcf::DataWriter;

class bxcf::DataWriter : public bxcf::DataStream, public bxcf::IndexedInstance<bxcf::DataWriter>
{
public:
	DataWriter(void);

	// reset
	void					close(bool bHasError = false);
	void					reset(bool bHasError = false);
	void					resetData(void);

	// file processing
	bool					openFile(std::string& strFilePath, uint32 uiFlags);
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
	void					writeVec2i(bxcf::Vec2i& vecPoint);
	void					writeVector2i32(bxcf::Vec2i& vecUints);
	void					writeVec2u(bxcf::Vec2u& vecSize);
	void					writeVector2ui8(bxcf::Vec2u8& vecUints);
	void					writeVector2ui32(bxcf::Vec2u& vecUints);
	void					writeVector3ui8(bxcf::Vec3u8& vecUints);
	void					writeVector3ui32(bxcf::Vec3u& vecUints);
	void					writeVector4ui8(bxcf::Vec4u8& vecUints);
	void					writeStdVectorUint32(std::vector<uint32>& vecUints);
	void					writeStdVector4ui8(std::vector<bxcf::Vec4u8>& vecVectors);
	void					writeStdVector4ui16(std::vector<Vec4u16>& vecVectors);

	// write float
	void					writeFloat32(float32 fFloat);
	void					writeFloat64(float64 fFloat);
	void					writeVector2D(bxcf::Vec2f& vecVector);
	void					writeVector3D(bxcf::Vec3f& vecVector);
	void					writeVector4D(bxcf::Vec4f& vecVector);
	void					writeStdVector2D(std::vector<bxcf::Vec2f>& vecVectors);
	void					writeStdVector3D(std::vector<bxcf::Vec3f>& vecVectors);
	void					writeStdVector4D(std::vector<bxcf::Vec4f>& vecVectors);

	// write token
	void					writeTokenString(std::string& strString);
	void					writeTokenInt32(int32 iInt);
	void					writeTokenUint32(uint32 uiInt);
	void					writeTokenFloat32(float32 fFloat);
	void					writeTokenVector2D(bxcf::Vec2f& vecVector);
	void					writeTokenVector3D(bxcf::Vec3f& vecVector);
	void					writeTokenVector4D(bxcf::Vec4f& vecVector);

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
	void					write(bxcf::Vec2i& vecPoint);
	void					write(bxcf::Vec2u& vecSize);
	void					write(bxcf::Vec4u8& vecUints);
	void					write(std::vector<uint32>& vecUints);
	void					write(std::vector<bxcf::Vec2f>& vecVectors);
	void					write(std::vector<bxcf::Vec3f>& vecVectors);
	void					write(std::vector<bxcf::Vec4u8>& vecVectors);
	void					write(std::vector<bxcf::Vec4u16>& vecVectors);

	// write float - type guessed
	void					write(float32 fFloat);
	void					write(float64 fFloat);
	void					write(bxcf::Vec2f& vecVector);
	void					write(bxcf::Vec3f& vecVector);
	void					write(bxcf::Vec4f& vecVector);

	// write token - type guessed
	void					writeToken(std::string& strString);
	void					writeToken(int32 iInt);
	void					writeToken(uint32 uiInt);
	void					writeToken(float32 fFloat);
	void					writeToken(bxcf::Vec2f& vecVector);
	void					writeToken(bxcf::Vec3f& vecVector);
	void					writeToken(bxcf::Vec4f& vecVector);

	template <class DerivedFormatClass>
	void					writeLineEntries(bxcf::VectorPool<DerivedFormatClass> *pPool);
	template <class SectionClass, class EntryClass>
	void					writeSectionLineEntries(bxcf::VectorPool<SectionClass> *pPool);

	// write struct
	void					write(DataWriter& pDataWriter);

	// write raw struct
	template <class T>
	void					writeStruct(T& object)
	{
		write(&object, sizeof(T));
	}
	
	// replace
	void					replace(uint32 uiByteIndex, std::string& strData);

	// seek
	void					setSeek(uint64 uiByteIndex);
	uint64					getSeek(void);

	// file mode only
	std::ofstream&			getFile(void) { return m_file; }

	void					setTemporaryFilePath(std::string& strTemporaryFilePath) { m_strTemporaryFilePath = strTemporaryFilePath; }
	std::string&			getTemporaryFilePath(void) { return m_strTemporaryFilePath; }

	std::string				generateTemporaryFilePath(std::string& strFilePath);

private:
	static std::vector<DataWriter*>	m_vecDataWriters;
	std::ofstream			m_file;
	std::string				m_strTemporaryFilePath;
};

template<class DerivedFormatClass>
void						bxcf::DataWriter::writeLineEntries(bxcf::VectorPool<DerivedFormatClass> *pPool)
{
	DataWriter *pDataWriter = DataWriter::get();

	for (DerivedFormatClass *pEntry : pPool->getEntries())
	{
		pEntry->serialize();
		pDataWriter->writeString("\n");
	}
}

template <class SectionClass, class EntryClass>
void						bxcf::DataWriter::writeSectionLineEntries(bxcf::VectorPool<SectionClass> *pPool)
{
	DataWriter *pDataWriter = DataWriter::get();

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