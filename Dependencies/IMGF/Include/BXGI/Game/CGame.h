#pragma once

#include "nsbxgi.h"
#include "Game/EGame.h"
#include <string>

class bxgi::CGame
{
public:
	CGame(void);

	void					unload(void) {}

	void					setGameId(EGame uiGameId) { m_uiGameId = uiGameId; }
	EGame					getGameId(void) { return m_uiGameId; }

	void					setName(std::string& strName) { m_strName = strName; }
	std::string&			getName(void) { return m_strName; }

private:
	EGame					m_uiGameId;
	std::string				m_strName;
};