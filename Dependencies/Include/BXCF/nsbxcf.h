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
	
	
	
	enum ECompressionAlgorithm;

	class DataPath;

	class Debug;

	template <typename TReturn, typename ...Args> struct EventFunction;
	template <typename TReturn, typename ...Args> std::unordered_map<int, std::vector< bxcf::EventFunction<TReturn, Args...>* >> g_eventBoundFunctions;
	template <typename TReturn, typename ...Args> std::unordered_map<int, std::vector< bxcf::EventFunction<TReturn, const Args...>* >> g_eventBoundFunctionsConst;
	struct Events;
	struct EventBindable;

	enum EExceptionCode;

	namespace fileType
	{
		enum EFileType;
	};


	template<class T> class FormatManager;
	class Format;

	class BMPFormat;
	struct BMPFormat_Header1;
	struct BMPFormat_Header2_Version2;
	struct BMPFormat_Header2_Version3;
	struct BMPFormat_Header2_Version4;
	class BMPManager;

	class CURFormat;
	class CURManager;

	class DDSFormat;
	struct DDSFormat_Header_DDS_HEADER;
	struct DDSFormat_Header_DDS_HEADER_DXT10;
	struct DDSFormat_Header_DDS_PIXELFORMAT_Part1;
	struct DDSFormat_Header_DDS_PIXELFORMAT_Part2;
	class DDSManager;

	class ICOFormat;
	class ICOManager;

	enum EJSONType;
	class JSONString;
	class JSONValue;
	class JSONNumber;
	class JSONBoolean;
	class JSONNull;
	class JSONContainer;
	class JSONArray;
	class JSONObject;
	class JSONManager;

	class URL;
	struct URLComponents;

	class INIManager;

	class ImageFile;
	class ImageManager;
	class RasterDataFormat;
	class RasterDataFormatManager;

	class LocalizationFormat;
	class LocalizationManager;
	enum ELanguage;

	template<class Class> class IndexedInstance;
	template<class SingletonClass> class Singleton;
	class Manager;

	class Platform;
	class PlatformManager;
	enum EPlatform;

	template <class T> class VectorPool;
	template <class Key, class Value> class UMapContainer;

	class DataReader;
	class DataStream;
	enum EDataStreamType;
	class DataWriter;

	class Timing;

	enum EEndian;

	class CompressionManager;
	class File;
	class ImageManager;
	class Input;
	enum EDXTCompressionType;
	enum ERasterDataFormat;
	class Math;
	class Memory;
	class Number;
	class Path;
	class Process;
	class Registry;
	class String;
	class StdVector;

	template <typename TReturn, class TStruct, typename ...Args> class Timers;
	template <typename TReturn, class TStruct, typename ...Args> class Timer;

	enum E2DAxis;
	class Colour;
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