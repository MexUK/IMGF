#ifndef CString2_H
#define CString2_H

#include "bxa.h"
#include "Type/Types.h"
#include "Type/Vector/CVector2D.h"
#include "Type/Vector/CVector3D.h"
#include "Type/Vector/CVector4D.h"
#include "Type/Vector/CVector4ui8.h"
#include "Type/Vector/CVector4ui16.h"
#include <atlstr.h>
#include <string>
#include <vector>
#include <deque>
#include <codecvt>
#include <stdint.h>

uint64_t pack754(float80 f, unsigned bits, unsigned expbits);
#define pack754_32(f) (pack754((f), 32, 8))
#define pack754_64(f) (pack754((f), 64, 11))

float80 unpack754(uint64_t i, unsigned bits, unsigned expbits);
#define unpack754_32(i) (unpack754((i), 32, 8))
#define unpack754_64(i) (unpack754((i), 64, 11))

class bxa::CString2
{
public:
	static std::vector<std::string>			split(std::string& strString, std::string strToken);
	static std::string						join(std::vector<std::string>& vecTokens, std::string strDelimiter);

	static std::string						join(std::deque<std::string>& deqTokens, std::string strDelimiter);
	static std::string						replace(std::string& strString, std::string strFind, std::string strReplace);
	static std::string						packUint64(uint64 uiULongLong, bool bBigEndian = true);
	static std::string						packUint32(uint32 uiULong, bool bBigEndian = true);
	static std::string						packUint16(uint16 usUShort, bool bBigEndian = true);
	static std::string						packUint8(uint8 ucUChar);
	static std::string						packInt64(int64 iLongLong, bool bBigEndian = true);
	static std::string						packInt32(int32 iLong, bool bBigEndian = true);
	static std::string						packInt16(int16 iShort, bool bBigEndian = true);
	static std::string						packInt8(int8 iChar);
	static std::string						packFloat32(float32 fValue, bool bBigEndian = true);
	static std::string						packFloat64(float64 fValue, bool bBigEndian = true);
	static std::string						packVector2D(bxa::CVector2D& vecVector, bool bBigEndian = true);
	static std::string						packVector3D(bxa::CVector3D& vecVector, bool bBigEndian = true);
	static std::string						packVector4D(bxa::CVector4D& vecVector, bool bBigEndian = true);
	static std::string						packVector4ui8(bxa::CVector4ui8& vecVector);
	static std::string						packVector4ui16(bxa::CVector4ui16& vecVector, bool bBigEndian = true);
	static uint32							unpackUint32(std::string& strData, bool bBigEndian = true);
	static uint16							unpackUint16(std::string& strData, bool bBigEndian = true);
	static uint8							unpackUint8(std::string& strData);
	static int32							unpackInt32(std::string& strData, bool bBigEndian = true);
	static int16							unpackInt16(std::string& strData, bool bBigEndian = true);
	static int8								unpackInt8(std::string& strData);
	static float32							unpackFloat32(std::string& strData, bool bBigEndian = true);
	static bxa::CVector2D						unpackVector2D(std::string& strData, bool bBigEndian = true);
	static bxa::CVector3D						unpackVector3D(std::string& strData, bool bBigEndian = true);
	static bxa::CVector4D						unpackVector4D(std::string& strData, bool bBigEndian = true);
	static std::string						toString(int iNumber);
	static std::string						toString(uint32 uiNumber);
	static std::string						toString(size_t iNumber);
	static std::string						toString(float32 fNumber);
	static std::string						toStringExtendedFloat(float32 fNumber);
	static std::string						toStringHex(uint32 uiNumber);
	static int								toNumber(std::string& strText);
	static uint32							toUint32(std::string& strString);
	static uint16							toUint16(std::string& strString);
	static uint8							toUint8(std::string& strString);
	static int32							toInt32(std::string& strString);
	static int16							toInt16(std::string& strString);
	static int8								toInt8(std::string& strString);
	static float32							toFloat32(std::string& strString);
	static std::string						trim(std::string& strString, std::string strTrimCharacters = "");
	static std::string						ltrim(std::string& strString, std::string strTrimCharacters = "");
	static std::string						rtrim(std::string& strString, std::string strTrimCharacters = "");
	static std::string						rtrimFromLeft(std::string& strString);
	static std::string						zeroPad(std::string& strData, uint32 uiPadLength);
	static std::string						zeroPad(uint32 uiPadLength);
	static std::string						toUpperCase(std::string& strString);
	static std::string						toLowerCase(std::string& strString);
	static std::string						toTitleCase(std::string& strString);
	static std::string						getTimestampText(uint32 uiTimestamp = 0);
	static std::string						getDateTextForFolder(void);
	static std::string						escapeMenuText(std::string& strText);
	static bool								isIn(std::string& strText, std::string strFind);
	static std::string						readStringUntilZero(std::string& strData);
	static std::string						readStringUntilSpace(std::string& strData);
	static std::string						stripNumbersFromRight(std::string& strText);
	static bool								isLengthInRange(std::string& strString, uint32 uiMinLength, uint32 uiMaxLength);
	static bool								isAlphaNumericUnderscore(std::string& strData);
	static void								setClipboardText(std::string& strText);
	static std::string						getClipboardText(void);
	static std::string						capLength(std::string& strData, uint32 uiMaxLength);
	static uint32							getCurrentEpochTime(void);
	static std::string						mergeStrings(std::string& strString1, std::string& strString2, uint32 uiCapLength);
	static bool								doesStartWith(std::string& strText, std::string& strStartWith, bool bMatchCase = true);
	static bool								isPositiveInteger(std::string& strText);
	static std::string						addNumberGrouping(std::string& strNumber);
	static std::string						fixEOLs(std::string& strData, std::string strEOLCharsToUse);
	static uint32							swapEndian(uint32 uiValue);
	static bool								isAsciiCharacterDisplayable(uint8 uiCharCode, bool bIncludeSpace = true, bool bIncludeTab = true);
	static std::string						createCharString(uint8 uiCharCode);
	static std::string						getTextInSameCase(std::string& strText, std::string& strTextCase);
	static uint32							getCRC(std::string& strData);
	static std::string						extractQuotedData(std::string& strData, uint32 uiQuoteIndex = 0);
	static std::string						convertCStringToStdString(CString str)
	{
		CT2CA pszConvertedAnsiString(str);
		return std::string(pszConvertedAnsiString);
	}
	static std::wstring						convertStdStringToStdWString(std::string str)
	{
		/*
		std::wstring string_to_convert;

		typedef std::codecvt_utf8<wchar_t> convert_typeX;
		std::wstring_convert<convert_typeX, wchar_t> converterX;

		return converterX.from_bytes(str);
		*/

		/*
		std::wstring wstr;
		for (uint32 i = 0, j = str.length(); i < j; i++)
		{
			wstr.append(1, (uint8)str.c_str()[i]);
		}
		return wstr;
		*/

		/*
		int iLength = MultiByteToWideChar(0, 0, str.c_str(), str.length() + 1, 0, 0);
		WCHAR *wstr = new WCHAR[iLength + 1];
		MultiByteToWideChar(0, 0, str.c_str(), str.length() + 1, wstr, iLength + 1);
		wstr[iLength] = 0;
		std::wstring wstr2(wstr, iLength);
		delete wstr;
		return wstr2;
		*/

		setlocale(LC_ALL, "");
		std::wstring wc(str.length()+1, L'#');
		size_t uiCharsConvertedCount = 0;
		mbstowcs_s(&uiCharsConvertedCount, &wc[0], str.length()+1, str.c_str(), str.length());
		//mbstowcs(&wc[0], str.c_str(), str.length());
		return wc;
	}
	static std::string						convertStdWStringToStdString(std::wstring str)
	{
		int len;
		int slength = (int)str.length() + 1;
		len = WideCharToMultiByte(CP_ACP, 0, str.c_str(), slength, 0, 0, 0, 0);
		char* buf = new char[len];
		WideCharToMultiByte(CP_ACP, 0, str.c_str(), slength, buf, len, 0, 0);
		std::string r(buf);
		delete[] buf;
		return r;
	}
};

#endif