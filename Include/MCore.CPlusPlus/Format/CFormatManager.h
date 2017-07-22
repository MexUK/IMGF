#ifndef CFormatManager_H
#define CFormatManager_H

#include "bxa.h"
#include "Object/CManager.h"
#include "Format/CFormat.h"
#include <string>

template<class T>
class bxa::CFormatManager : public bxa::CManager
{
public:
	static T*				parseViaMemory(std::string& strData);
	static T*				parseViaFile(std::string& strFilePath);

	static T*				parseManyViaMemory(std::vector<std::string>& vecData);
	static T*				parseManyViaFile(std::vector<std::string>& vecFilePaths);
};




template<class T>
T*			bxa::CFormatManager<T>::parseViaMemory(std::string& strData)
{
	T *pFormat = new T;
	pFormat->unserializeViaMemory(strData);
	return pFormat;
}

template<class T>
T*			bxa::CFormatManager<T>::parseViaFile(std::string& strFilePath)
{
	T *pFormat = new T;
	pFormat->setFilePath(strFilePath);
	pFormat->unserializeViaFile(strFilePath);
	return pFormat;
}

template<class T>
T*			bxa::CFormatManager<T>::parseManyViaMemory(std::vector<std::string>& vecData)
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
T*			bxa::CFormatManager<T>::parseManyViaFile(std::vector<std::string>& vecFilePaths)
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

#endif