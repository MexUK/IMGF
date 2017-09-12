#pragma once

#include "nsimgf.h"
#include "nsbxgi.h"
#include "Format/IDE/EIDESection.h"
#include <unordered_map>

struct imgf::IDEInputWindowResult
{
	std::unordered_map<uint32, bool>		m_umapCheckBoxStatuses;

	void									getIDESections(std::vector<bxgi::EIDESection>& vecModelSections, std::vector<bxgi::EIDESection>& vecTextureSections)
	{
		for (auto it : m_umapCheckBoxStatuses)
		{
			uint32 uiCheckBoxId = it.first;

			if (uiCheckBoxId >= 300 && uiCheckBoxId < 400)
			{
				vecModelSections.push_back((bxgi::EIDESection)(uiCheckBoxId - 300));
			}
			else if (uiCheckBoxId >= 400 && uiCheckBoxId <= 500)
			{
				vecTextureSections.push_back((bxgi::EIDESection)(uiCheckBoxId - 400));
			}
		}
	}
};