#ifndef HTTP_H
#define HTTP_H

#include "Type/Types.h"
#include "Object/CSingleton.h"
#include "Object/CManager.h"
#include "Protocol/HTTP/HappyHTTP/happyhttp.h"
#include <string>

// this code has been taken from happyhttp lib and has been modified.

void		OnBegin(const happyhttp::Response* r, void* userdata);
void		OnData(const happyhttp::Response* r, void* userdata, const uint8* data, int n);
void		OnComplete(const happyhttp::Response* r, void* userdata);

class HTTP : public bxcf::CManager, public bxcf::CSingleton<HTTP>
{
public:
	void						init(void);
	void						uninit(void);

	std::string					getFileContent(std::string strURL);
	
	bool						m_bConnectionComplete;
	std::string					m_strReceivedData;
};

#endif