#pragma once

#include "nsimgf.h"
#include <ObjIdl.h>
#include <vector>

struct imgf::DraggableFile;
class File;

class imgf::DropSource // todo : protected COleDataSource
{
public:
	void							StartDragging(void);
	void							setDraggableFiles(std::vector<DraggableFile*> vecDraggableFiles) { m_vecDraggableFiles = vecDraggableFiles; }
	void							clearDraggableFiles(void);

protected:
	virtual void					CompleteMove() {}
	virtual BOOL					OnRenderFileData(LPFORMATETC lpFormatEtc, ::File* pFile);

private:
	std::vector<DraggableFile*>	m_vecDraggableFiles;
};