#pragma once

#include "Type/Types.h"
#include <string>
#include <vector>
#include <unordered_map>

namespace bxcf
{
	extern std::string g_strBlankString;
	extern bool g_bDefaultBool;
	
	
	
	void init(void);
	
	
	
	enum eCompressionAlgorithm;

	class CDataPath;

	class CDebug;

	template <typename TReturn, typename ...Args> struct EventFunction;
	template <typename TReturn, typename ...Args> std::unordered_map<int, std::vector< bxcf::EventFunction<TReturn, Args...>* >> g_eventBoundFunctions;
	struct Events;
	struct EventBindable;

	enum eExceptionCode;

	namespace fileType
	{
		enum EFileType;
	};


	template<class T> class CFormatManager;
	class CFormat;

	class CBMPFormat;
	struct CBMPFormat_Header1;
	struct CBMPFormat_Header2_Version2;
	struct CBMPFormat_Header2_Version3;
	struct CBMPFormat_Header2_Version4;
	class CBMPManager;

	class CCURFormat;
	class CCURManager;

	class CDDSFormat;
	struct CDDSFormat_Header_DDS_HEADER;
	struct CDDSFormat_Header_DDS_HEADER_DXT10;
	struct CDDSFormat_Header_DDS_PIXELFORMAT_Part1;
	struct CDDSFormat_Header_DDS_PIXELFORMAT_Part2;
	class CDDSManager;

	class CICOFormat;
	class CICOManager;

	enum eJsonTypes;
	class CJSONString;
	class CJSONValue;
	class CJSONNumber;
	class CJSONBoolean;
	class CJSONNull;
	class CJSONContainer;
	class CJSONArray;
	class CJSONObject;
	class CJSONManager;

	class CURL;

	class CINIManager;

	class CImageFile;
	class CImageManager;
	class CRasterDataFormat;
	class CRasterDataFormatManager;

	class CLocalizationFormat;
	class CLocalizationManager;
	enum eLanguage;

	template<class Class> class CIndexedInstance;
	template<class SingletonClass> class CSingleton;
	class CManager;

	class CPlatform;
	class CPlatformManager;
	enum ePlatform;

	template <class T> class CVectorPool;
	template <class Key, class Value> class CUMapContainer;
	template <class KeyClass> class CMultipleTypeValuesUMapContainer;

	class CDataReader;
	class CDataStream;
	enum eDataStreamType;
	class CDataWriter;

	class CTiming;

	enum eEndian;

	class CCompressionManager;
	class CFile;
	class CImageManager;
	class CInput;
	enum eDXTCompressionType;
	enum eRasterDataFormat;
	class CMath;
	class CMemory;
	class CNumber;
	class CPath;
	class CProcess;
	class CRegistry;
	class CString2;
	class CStdVector;

	class CColour;
	class Vec2i8;
	class Vec2i16;
	class Vec2i;
	class Vec2i64;
	class Vec2u8;
	class Vec2u16;
	class Vec2u;
	class Vec2u64;
	class Vec2f;
	class Vec2f64;
	class Vec2f80;
	class Vec3i8;
	class Vec3i16;
	class Vec3i;
	class Vec3i64;
	class Vec3u8;
	class Vec3u16;
	class Vec3u;
	class Vec3u64;
	class Vec3f;
	class Vec3f64;
	class Vec3f80;
	class Vec4i8;
	class Vec4i16;
	class Vec4i;
	class Vec4i64;
	class Vec4u8;
	class Vec4u16;
	class Vec4u;
	class Vec4u64;
	class Vec4f;
	class Vec4f64;
	class Vec4f80;

	class LinkLayer;
	class IP;
	class ICMP;
};