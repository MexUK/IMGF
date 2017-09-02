#pragma once

#include "nsimgf.h"
#include "DropSource.h"
//#include <Windows.h>
#include <string>

struct imgf::CDraggableFile
{
	CDraggableFile(void);

	std::string						m_strFileName;
	std::string						m_strFileData;
	bool							m_bLogged;
};

class imgf::DragListCtrl // todo : public CListCtrl
{
public:
	/*
	todo
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnBeginDrag(void);
	*/

private:
	DropSource						m_dropSource;
	std::vector<CDraggableFile*>	m_vecDraggableFiles;
};