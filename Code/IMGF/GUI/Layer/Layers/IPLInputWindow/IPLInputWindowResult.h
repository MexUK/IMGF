#pragma once

#include "nsimgf.h"
#include "nsbxgi.h"
#include "Format/IPL/EIPLSection.h"
#include <unordered_map>

struct imgf::IPLInputWindowResult
{
	std::unordered_map<uint32, bool>		m_umapCheckBoxStatuses;

	void									getIPLSections(std::vector<bxgi::EIPLSection>& vecModelSections, std::vector<bxgi::EIPLSection>& vecTextureSections)
	{
		for (auto it : m_umapCheckBoxStatuses)
		{
			uint32 uiCheckBoxId = it.first;

			if (uiCheckBoxId >= 300 && uiCheckBoxId < 400)
			{
				vecModelSections.push_back((bxgi::EIPLSection)(uiCheckBoxId - 300));
			}
			else if (uiCheckBoxId >= 400 && uiCheckBoxId <= 500)
			{
				vecTextureSections.push_back((bxgi::EIPLSection)(uiCheckBoxId - 400));
			}
		}
	}
};