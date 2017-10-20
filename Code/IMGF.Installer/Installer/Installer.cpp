#include "Installer.h"
#include "Static/Process.h"
#include "Static/DataPath.h"
#include "Static/File.h"
#include "Static/Path.h"
#include "Static/Registry.h"
#include "nsbxgx.h"
#include "BXGX.h"
#include "Event/EInputEvent.h"
#include "Control/Controls/TextBox.h"
#include "Control/Controls/Button.h"
#include "InstallerFile.h"
#include "../../../Compiler/Projects/IMGF.Installer/resource.h"

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace bxgx::events;

Installer::Installer(void) :
	m_pInstallerFiles(nullptr),

	m_pWindow(nullptr),

	m_pLog(nullptr),

	m_pButton1(nullptr),
	m_pButton2(nullptr),
	m_pButton3_1(nullptr),
	m_pButton3_2(nullptr)
{
	m_pInstallerFiles = new InstallerFiles;

	m_strIMGFFileName = "IMG Factory.exe";
}

// initialization
void					Installer::init(void)
{
	DataPath::setAppFolderName("IMGFactory");

	initTheme();
	m_pInstallerFiles->load();
}

void					Installer::initTheme(void)
{
	string
		strThemeData =
		"\n\
.centerText\n\
text center center\n\
\n\
.textSpacing\n\
spacing x 8\n\
spacing y 8\n\
\n\
.window\n\
fill 0 0 0\n\
line 181 230 29\n\
\n\
.titleBar\n\
fill 80 80 80\n\
text 181 230 29\n\
\n\
.titleBarIcon\n\
line 181 230 29\n\
text 181 230 29\n\
\n\
textbox .textSpacing\n\
fill 96 96 96\n\
text 181 230 29\n\
\n\
text\n\
text 181 230 29\n\
\n\
button .centerText\n\
fill 96 96 96\n\
text 181 230 29\n\
";

	StyleManager::get()->setThemeData(strThemeData);
}

// window
void					Installer::openWindow(void)
{
	Vec2u vecWindowSize = Vec2u(530, 280);

	m_pWindow = BXGX::get()->addWindow(vecWindowSize.x, vecWindowSize.y);
	m_pWindow->addTitleBar("IMG Factory Installer - Version 2.0 Alpha");

	Layer *pLayer;

	pLayer = m_pWindow->addLayer(-1, true, 0);
	pLayer->addText(50, 50, 200, 25, "IMG Factory Installer");
	pLayer->addText(50, 80, 200, 25, "Version: 2.0 Alpha");
	m_pButton1 = pLayer->addButton(vecWindowSize.x - 100 - 20, vecWindowSize.y - 25 - 20, 100, 25, "Install");

	pLayer = m_pWindow->addLayer(-1, false, 0);
	pLayer->addText(50, 50, 200, 25, "Log:");
	m_pLog = pLayer->addTextBox(50, 80, 430, 120, "", true);
	m_pLog->setReadOnly(true);

	pLayer = m_pWindow->addLayer(-1, false, 0);
	m_pButton2 = pLayer->addButton(vecWindowSize.x - 100 - 20, vecWindowSize.y - 25 - 20, 100, 25, "Installing..");

	pLayer = m_pWindow->addLayer(-1, false, 0);
	m_pButton3_1 = pLayer->addButton(vecWindowSize.x - 270 - 20, vecWindowSize.y - 25 - 20, 150, 25, "Open IMG Factory");
	m_pButton3_2 = pLayer->addButton(vecWindowSize.x - 100 - 20, vecWindowSize.y - 25 - 20, 100, 25, "Close");

	bindEvent(PRESS_BUTTON, &Installer::onPressButton);
}

// processing
void					Installer::process(void)
{
	BXGX::get()->process();
}

// log
void					Installer::log(string strText)
{
	m_pLog->addText(strText + "\n");
	m_pLog->render();
}

// events
void					Installer::onPressButton(Button *pButton)
{
	if (pButton == m_pButton1)
	{
		// Install
		m_pWindow->getEntryByIndex(0)->setEnabled(false);
		m_pWindow->getEntryByIndex(1)->setEnabled(true);
		m_pWindow->getEntryByIndex(2)->setEnabled(true);

		install();

		m_pWindow->getEntryByIndex(2)->setEnabled(false);
		m_pWindow->getEntryByIndex(3)->setEnabled(true);
	}
	else if (pButton == m_pButton3_1)
	{
		// Open IMG Factory
		Process::startProcess(DataPath::getDataPath() + "Builds/" + m_strIMGFFileName);
	}
	else if (pButton == m_pButton3_2)
	{
		// Close
		ExitProcess(0);
	}
}

