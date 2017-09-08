#pragma once

#include "nsimgf.h"
#include "nsbxcf.h"
#include "nsbxgx.h"
#include "Event/Events.h"

class bxgx::MenuItem;
class bxgx::Button;
class imgf::MainWindow;
class imgf::Tasks;

class imgf::InputManager : public bxcf::EventBindable
{
public:
	void					init(void);

private:
	void					bindEvents(void);

public:
	void					onPressButton(bxgx::Button *pMenuItem);
	void					onPressMenuItem(bxgx::MenuItem *pMenuItem);

private:
	void					formats(void);
	void					utility(void);

	void					dat(void);
	void					img(void);
	void					itemDefinition(void);
	void					itemPlacement(void);
	void					models(void);
	void					collisions(void);
	void					textures(void);
	void					animations(void);
	void					radar(void);

	void					open(void);
	void					close(void);
	void					save(void);

	void					importByFiles(void);
	void					importBySingleFolder(void);
	void					importByFolderRecursively(void);

	void					exportSelected(void);
	void					exportAll(void);
	void					quickExport(void);

	void					selectAll(void);
	void					unselectAll(void);
	void					selectInverse(void);




	void					rename(void);
	void					replace(void);
	void					remove(void);
	void					merge(void);
	void					split(void);
	void					convert(void);
	void					sort(void);
	void					lst(void);

	void					settings(void);

private:
	MainWindow*			m_pMainWindow;
	Tasks*	m_pTasks;
};