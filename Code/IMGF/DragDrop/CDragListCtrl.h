#pragma once

#include "nsimgf.h"
#include "CDropSource.h"
//#include <Windows.h>
#include <string>

struct imgf::CDraggableFile
{
	CDraggableFile(void) :
		m_bLogged(false) {};

	std::string						m_strFileName;
	std::string						m_strFileData;
	bool							m_bLogged;
};

class imgf::CDragListCtrl // todo : public CListCtrl
{
public:
	/*
	todo
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnBeginDrag(void);
	*/

private:
	CDropSource						m_dropSource;
	std::vector<CDraggableFile*>	m_vecDraggableFiles;
};