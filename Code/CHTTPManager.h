#ifndef CHTTPManager_H
#define CHTTPManager_H

#include "Type/Types.h"
#include "Object/CSingleton.h"
#include "Object/CManager.h"
#include "HappyHTTP.h"
#include <string>

void		OnBegin(const happyhttp::Response* r, void* userdata);
void		OnData(const happyhttp::Response* r, void* userdata, const uint8* data, int n);
void		OnComplete(const happyhttp::Response* r, void* userdata);

class CHTTPManager : public mcore::CManager, public mcore::CSingleton<CHTTPManager>
{
public:
	void						init(void);
	void						uninit(void);

	std::string					getFileContent(std::string strURL);
	
	bool						m_bConnectionComplete;
	std::string					m_strReceivedData;
};

#endif