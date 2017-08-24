#ifndef CSectionLinesFormat_H
#define CSectionLinesFormat_H

#include "bxgi.h"
#include "Format/CFormat.h"
#include "Format/e2DFXType.h"
#include <string>
#include <vector>
#include <map>
#include <algorithm>

template<class FormatClass, class EntryClass, typename SectionEnum, class OtherEntryClass, class SectionEntryClass, class DataEntryClass>
class bxgi::CSectionLinesFormat : public bxcf::CFormat
{
public:
	CSectionLinesFormat(void);

	virtual void										unload(void);

	std::map<SectionEnum, std::vector<EntryClass*>>&	getSectionEntries(void) { return m_umapSectionEntries; }

	void												unserializeLine(void);

	std::vector<std::string>							getModelNames(void);
	std::vector<std::string>							getTXDNames(void);
	std::vector<std::string>							getTXDNamesFromModelNames(std::vector<std::string>& vecModelNames);
	std::string											getTXDNameFromModelName(std::string strModelName);
	std::vector<EntryClass*>							getEntriesByModelName(std::string strModelName);
	std::vector<EntryClass*>							getEntriesByTXDName(std::string strTXDName);

	template<class EntryClass2>
	std::vector<EntryClass2*>							getEntriesBySection(SectionEnum eSectionValue);

	OtherEntryClass*									createOtherEntry(void);
	SectionEntryClass*									createSectionEntry(SectionEnum eFormatSectionValue);
	virtual DataEntryClass*								createDataEntry(SectionEnum eFormatSectionValue, uint32 uiSectionSpecificType = 0) = 0;

	virtual void										sortAllSectionsByObjectId(void);

	std::vector<std::vector<EntryClass*>>				getSectionsBySection(SectionEnum eFormatSectionValue);

	virtual SectionEnum									getSectionFromText(std::string strSectionText) = 0;
	virtual std::string									getSectionText(SectionEnum eSectionValue) = 0;

	virtual uint32										detectSectionSpecificType(SectionEnum eFormatSectionValue) = 0;

protected:
	void												unserializeText(void);
	void												serializeText(void);

private:
	void												setActiveReadSection(SectionEnum eActiveReadSection) { m_eActiveReadSection = eActiveReadSection; }
	SectionEnum											getActiveReadSection(void) { return m_eActiveReadSection; }

private:
	std::map<SectionEnum, std::vector<EntryClass*>>		m_umapSectionEntries;
	SectionEnum											m_eActiveReadSection;
};




template<class FormatClass, class EntryClass, typename SectionEnum, class OtherEntryClass, class SectionEntryClass, class DataEntryClass>
bxgi::CSectionLinesFormat<FormatClass, EntryClass, SectionEnum, OtherEntryClass, SectionEntryClass, DataEntryClass>::CSectionLinesFormat(void) :
	CFormat(false),
	m_eActiveReadSection((SectionEnum)0)
{
}

template<class FormatClass, class EntryClass, typename SectionEnum, class OtherEntryClass, class SectionEntryClass, class DataEntryClass>
void				bxgi::CSectionLinesFormat<FormatClass, EntryClass, SectionEnum, OtherEntryClass, SectionEntryClass, DataEntryClass>::unload(void)
{
	for (auto it : m_umapSectionEntries)
	{
		for (EntryClass *pFormatEntry : it.second)
		{
			pFormatEntry->unload();
			delete pFormatEntry;
		}
	}
	m_umapSectionEntries.clear();
}

