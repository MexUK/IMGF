#pragma once

#include "nsbxgi.h"
#include "Game/EPlatformedGame.h"
#include <string>

class bxgi::PlatformedGame
{
public:
	PlatformedGame(void);

	void					unload(void) {}

	void					setPlatformedGameId(EPlatformedGame uiPlatformedGameId) { m_uiPlatformedGameId = uiPlatformedGameId; }
	EPlatformedGame			getPlatformedGameId(void) { return m_uiPlatformedGameId; }

	void					setText(std::string& strText) { m_strText = strText; }
	std::string&			getText(void) { return m_strText; }

private:
	EPlatformedGame			m_uiPlatformedGameId;
	std::string				m_strText;
};