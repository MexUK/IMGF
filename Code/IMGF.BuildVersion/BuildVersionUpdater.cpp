#include "BuildVersionUpdater.h"
#include "Static/String.h"
#include "Static/File.h"

#define PATH_TO_BUILD_VERSION_H std::string("../../../Code/IMGF/Program/BuildVersion.h") // relative to .vcxproj file

using namespace std;
using namespace bxcf;

int					main(void)
{
	updateMinorBuildNumber();
	
	return 0;
}

void				updateMinorBuildNumber(void)
{
	if (!File::doesFileExist(PATH_TO_BUILD_VERSION_H))
	{
		return;
	}

	uint32
		uiMinorBuildVersion = 0,
		uiNewMinorBuildVersion = 0,
		uiLineIndex = 0;
	string
		strUpdateLinesContaining = "MINOR_BUILD_VERSION";
	vector<string>
		vecFileLines = File::getFileLines(PATH_TO_BUILD_VERSION_H),
		vecNewFileLines;

	vecNewFileLines.resize(vecFileLines.size());

	/*
	printf("AAA\n");
	for (string& strFileLine : vecFileLines)
	{
		printf("BB%sCC\n", strFileLine.c_str());
	}
	printf("\n");
	printf("DDD\n");
	*/

	for(string& strFileLine : vecFileLines)
	{
		if(String::isIn(strFileLine, strUpdateLinesContaining))
		{
			if(uiMinorBuildVersion == 0)
			{
				uiMinorBuildVersion = String::toNumber(String::trim(strFileLine.substr(strFileLine.find(strUpdateLinesContaining) + strUpdateLinesContaining.length())));
				uiNewMinorBuildVersion = uiMinorBuildVersion + 1;
				printf("Minor Build Version: %u", uiNewMinorBuildVersion);
			}
			
			vecNewFileLines[uiLineIndex] = String::replace(strFileLine, String::toString(uiMinorBuildVersion), String::toString(uiNewMinorBuildVersion));
		}
		else
		{
			vecNewFileLines[uiLineIndex] = strFileLine;
		}
		uiLineIndex++;
	}

	File::setFileContent(PATH_TO_BUILD_VERSION_H, String::join(vecNewFileLines, "\n"), false);
}