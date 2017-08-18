#pragma once

#include "bxcf.h"
#include "Type/Types.h"
#include <string>
#include <vector>
#include <deque>
#include <unordered_map>

class bxcf::CStdVector
{
public:
	static std::vector<std::string>					combineVectors(std::vector<std::string>& vecVector1, std::vector<std::string>& vecVector2);

	template <class T>
	static std::vector<T>							combineVectors(std::vector<T>& vecVector1, std::vector<T>& vecVector2);

	static void										addToVector(std::vector<std::string>& vecVector1, std::vector<std::string>& vecVector2);
	static std::deque<std::string>					convertVectorToDeque(std::vector<std::string>& vecVector);
	static std::unordered_map<std::string, bool>	convertVectorToUnorderedMap(std::vector<std::string>& vecVector);
	static std::vector<std::string>					toUpperCase(std::vector<std::string> vecVector);
	static std::vector<std::string>					removeDuplicates(std::vector<std::string>& vecVector);
	static uint32									findKey(std::vector<std::string>& vecVector, std::string& strValue);
	static void										addUniqueEntry(std::vector<std::string>& vecVector, std::string& strValue);
	static std::vector<std::string>					getUniqueEntries(std::vector<std::string>& vecVector1, std::vector<std::string>& vecVector2);
	static bool										isIn(std::vector<std::string>& vecVector1, std::string& strLookFor);
	static void										sortAZCaseInsensitive(std::vector<std::string>& vecVector);
	template <typename T>
	static std::vector<std::string>					mapSorted(std::vector<T>& vecVector, std::string(*fpCallback)(T));
};

template <class T>
static std::vector<T>								bxcf::CStdVector::combineVectors(std::vector<T>& vecVector1, std::vector<T>& vecVector2)
{
	uint32 i = 0;
	vector<T> vecValues;
	vecValues.resize(vecVector1.size() + vecVector2.size());
	for (T& value : vecVector1)
	{
		vecValues[i++] = value;
	}
	for (T& value : vecVector2)
	{
		vecValues[i++] = value;
	}
	return vecValues;
}

template <typename T>
std::vector<std::string>							bxcf::CStdVector::mapSorted(std::vector<T>& vecVector, std::string(*fpCallback)(T))
{
	std::vector<std::string> vecOutVector;
	vecOutVector.resize(vecVector.size());
	uint32 i = 0;
	for (T uiValue : vecVector)
	{
		vecOutVector[i++] = fpCallback(uiValue);
	}
	sortAZCaseInsensitive(vecOutVector);
	return vecOutVector;
}