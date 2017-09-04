#pragma once

#include "nsbxcf.h"
#include "Image/ERasterDataFormat.h"
#include <string>

class bxcf::CRasterDataFormat
{
public:
	void						unload(void) {}

	void						setRasterDataFormatId(ERasterDataFormat ERasterDataFormatValue) { m_ERasterDataFormatId = ERasterDataFormatValue; }
	ERasterDataFormat			getRasterDataFormatId(void) { return m_ERasterDataFormatId; }

	void						setLocalizationKey(std::string strLocalizationKey) { m_strLocalizationKey = strLocalizationKey; }
	std::string					getLocalizationKey(void) { return m_strLocalizationKey; }

	void						setText(std::string strText) { m_strText = strText; }
	std::string					getText(void) { return m_strText; }
	std::string					getTextForMenu(void);

private:
	ERasterDataFormat			m_ERasterDataFormatId;
	std::string					m_strText;
	std::string					m_strLocalizationKey;		// e.g. TextureFormat_1
};