#ifndef CRasterDataFormat_H
#define CRasterDataFormat_H

#include "mcore.h"
#include "Image/eRasterDataFormat.h"
#include <string>

class mcore::CRasterDataFormat
{
public:
	void						unload(void) {}

	void						setRasterDataFormatId(eRasterDataFormat eRasterDataFormatValue) { m_eRasterDataFormatId = eRasterDataFormatValue; }
	eRasterDataFormat			getRasterDataFormatId(void) { return m_eRasterDataFormatId; }

	void						setLocalizationKey(std::string strLocalizationKey) { m_strLocalizationKey = strLocalizationKey; }
	std::string					getLocalizationKey(void) { return m_strLocalizationKey; }

	void						setText(std::string strText) { m_strText = strText; }
	std::string					getText(void) { return m_strText; }
	std::string					getTextForMenu(void);

private:
	eRasterDataFormat			m_eRasterDataFormatId;
	std::string					m_strText;
	std::string					m_strLocalizationKey;		// e.g. TextureFormat_1
};

#endif