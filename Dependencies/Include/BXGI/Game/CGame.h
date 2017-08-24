#ifndef CGame_H
#define CGame_H

#include "bxgi.h"
#include "Games/eGame.h"
#include <string>

class bxgi::CGame
{
public:
	void					unload(void) {}

	void					setGameId(eGame eGameValue) { m_eGameId = eGameValue; }
	eGame					getGameId(void) { return m_eGameId; }

	void					setName(std::string strName) { m_strName = strName; }
	std::string				getName(void) { return m_strName; }

	void					setLocalizationKey(std::string strName) { m_strLocalizationKey = strName; }
	std::string				getLocalizationKey(void) { return m_strLocalizationKey; }

private:
	eGame					m_eGameId;
	std::string				m_strName;
	std::string				m_strLocalizationKey;
};

#endif