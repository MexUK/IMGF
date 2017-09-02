#pragma once

#include "nsimgf.h"
#include <ObjIdl.h>
#include <vector>

struct imgf::CDraggableFile;
class CFile;

class imgf::DropSource // todo : protected COleDataSource
{
public:
	void							StartDragging(void);
	void							setDraggableFiles(std::vector<CDraggableFile*> vecDraggableFiles) { m_vecDraggableFiles = vecDraggableFiles; }
	void							clearDraggableFiles(void);

protected:
	virtual void					CompleteMove() {}
	virtual BOOL					OnRenderFileData(LPFORMATETC lpFormatEtc, ::CFile* pFile);

private:
	std::vector<CDraggableFile*>	m_vecDraggableFiles;
};