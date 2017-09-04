#pragma once

#include "nsbxcf.h"
#include "Object/Manager.h"
#include <string>

template<class T>
class bxcf::FormatManager : public bxcf::Manager
{
public:
	static T*					parseViaMemory(std::string& strData);
	static T*					parseViaFile(std::string& strFilePath);

	static T*					parseManyViaMemory(std::vector<std::string>& vecData);
	static T*					parseManyViaFile(std::vector<std::string>& vecFilePaths);
};

template<class T>
T*			bxcf::FormatManager<T>::parseViaMemory(std::string& strData)
{
	T *pFormat = new T;
	pFormat->unserializeViaMemory(strData);
	return pFormat;
}

template<class T>
T*			bxcf::FormatManager<T>::parseViaFile(std::string& strFilePath)
{
	T *pFormat = new T;
	pFormat->setFilePath(strFilePath);
	pFormat->unserializeViaFile(strFilePath);
	return pFormat;
}

template<class T>
T*			bxcf::FormatManager<T>::parseManyViaMemory(std::vector<std::string>& vecData)
{
	T
		*pFormat = new T[vecData.size()],
		*pFormat2 = pFormat;
	for (std::string& strData : vecData)
	{
		pFormat2->unserializeViaData(strData);
		pFormat2++;
	}
	return pFormat;
}

template<class T>
T*			bxcf::FormatManager<T>::parseManyViaFile(std::vector<std::string>& vecFilePaths)
{
	T
		*pFormat = new T[vecFilePaths.size()],
		*pFormat2 = pFormat;
	for (std::string& strFilePath : vecFilePaths)
	{
		pFormat2->unserializeViaFile(strFilePath);
		pFormat2++;
	}
	return pFormat;
}