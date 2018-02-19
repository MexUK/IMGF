#include "RadarEditor.h"
#include "BXGX.h"
#include "Format/IMG/Regular/IMGFormatVersion1.h"
#include "Format/IMG/Regular/IMGFormatVersion2.h"
#include "Format/IMG/Regular/IMGFormatVersion3.h"
#include "Format/IMG/Regular/IMGFormatVersionFastman92.h"

using namespace std;
using namespace bxcf::fileType;
using namespace bxgi;
using namespace bxgx;
using namespace bxgx::events;
using namespace imgf;

void									RadarEditor::init(void)
{
	setEditorFileType(IMG);
	setEditorFileFormats({ "IMG" });
	//setImportEditorFileFormats({ "BMP", "PNG", "GIF", "JPG", "JPEG", "ICO", "CUR", "DDS" });
	setImportEditorFileFormats({ "TXD", "WTD" });

	m_pEditorButton = (Button*)m_pMainWindow->getItemById(1012);

	Editor::init();
}

// events
void									RadarEditor::bindEvents(void)
{
	Editor::bindEvents();
}

void									RadarEditor::unbindEvents(void)
{
	Editor::unbindEvents();
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
		if (!pRadarEditorTab->init(false))
		{
			removeEditorTab(pRadarEditorTab);
			return nullptr;
		}
	}
	return pRadarEditorTab;
}

RadarEditorTab*							RadarEditor::addBlankEditorTab(string& strFilePath)
{
	return addBlankEditorTab(strFilePath, IMG_1);
}

RadarEditorTab*							RadarEditor::addBlankEditorTab(string& strFilePath, EIMGVersion uiIMGVersion)
{
	RadarEditorTab *pRadarEditorTab;

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
		if (uiIMGVersion == IMG_3)
		{
			pRadarEditorTab->getIMGFile()->setEncrypted(true);
		}
		pRadarEditorTab->init(true);
	}

	return pRadarEditorTab;
}