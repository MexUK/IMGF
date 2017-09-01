#pragma once

#include "nsimgf.h"
#include "nsbxcf.h"
#include "nsbxgx.h"
#include "Event/Events.h"

class bxgx::CMenuItem;
class bxgx::CButton;
class imgf::CMainWindow;
class imgf::CTaskDispatchManager;

class imgf::CInputManager : public bxcf::EventBindable
{
public:
	void					init(void);

private:
	void					bindEvents(void);

public:
	void					onPressButton(bxgx::CButton *pMenuItem);
	void					onPressMenuItem(bxgx::CMenuItem *pMenuItem);

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

	void					_import(void);
	void					_export(void);
	void					quickExport(void);
	void					rename(void);
	void					replace(void);
	void					remove(void);
	void					merge(void);
	void					split(void);
	void					convert(void);
	void					select(void);
	void					sort(void);
	void					lst(void);

	void					settings(void);

private:
	CMainWindow*			m_pMainWindow;
	CTaskDispatchManager*	m_pTaskDispatchManager;
};