template<class FormatClass, class EntryClass, typename SectionEnum, class OtherEntryClass, class SectionEntryClass, class DataEntryClass>
void				bxgi::CSectionLinesFormat<FormatClass, EntryClass, SectionEnum, OtherEntryClass, SectionEntryClass, DataEntryClass>::unserializeLine(void)
{
	// initialize
	EntryClass *pFormatEntry = nullptr;
	CDataReader *pDataReader = CDataReader::get();
	string strActiveLine = *pDataReader->getActiveLine();

	// remove comment from end of line
	string strComment = "";
	size_t uiCommentPosition = strActiveLine.find('#');
	if (uiCommentPosition != string::npos)
	{
		strComment = strActiveLine.substr(uiCommentPosition + 1);
		strActiveLine = strActiveLine.substr(0, uiCommentPosition);
	}

	// trim line
	strActiveLine = CString2::trim(strActiveLine);

	// check if line is blank or section end
	if (strActiveLine == "" || CString2::toUpperCase(strActiveLine) == "END")
	{
		pFormatEntry = createOtherEntry();
		pFormatEntry->unserialize();
	}
	else
	{
		// set active line for data reader - keep blank lines intact (detected blank after comment removal and trimming)
		pDataReader->setActiveLine(&strActiveLine);

		// check if line is a section name
		SectionEnum eFormatSectionValue = getSectionFromText(strActiveLine);
		if (eFormatSectionValue != 0) // 0 is the value of both IDE_SECTION_UNKNOWN and IPL_SECTION_UNKNOWN
		{
			pFormatEntry = createSectionEntry(eFormatSectionValue);
			pFormatEntry->unserialize();
			setActiveReadSection(eFormatSectionValue);
		}
		else
		{
			// line is a data line
			pDataReader->setTokenModeEnabled(true);
			pDataReader->setLineTokens(CString2::split(CString2::replace(strActiveLine, ",", ""), " "));
			try
			{
				eFormatSectionValue = getActiveReadSection();
				pFormatEntry = createDataEntry(eFormatSectionValue, detectSectionSpecificType(eFormatSectionValue));
				pFormatEntry->unserialize();
			}
			catch (eExceptionCode)
			{
				// e.g. undocumeted formats: despite being detected as a data line, treat it as a other line to preserve data when serializing.
				if (pFormatEntry != nullptr)
				{
					delete pFormatEntry;
				}
				pFormatEntry = createOtherEntry();
				pFormatEntry->setSectionType(getActiveReadSection());
				pFormatEntry->unserialize();
			}
			pDataReader->setTokenModeEnabled(false);
		}
	}

	// apply comment to entry
	pFormatEntry->setComment(strComment);

	// store entry in Format object
	if (pFormatEntry->getEntryType() != SECTION_LINES_ENTRY_SECTION)
	{
		getSectionEntries().rbegin()->second.push_back(pFormatEntry);
	}
}

template<class FormatClass, class EntryClass, typename SectionEnum, class OtherEntryClass, class SectionEntryClass, class DataEntryClass>
void				bxgi::CSectionLinesFormat<FormatClass, EntryClass, SectionEnum, OtherEntryClass, SectionEntryClass, DataEntryClass>::unserializeText(void)
{
	CDataReader *pDataReader = CDataReader::get();
	pDataReader->readAndStoreLines();
	while (pDataReader->iterateLines())
	{
		unserializeLine();
	}
}

template<class FormatClass, class EntryClass, typename SectionEnum, class OtherEntryClass, class SectionEntryClass, class DataEntryClass>
void				bxgi::CSectionLinesFormat<FormatClass, EntryClass, SectionEnum, OtherEntryClass, SectionEntryClass, DataEntryClass>::serializeText(void)
{
	CDataWriter *pDataWriter = CDataWriter::get();
	for (auto it : getSectionEntries())
	{
		for (EntryClass *pFormatEntry : it.second)
		{
			pFormatEntry->serialize();
			pDataWriter->writeString("\n");
		}
	}
}

template<class FormatClass, class EntryClass, typename SectionEnum, class OtherEntryClass, class SectionEntryClass, class DataEntryClass>
std::vector<std::vector<EntryClass*>>	bxgi::CSectionLinesFormat<FormatClass, EntryClass, SectionEnum, OtherEntryClass, SectionEntryClass, DataEntryClass>::getSectionsBySection(SectionEnum eFormatSectionValue)
{
	std::vector<std::vector<EntryClass*>> vecFormatSections;
	for (auto it : getSectionEntries())
	{
		if (it.first == eFormatSectionValue)
		{
			vecFormatSections.push_back(it.second);
		}
	}
	return vecFormatSections;
}

