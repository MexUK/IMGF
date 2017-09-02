#include "LSTFormat.h"
#include "LSTSection.h"
#include "LSTEntry.h"
#include "Static/CString2.h"
#include "Static/CStdVector.h"
#include "Stream/CDataReader.h"

using namespace std;
using namespace bxcf;
using namespace imgf;

void						LSTFormat::unload(void)
{
	removeAllEntries();
}

void						LSTFormat::unserialize(void)
{
	CDataReader *pDataReader = CDataReader::get();
	pDataReader->readAndStoreLines();
	while (pDataReader->iterateLines() && pDataReader->getUserData() == 0) // LST format user data for data reader: 0 = normal processing, 1 = stop processing (e.g. found END in file)
	{
		unserializeLine();
	}
}

void						LSTFormat::unserializeLine(void)
{
	// initialize
	static LSTSection *pLSTActiveSection = nullptr;
	CDataReader *pDataReader = CDataReader::get();
	string strActiveLine = *pDataReader->getActiveLine();

	// remove comment from end of line ( comment characters: # ; )
	string strComment = "";
	size_t uiCommentPosition = strActiveLine.find('#');
	if (uiCommentPosition != string::npos)
	{
		strComment = strActiveLine.substr(uiCommentPosition + 1);
		strActiveLine = strActiveLine.substr(0, uiCommentPosition);
	}
	uiCommentPosition = strActiveLine.find(';');
	if (uiCommentPosition != string::npos)
	{
		strComment = strActiveLine.substr(uiCommentPosition + 1);
		strActiveLine = strActiveLine.substr(0, uiCommentPosition);
	}

	// trim line
	strActiveLine = CString2::trim(strActiveLine);
	
	// process line
	if (strActiveLine == "")
	{
		// blank line
	}
	else
	{
		if (strActiveLine.c_str()[0] == '[')
		{
			// line is a section
			LSTSection *pLSTFileSection = new LSTSection;
			pLSTFileSection->setName(CString2::trim(strActiveLine.substr(1, strActiveLine.length() - 2)));
			pLSTActiveSection = pLSTFileSection;
			addEntry(pLSTFileSection);

			if (CString2::toUpperCase(pLSTFileSection->getName()) == "END")
			{
				pDataReader->setUserData(1); // stop processing LST format
			}
		}
		else
		{
			// line is an entry
			deque<string> deqTokens = CStdVector::convertVectorToDeque(CString2::split(strActiveLine, " "));

			LSTEntry *pLSTEntry = new LSTEntry;
			pLSTEntry->setName(deqTokens[0]);
			deqTokens.pop_front();
			pLSTEntry->setValues(deqTokens);
			pLSTActiveSection->addEntry(pLSTEntry);
		}
	}
}

void						LSTFormat::serialize(void)
{
	// todo - serialize LST format
}

LSTSection*				LSTFormat::getEntryByName(string strName)
{
	strName = CString2::toUpperCase(strName);
	for (auto pSection : getEntries())
	{
		if (CString2::toUpperCase(pSection->getName()) == strName)
		{
			return pSection;
		}
	}
	return nullptr;
}

bool						LSTFormat::doesEntryExistByName(string strName)
{
	return getEntryByName(strName) != nullptr;
}