// process install
void					Installer::install(void)
{
	log("Starting install.");
	log("");



	log("Creating files..");
	createFiles();

	log("Creating desktop icon..");
	addDesktopIcon();

	log("Adding to start menu..");
	addToStartMenu();

	log("Associating file extension(s)..");
	associateFileExtensions();



	log("");
	log("Completed install.");
}

void					Installer::createFiles(void)
{
	HMODULE hModule = GetModuleHandle(NULL);
	string strIMGFDataFolderPath = DataPath::getDataPath();

	createFile(hModule, IDR_RCDATA22, strIMGFDataFolderPath + "Builds/" + m_strIMGFFileName);
	
	createFile(hModule, IDB_PNG1, strIMGFDataFolderPath + "Images/Logo.png");
	
	createFile(hModule, IDR_RCDATA21, strIMGFDataFolderPath + "Settings/RegularSettings.ini");

	createFile(hModule, IDR_RCDATA6, strIMGFDataFolderPath + "Styles/Main (dark).bxs");
	createFile(hModule, IDR_RCDATA7, strIMGFDataFolderPath + "Styles/Main (orange and yellow).bxs");
	createFile(hModule, IDR_RCDATA8, strIMGFDataFolderPath + "Styles/Main.bxs");
	createFile(hModule, IDR_RCDATA9, strIMGFDataFolderPath + "Styles/Main_Black.bxs");
	createFile(hModule, IDR_RCDATA10, strIMGFDataFolderPath + "Styles/Main_Blue.bxs");
	createFile(hModule, IDR_RCDATA11, strIMGFDataFolderPath + "Styles/Main_Blueish.bxs");
	createFile(hModule, IDR_RCDATA12, strIMGFDataFolderPath + "Styles/Main_Green.bxs");
	createFile(hModule, IDR_RCDATA13, strIMGFDataFolderPath + "Styles/Main_LightGreen.bxs");
	createFile(hModule, IDR_RCDATA14, strIMGFDataFolderPath + "Styles/Main_Orange.bxs");
	createFile(hModule, IDR_RCDATA15, strIMGFDataFolderPath + "Styles/Main_Purple.bxs");
	createFile(hModule, IDR_RCDATA16, strIMGFDataFolderPath + "Styles/Main_Red.bxs");
	createFile(hModule, IDR_RCDATA17, strIMGFDataFolderPath + "Styles/Main-1 (grey).bxs");
	createFile(hModule, IDR_RCDATA18, strIMGFDataFolderPath + "Styles/Main-2 (blue and yellow).bxs");
}

void					Installer::createFile(HMODULE hModule, int iResourceId, string strFilePath)
{
	HRSRC hResourceFindResult = FindResource(hModule, MAKEINTRESOURCE(iResourceId), RT_RCDATA);
	if (!hResourceFindResult) return;

	HGLOBAL hResource = LoadResource(hModule, hResourceFindResult);
	if (!hResource) return;

	void *pData = LockResource(hResource);
	uint64 uiFileDataLength = SizeofResource(hModule, hResourceFindResult);

	File::storeFile(strFilePath, string((char*)pData, uiFileDataLength), false, true);

	UnlockResource(hResource);
	FreeResource(hResource);
}

void					Installer::addDesktopIcon(void)
{
	string
		strEXEFilePath = DataPath::getDataPath() + "Builds/" + m_strIMGFFileName,
		strLinkFilePath = DataPath::getDesktopFolderPath() + Path::replaceFileExtensionWithCase(m_strIMGFFileName, "LNK"),
		strLinkDescription = "IMG Factory";
	File::createLink(strEXEFilePath, strLinkFilePath, strLinkDescription);
}

void					Installer::addToStartMenu(void)
{
	string
		strEXEFilePath = DataPath::getDataPath() + "Builds/" + m_strIMGFFileName,
		strLinkFilePath = DataPath::geStartMenuFolderPath() + Path::replaceFileExtensionWithCase(m_strIMGFFileName, "LNK"),
		strLinkDescription = "IMG Factory";
	File::createLink(strEXEFilePath, strLinkFilePath, strLinkDescription);

	strLinkFilePath = DataPath::geStartMenuFolderPath() + "IMG Factory/" + Path::replaceFileExtensionWithCase(m_strIMGFFileName, "LNK");
	File::createLink(strEXEFilePath, strLinkFilePath, strLinkDescription);
}

void					Installer::associateFileExtensions(void)
{
	string
		strEXEFilePath = DataPath::getDataPath() + "Builds/" + m_strIMGFFileName,
		strAppIdentifier = "IMGFactory.2";
	vector<string>
		vecFileExtensions = { "DAT", "IMG", "DIR", "IDE", "IPL", "DFF", "COL", "TXD", "IFP", "WDR" };

	for (string& strFileExtension : vecFileExtensions)
	{
		Registry::assoicateFileExtension(strFileExtension, strEXEFilePath, strAppIdentifier);
	}
}