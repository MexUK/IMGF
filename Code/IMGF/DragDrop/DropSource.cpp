#pragma warning(disable : 4005)

#include "DropSource.h"
#include "DragListCtrl.h"
#include "Static/String2.h"
#include "Globals.h"
#include "IMGF.h"
#include "GUI/Editors/Tab/IMGEditorTab.h"
#include "Static/Debug.h"
#include "Format/IMG/Regular/IMGEntry.h"
#include "Localization/LocalizationManager.h"

using namespace std;
using namespace bxcf;
using namespace imgf;

void		DropSource::StartDragging(void)
{
	/*
	todo

	UINT uFileCount = m_vecDraggableFiles.size();
	INT uBuffSize = sizeof(FILEGROUPDESCRIPTOR) + (uFileCount * sizeof(FILEDESCRIPTOR));
	HGLOBAL hFileDescriptor = GlobalAlloc(GHND | GMEM_SHARE, uBuffSize);
	if (hFileDescriptor)
	{
		FILEGROUPDESCRIPTOR* pGroupDescriptor = (FILEGROUPDESCRIPTOR*)GlobalLock(hFileDescriptor);
		pGroupDescriptor->cItems = uFileCount;
		if (pGroupDescriptor)
		{
			FILEDESCRIPTOR* pFileDescriptorArray = (FILEDESCRIPTOR*)((LPBYTE)pGroupDescriptor + sizeof(UINT));

			int index = 0;
			for (auto pDraggableFile : m_vecDraggableFiles)
			{
				ZeroMemory(&pFileDescriptorArray[index], sizeof(FILEDESCRIPTOR));
				lstrcpy(pFileDescriptorArray[index].cFileName, String2::convertStdStringToStdWString(pDraggableFile->m_strFileName).c_str());
				//m_DataSrc.m_Files.Add(pFileDescriptorArray[index].cFileName);
				pFileDescriptorArray[index].dwFlags = FD_FILESIZE | FD_ATTRIBUTES;
				pFileDescriptorArray[index].nFileSizeLow = pDraggableFile->m_strFileData.length();
				pFileDescriptorArray[index].nFileSizeHigh = 0;
				pFileDescriptorArray[index].dwFileAttributes = FILE_ATTRIBUTE_NORMAL;

				index++;
			}
		}
		else
		{
			GlobalFree(hFileDescriptor);
			return;
		}
	}
	else
	{
		return;
	}
	GlobalUnlock(hFileDescriptor);

	FORMATETC etcDescriptor = { RegisterClipboardFormat(CFSTR_FILEDESCRIPTOR), NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
	CacheGlobalData(RegisterClipboardFormat(CFSTR_FILEDESCRIPTOR), hFileDescriptor, &etcDescriptor);

	FORMATETC etcContents = { RegisterClipboardFormat(CFSTR_FILECONTENTS), NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
	DelayRenderFileData(RegisterClipboardFormat(CFSTR_FILECONTENTS), &etcContents);

	DROPEFFECT dwEffect = DoDragDrop(DROPEFFECT_COPY | DROPEFFECT_MOVE);
	*/
}

BOOL DropSource::OnRenderFileData(LPFORMATETC lpFormatEtc, ::File* pFile)
{
	/*
	todo

	if (lpFormatEtc->cfFormat == RegisterClipboardFormat(CFSTR_FILECONTENTS))
	{
		if (lpFormatEtc->lindex == -1)
		{
			return FALSE;
		}
		CDraggableFile *pDraggableFile = m_vecDraggableFiles[lpFormatEtc->lindex];
		pFile->Write(pDraggableFile->m_strFileData.c_str(), pDraggableFile->m_strFileData.length());

		if (!pDraggableFile->m_bLogged)
		{
			pDraggableFile->m_bLogged = true;
			getIMGF()->getEntryListTab()->log(LocalizationManager::get()->getTranslatedFormattedText("Log_1", m_vecDraggableFiles[lpFormatEtc->lindex]->m_strFileName.c_str()));
		}
	}
	*/

	return TRUE;
}

void		DropSource::clearDraggableFiles(void)
{
	/*
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
	*/
	// objects stored in m_vecDraggableFiles should be deleted in DragListCtrl::OnBeginDrag().
	m_vecDraggableFiles.clear();
}