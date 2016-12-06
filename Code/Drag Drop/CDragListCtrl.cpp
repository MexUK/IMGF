#pragma warning(disable : 4005)

#include "CDragListCtrl.h"
#include "Format/RockstarGames/IMG/CIMGEntry.h"
#include "Type/String/CString2.h"
#include "Globals.h"
#include "CIMGF.h"
#include "GUI/Editors/Tab/CIMGEditorTab.h"
#include "Format/RockstarGames/IMG/CIMGFormat.h"
#include <string>

using namespace std;
using namespace mcore;

/*
todo

BEGIN_MESSAGE_MAP(CDragListCtrl, CListCtrl)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

void		CDragListCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	CListCtrl::OnLButtonDown(nFlags, point);
}

void		CDragListCtrl::OnBeginDrag(void)
{
	uint32 i = 0;
	for (auto pDraggableFile : m_vecDraggableFiles)
	{
		if (pDraggableFile != nullptr)
		{
			delete pDraggableFile;
			m_vecDraggableFiles[i] = nullptr;
		}
		i++;
	}
	m_vecDraggableFiles.clear();
	//m_dropSource.clearDraggableFiles();

	//vector<CDraggableFile*> vecDraggableFiles;

	POSITION pos = GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		return;
	}
	CIMGEntry *pIMGEntry;
	while (pos)
	{
		int nItem = GetNextSelectedItem(pos);
		pIMGEntry = (CIMGEntry*)GetItemData(nItem);

		CDraggableFile *pDraggableFile = new CDraggableFile;
		pDraggableFile->m_strFileName = pIMGEntry->getEntryName();
		pDraggableFile->m_strFileData = pIMGEntry->getEntryData();
		m_vecDraggableFiles.push_back(pDraggableFile);
	}

	m_dropSource.setDraggableFiles(m_vecDraggableFiles);
	m_dropSource.StartDragging();
}
*/