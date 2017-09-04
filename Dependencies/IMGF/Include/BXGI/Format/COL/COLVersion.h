#pragma once

#include "nsbxgi.h"
#include "ECOLVersion.h"
#include <string>

class bxgi::COLVersion
{
public:
	void				unload(void) {}

	void				setVersionId(bxgi::ECOLVersion eVersionId) { m_uiVersionId = eVersionId; }
	bxgi::ECOLVersion	getVersionId(void) { return m_uiVersionId; }

	void				setText(std::string strText) { m_strText = strText; }
	std::string			getText(void) { return m_strText; }

	void					setGames(std::vector<bxgi::EGame>& vecGames) { m_vecGames = vecGames; }
	std::vector<EGame>&		getGames(void) { return m_vecGames; }

private:
	bxgi::ECOLVersion	m_uiVersionId;
	std::string			m_strText;
	std::vector<EGame>	m_vecGames;
};