#pragma once

#include "Type/Types.h"
#include <string>

class CTokens
{
public:
	static uint32				getTokenCount(std::string& strText, std::string strDelimiter);
	static std::string			addToken(std::string& strText, std::string& strToken, std::string strDelimiter);
	static std::string			addTokenRightShift(std::string& strText, std::string& strToken, std::string strDelimiter);
	static std::string			addTokenRightShiftMax(std::string& strText, std::string& strToken, std::string strDelimiter, uint32 uiMaxTokens);
	static std::string			removeToken(std::string& strText, uint32 uiTokenIndex, std::string strDelimiter); // uiTokenIndex: starts at 0 for first token
};