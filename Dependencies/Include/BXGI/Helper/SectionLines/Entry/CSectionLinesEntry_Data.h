#ifndef CSectionLinesEntry_Data_H
#define CSectionLinesEntry_Data_H

#include "bxgi.h"
#include "Type/Types.h"
#include "Games/eGameFlag.h"
#include <string>

class bxgi::CSectionLinesEntry_Data
{
public:
	void						setFormatGames(uint32 uiFormatGames) { m_uiFormatGames = uiFormatGames; }
	uint32						getFormatGames(void) { return m_uiFormatGames; }
	bool						doesSupportFormatGame(bxgi::eGameFlag eGameFlagValue) { return (m_uiFormatGames & eGameFlagValue) == eGameFlagValue; }
	void						addFormatGame(bxgi::eGameFlag eGameFlagValue) { m_uiFormatGames |= eGameFlagValue; }
	void						removeFormatGame(bxgi::eGameFlag eGameFlagValue) { m_uiFormatGames &= ~eGameFlagValue; }

	virtual uint32				getObjectId(void) { return -1; }
	virtual std::string&		getModelName(void) { static std::string strBlank = ""; return strBlank; }
	virtual std::string&		getTXDName(void) { static std::string strBlank = ""; return strBlank; }

private:
	uint32						m_uiFormatGames;
};

#endif