template<class FormatClass, class EntryClass, typename SectionEnum, class OtherEntryClass, class SectionEntryClass, class DataEntryClass>
OtherEntryClass*	bxgi::CSectionLinesFormat<FormatClass, EntryClass, SectionEnum, OtherEntryClass, SectionEntryClass, DataEntryClass>::createOtherEntry(void)
{
	OtherEntryClass *pFormatEntry = new OtherEntryClass((FormatClass*)this);
	return pFormatEntry;
}

template<class FormatClass, class EntryClass, typename SectionEnum, class OtherEntryClass, class SectionEntryClass, class DataEntryClass>
SectionEntryClass*	bxgi::CSectionLinesFormat<FormatClass, EntryClass, SectionEnum, OtherEntryClass, SectionEntryClass, DataEntryClass>::createSectionEntry(SectionEnum eFormatSectionValue)
{
	SectionEntryClass *pFormatEntry = new SectionEntryClass((FormatClass*)this);
	pFormatEntry->setSectionType(eFormatSectionValue);
	return pFormatEntry;
}

template<class FormatClass, class EntryClass, typename SectionEnum, class OtherEntryClass, class SectionEntryClass, class DataEntryClass>
std::vector<std::string>	bxgi::CSectionLinesFormat<FormatClass, EntryClass, SectionEnum, OtherEntryClass, SectionEntryClass, DataEntryClass>::getModelNames(void)
{
	std::vector<std::string> vecModelNames;
	for (auto it : getSectionEntries())
	{
		for (EntryClass *pFormatEntry : it.second)
		{
			if (pFormatEntry->getEntryType() == SECTION_LINES_ENTRY_DATA)
			{
				std::string strModelName = CString2::toUpperCase(((DataEntryClass*)pFormatEntry)->getModelName());
				if (strModelName != "")
				{
					vecModelNames.push_back(strModelName);
				}
			}
		}
	}
	return vecModelNames;
}

template<class FormatClass, class EntryClass, typename SectionEnum, class OtherEntryClass, class SectionEntryClass, class DataEntryClass>
std::vector<std::string>	bxgi::CSectionLinesFormat<FormatClass, EntryClass, SectionEnum, OtherEntryClass, SectionEntryClass, DataEntryClass>::getTXDNames(void)
{
	std::vector<std::string> vecTXDNames;
	for (auto it : getSectionEntries())
	{
		for (EntryClass *pFormatEntry : it.second)
		{
			if (pFormatEntry->getEntryType() == SECTION_LINES_ENTRY_DATA)
			{
				std::string strTXDName = CString2::toUpperCase(((DataEntryClass*)pFormatEntry)->getTXDName());
				if (strTXDName != "")
				{
					vecTXDNames.push_back(strTXDName);
				}
			}
		}
	}
	return vecTXDNames;
}

template<class FormatClass, class EntryClass, typename SectionEnum, class OtherEntryClass, class SectionEntryClass, class DataEntryClass>
std::vector<std::string>	bxgi::CSectionLinesFormat<FormatClass, EntryClass, SectionEnum, OtherEntryClass, SectionEntryClass, DataEntryClass>::getTXDNamesFromModelNames(std::vector<std::string>& vecModelNames)
{
	std::vector<std::string> vecTextureNames;
	for (auto strModelName : vecModelNames)
	{
		vecTextureNames.push_back(getTXDNameFromModelName(strModelName));
	}
	return vecTextureNames;
}

template<class FormatClass, class EntryClass, typename SectionEnum, class OtherEntryClass, class SectionEntryClass, class DataEntryClass>
std::string			bxgi::CSectionLinesFormat<FormatClass, EntryClass, SectionEnum, OtherEntryClass, SectionEntryClass, DataEntryClass>::getTXDNameFromModelName(std::string strModelName)
{
	strModelName = CString2::toUpperCase(strModelName);
	for (auto it : getSectionEntries())
	{
		for (EntryClass *pFormatEntry : it.second)
		{
			if (pFormatEntry->getEntryType() == SECTION_LINES_ENTRY_DATA && strModelName == CString2::toUpperCase(((DataEntryClass*)pFormatEntry)->getModelName()))
			{
				return ((DataEntryClass*)pFormatEntry)->getTXDName();
			}
		}
	}
	return "";
}

