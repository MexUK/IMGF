#pragma warning(disable : 4005)

#include "DragListCtrl.h"
#include "Format/IMG/Regular/IMGEntry.h"
#include "Static/String.h"
#include "Globals.h"
#include "IMGF.h"
#include "GUI/Editors/Tab/IMGEditorTab.h"
#include "Format/IMG/Regular/IMGFormat.h"
#include <string>

using namespace std;
using namespace bxcf;
using namespace imgf;

CDraggableFile::CDraggableFile(void) :
	m_bLogged(false)
{
}

/*
todo

BEGIN_MESSAGE_MAP(DragListCtrl, CListCtrl)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

void		DragListCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	CListCtrl::OnLButtonDown(nFlags, point);
}

void		DragListCtrl::OnBeginDrag(void)
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
	IMGEntry *pIMGEntry;
	while (pos)
	{
		int nItem = GetNextSelectedItem(pos);
		pIMGEntry = (IMGEntry*)GetItemData(nItem);

		CDraggableFile *pDraggableFile = new CDraggableFile;
		pDraggableFile->m_strFileName = pIMGEntry->getEntryName();
		pDraggableFile->m_strFileData = pIMGEntry->getEntryData();
		m_vecDraggableFiles.push_back(pDraggableFile);
	}

	m_dropSource.setDraggableFiles(m_vecDraggableFiles);
	m_dropSource.StartDragging();
}
*/