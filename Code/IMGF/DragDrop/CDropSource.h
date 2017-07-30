#ifndef CDropSource_H
#define CDropSource_H

#include <ObjIdl.h>
#include <string>
#include <vector>

struct CDraggableFile;
class CFile;

class CDropSource // todo : protected COleDataSource
{
public:
	void							StartDragging(void);
	void							setDraggableFiles(std::vector<CDraggableFile*> vecDraggableFiles) { m_vecDraggableFiles = vecDraggableFiles; }
	void							clearDraggableFiles(void);

protected:
	virtual void					CompleteMove() {};
	virtual BOOL					OnRenderFileData(LPFORMATETC lpFormatEtc, CFile* pFile);

private:
	std::vector<CDraggableFile*>	m_vecDraggableFiles;
};

#endif