template<class FormatClass, class EntryClass, typename SectionEnum, class OtherEntryClass, class SectionEntryClass, class DataEntryClass>
std::vector<EntryClass*>	bxgi::CSectionLinesFormat<FormatClass, EntryClass, SectionEnum, OtherEntryClass, SectionEntryClass, DataEntryClass>::getEntriesByModelName(std::string strModelName)
{
	strModelName = CString2::toUpperCase(strModelName);
	std::vector<EntryClass*> vecFormatEntries;
	for (auto it : getSectionEntries())
	{
		for (EntryClass *pFormatEntry : it.second)
		{
			if (pFormatEntry->getEntryType() == SECTION_LINES_ENTRY_DATA && strModelName == CString2::toUpperCase(((DataEntryClass*)pFormatEntry)->getModelName()))
			{
				vecFormatEntries.push_back(pFormatEntry);
			}
		}
	}
	return vecFormatEntries;
}

template<class FormatClass, class EntryClass, typename SectionEnum, class OtherEntryClass, class SectionEntryClass, class DataEntryClass>
std::vector<EntryClass*>	bxgi::CSectionLinesFormat<FormatClass, EntryClass, SectionEnum, OtherEntryClass, SectionEntryClass, DataEntryClass>::getEntriesByTXDName(std::string strTXDName)
{
	strTXDName = CString2::toUpperCase(strTXDName);
	std::vector<EntryClass*> vecFormatEntries;
	for (auto it : getSectionEntries())
	{
		for (EntryClass *pFormatEntry : it.second)
		{
			if (pFormatEntry->getEntryType() == SECTION_LINES_ENTRY_DATA && strTXDName == CString2::toUpperCase(((DataEntryClass*)pFormatEntry)->getTXDName()))
			{
				vecFormatEntries.push_back(pFormatEntry);
			}
		}
	}
	return vecFormatEntries;
}

template<class FormatClass, class EntryClass, typename SectionEnum, class OtherEntryClass, class SectionEntryClass, class DataEntryClass>
template<class EntryClass2>
std::vector<EntryClass2*>	bxgi::CSectionLinesFormat<FormatClass, EntryClass, SectionEnum, OtherEntryClass, SectionEntryClass, DataEntryClass>::getEntriesBySection(SectionEnum eSectionValue)
{
	std::vector<EntryClass2*> vecDerivedEntries;
	for (auto it : getSectionEntries())
	{
		for (EntryClass *pFormatEntry : it.second)
		{
			if (pFormatEntry->getEntryType() == SECTION_LINES_ENTRY_DATA && it.first == eSectionValue)
			{
				vecDerivedEntries.push_back(((EntryClass2*)pFormatEntry));
			}
		}
	}
	return vecDerivedEntries;
}

template<class FormatClass, class EntryClass, class DataEntryClass>
bool						sortSectionLinesEntries_ObjectID(EntryClass *pFormatEntry1, EntryClass *pFormatEntry2) // todo - namespace
{
	// data lines
	if (pFormatEntry1->getEntryType() == SECTION_LINES_ENTRY_DATA && pFormatEntry2->getEntryType() == SECTION_LINES_ENTRY_DATA)
	{
		return ((DataEntryClass*)pFormatEntry1)->getObjectId() < ((DataEntryClass*)pFormatEntry2)->getObjectId();
	}

	// comments at top
	if (pFormatEntry1->getEntryType() == SECTION_LINES_ENTRY_OTHER && pFormatEntry2->getEntryType() == SECTION_LINES_ENTRY_OTHER)
	{
		return false;
	}
	else if (pFormatEntry1->getEntryType() == SECTION_LINES_ENTRY_OTHER)
	{
		return true;
	}

	// fallback
	return false;
}

template<class FormatClass, class EntryClass, typename SectionEnum, class OtherEntryClass, class SectionEntryClass, class DataEntryClass>
void				bxgi::CSectionLinesFormat<FormatClass, EntryClass, SectionEnum, OtherEntryClass, SectionEntryClass, DataEntryClass>::sortAllSectionsByObjectId(void)
{
	for (auto it : getSectionEntries())
	{
		std::sort(it.second.begin(), it.second.end(), sortSectionLinesEntries_ObjectID<FormatClass, EntryClass, DataEntryClass>);
	}
};

#endif