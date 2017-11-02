#include "RadarEditor.h"
#include "BXGX.h"
#include "Format/IMG/Regular/IMGFormatVersion1.h"
#include "Format/IMG/Regular/IMGFormatVersion2.h"
#include "Format/IMG/Regular/IMGFormatVersion3.h"
#include "Format/IMG/Regular/IMGFormatVersionFastman92.h"

using namespace std;
using namespace bxgi;
using namespace bxgx;
using namespace bxgx::events;
using namespace imgf;

void									RadarEditor::init(void)
{
	setEditorFileFormats({ "IMG", "TXD", "WTD" });
	setImportEditorFileFormats({ "BMP", "PNG", "GIF", "JPG", "JPEG", "ICO", "CUR", "DDS" });

	Editor::init();
}

// events
void									RadarEditor::bindEvents(void)
{
	bindEvent(BEFORE_RENDER, &RadarEditor::renderBefore);

	Editor::bindEvents();

	if (m_pActiveEditorTab)
	{
		m_pActiveEditorTab->bindEvents();
	}
}

void									RadarEditor::unbindEvents(void)
{
	unbindEvent(BEFORE_RENDER, &RadarEditor::renderBefore);

	Editor::unbindEvents();

	if (m_pActiveEditorTab)
	{
		m_pActiveEditorTab->unbindEvents();
	}
}

// render
void									RadarEditor::renderBefore(void)
{
	GraphicsLibrary *pGFX = BXGX::get()->getGraphicsLibrary();

	if (m_pMainWindow->getActiveEditor() != m_pMainWindow->getRadarEditor() || BXGX::get()->getEventWindow() != m_pMainWindow)
	{
		return;
	}

	m_pWindow->resetRenderingStyleGroups();
	m_pWindow->resetRenderingControlComponent();
	m_pWindow->resetRenderingStyleFragment();
	m_pWindow->resetRenderingStyleStatus();

	if (m_pActiveEditorTab)
	{
		((RadarEditorTab*)m_pActiveEditorTab)->renderEntryList();
		((RadarEditorTab*)m_pActiveEditorTab)->render_Type1();
	}
}

// add editor tab
RadarEditorTab*							RadarEditor::addEditorTab(string& strFilePath)
{
	IMGFormat imgFormat(strFilePath);
	if (!imgFormat.readMetaData())
	{
		return nullptr;
	}

	RadarEditorTab *pRadarEditorTab;

	switch (imgFormat.getVersion())
	{
	case IMG_1:
		pRadarEditorTab = Editor::_addEditorTab<IMGFormatVersion1, RadarEditorTab>(strFilePath, false);
		break;
	case IMG_2:
		pRadarEditorTab = Editor::_addEditorTab<IMGFormatVersion2, RadarEditorTab>(strFilePath, false);
		break;
	case IMG_3:
		pRadarEditorTab = Editor::_addEditorTab<IMGFormatVersion3, RadarEditorTab>(strFilePath, false);
		break;
	case IMG_FASTMAN92:
		pRadarEditorTab = Editor::_addEditorTab<IMGFormatVersionFastman92, RadarEditorTab>(strFilePath, false);
		break;
	default:
		pRadarEditorTab = nullptr;
		break;
	}

	if (pRadarEditorTab)
	{
		//pRadarEditorTab->setIMGEditor(this);
		pRadarEditorTab->setIMGFile((IMGFormat*)pRadarEditorTab->getFile());
		if (!pRadarEditorTab->init())
		{
			removeEditorTab(pRadarEditorTab);
			return nullptr;
		}
	}
	return pRadarEditorTab;
}

RadarEditorTab*							RadarEditor::addBlankEditorTab(string& strFilePath)
{
	RadarEditorTab *pRadarEditorTab;

	EIMGVersion uiIMGVersion = bxgi::EIMGVersion::IMG_1;

	switch (uiIMGVersion)
	{
	case IMG_1:
		pRadarEditorTab = Editor::_addEditorTab<IMGFormatVersion1, RadarEditorTab>(strFilePath, true);
		break;
	case IMG_2:
		pRadarEditorTab = Editor::_addEditorTab<IMGFormatVersion2, RadarEditorTab>(strFilePath, true);
		break;
	case IMG_3:
		pRadarEditorTab = Editor::_addEditorTab<IMGFormatVersion3, RadarEditorTab>(strFilePath, true);
		break;
	case IMG_FASTMAN92:
		pRadarEditorTab = Editor::_addEditorTab<IMGFormatVersionFastman92, RadarEditorTab>(strFilePath, true);
		break;
	default:
		pRadarEditorTab = nullptr;
		break;
	}

	if (pRadarEditorTab)
	{
		//pRadarEditorTab->setIMGEditor(this);
		pRadarEditorTab->setIMGFile((IMGFormat*)pRadarEditorTab->getFile());
		pRadarEditorTab->init();
	}

	return pRadarEditorTab;
}