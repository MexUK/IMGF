#include "ModelEditorTab.h"
#include "Format/DFF/DFFFormat.h"
#include "Format/TXD/TXDManager.h"
#include "Format/TXD/TXDFormat.h"
#include "Window/Window.h"
#include "IMGF.h"
#include "Task/Tasks/RecentlyOpen/RecentlyOpenManager.h"
#include "Static/File.h"
#include "Control/Controls/TextBox.h"
#include "Control/Controls/Text.h"
#include "GUI/Editor/Base/Editor.h"
#include "Format/RW/Sections/RWSection_Geometry.h"
#include "Format/RW/Sections/RWSection_String.h"
#include "Format/RW/Sections/RWSection_BinMeshPLG.h"
#include "Format/RW/Sections/RWSection_Material.h"
#include "Format/RW/Sections/RWSection_FrameList.h"
#include "Format/RW/Sections/RWSection_Atomic.h"
#include "Format/RW/Sections/RWSection_Frame.h"
#include "BXGX.h"
#include "Event/EInputEvent.h"

#include <include/GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32 1
#define GLFW_EXPOSE_NATIVE_WGL 1
#include <include/GLFW/glfw3native.h>

#include <gl\gl.h>
#include <gl\glu.h>

using namespace std;
using namespace bxcf;
using namespace bxgx;
using namespace bxgx::events;
using namespace bxgi;
using namespace imgf;

GLuint *textureIDs; // todo
unordered_map<string, GLuint> textureIndices; // todo

ModelEditorTab::ModelEditorTab(void) :
	m_pDFFFile(nullptr),
	m_bInitialized(false)
{
}

// controls
void						ModelEditorTab::addControls(void)
{
}

void						ModelEditorTab::initControls(void)
{
	repositionAndResizeControls(Vec2i(0, 0));
}

void						ModelEditorTab::repositionAndResizeControls(Vec2i& vecSizeChange)
{
	EditorTab::repositionAndResizeControls(vecSizeChange);

	if (!m_bInitialized)
	{
		return;
	}

	Vec2u vecRenderSize = Vec2u(m_pWindow->getSize().x - 335 - 139 - 139 - 250, m_pWindow->getSize().y - 192);

	mutexRendering.lock();

	if (m_hbm)
	{
		DeleteObject(m_hbm);
	}

	m_hbm = CreateCompatibleBitmap(m_hdcWindow, vecRenderSize.x, vecRenderSize.y);
	SelectObject(m_hDC, m_hbm);

	//glViewport(0, 0, vecRenderSize.x, vecRenderSize.y);
	//const float64 ar = ((float64)vecRenderSize.x) / ((float64)vecRenderSize.y);
	//perspectiveGL(45.0, ar, 1.0, 1500.0);

	update3DRenderSize(vecRenderSize);

	mutexRendering.unlock();
}

// events
void						ModelEditorTab::bindEvents(void)
{
	bindEvent(MOVE_MOUSE_WHEEL, &ModelEditorTab::onMouseWheelMove2);

	EditorTab::bindEvents();
}

void						ModelEditorTab::unbindEvents(void)
{
	unbindEvent(MOVE_MOUSE_WHEEL, &ModelEditorTab::onMouseWheelMove2);

	EditorTab::unbindEvents();
}

// event callbacks
void						ModelEditorTab::onMouseWheelMove2(int16 iRotationDistance)
{
	//if (isPointOverEntryList(BXGX::get()->getCursorPosition()))
	if(false)
	{
		/*
		int iDelta = -(iRotationDistance / WHEEL_DELTA);
		float32 fNewProgress = m_pVScrollBar->getProgress() + ((float32)iDelta * m_pVScrollBar->getProgressFor1Item());
		fNewProgress = Math::limit(fNewProgress, 0.0f, 1.0f);
		m_pVScrollBar->setProgress(fNewProgress);
		*/
	}
	else
	{
		float32 fMouseWheelScrollMultiplier = 1.2f;
		int iDelta = -(iRotationDistance / WHEEL_DELTA);
		zoomCamera((float32)-iDelta * fMouseWheelScrollMultiplier);
	}

	m_pWindow->render();
}

// file loading
bool						ModelEditorTab::unserializeFile(void)
{
	return m_pDFFFile->unserialize();
}

void						ModelEditorTab::onFileLoaded(void)
{
	// update tab text
	updateTabText();

	// add file path to recently opened files list
	getIMGF()->getRecentlyOpenManager()->addRecentlyOpenEntry(m_pEditor->getEditorType(), getFile()->getFilePath());

	// display file info
	setFileInfoText();

	// load texture for model
	string strTextureFilePath = Path::replaceFileExtension(getFile()->getFilePath(), "TXD");
	if (File::doesFileExist(strTextureFilePath))
	{
		m_pTXDFile = TXDManager::unserializeFile(strTextureFilePath);
	}

	// render
	m_pWindow->render();
}

// file info text
void						ModelEditorTab::setFileInfoText(void)
{
	m_pText_FilePath->setText(Path::getDisplayableFilePath(getFile()->getFilePath()));
	m_pText_FileVersion->setText(getDFFFile()->getRWVersion()->getVersionText(), false);
	m_pText_FileGame->setText(getDFFFile()->getRWVersion()->getGamesAsString());

	updateEntryCountText();
}

void						ModelEditorTab::updateEntryCountText(void)
{
	uint32
		uiDisplayedEntryCount = getDFFFile()->getSectionCountByType(RW_SECTION_GEOMETRY),
		uiTotalEntryCount = uiDisplayedEntryCount;
	string
		strEntryCountText;

	if (uiDisplayedEntryCount == uiTotalEntryCount)
	{
		strEntryCountText = String::toString(uiTotalEntryCount);
	}
	else
	{
		strEntryCountText = String::toString(uiDisplayedEntryCount) + " of " + String::toString(uiTotalEntryCount);
	}

	m_pText_FileEntryCount->setText(strEntryCountText);
}

// render 2d
void						ModelEditorTab::render_Type1(void)
{
}

// render 3d
mutex mutexInitializing3DRender_ModelEditor; // todo

void						ModelEditorTab::render(void)
{
	render3D();
}

void						ModelEditorTab::render3D(void)
{
	Vec2u vecRenderSize = Vec2u(m_pWindow->getSize().x - 335 - 139 - 139 - 250, m_pWindow->getSize().y - 192);

	if (!m_pTXDFile)
	{
		return;
	}

	mutexInitializing3DRender_ModelEditor.lock();
	if (!m_bInitialized)
	{






		//glfwInit();

		//glewExperimental = GL_TRUE;
		//GLenum err = glewInit();






		//hDC = GetDC(m_pWindow->getWindowHandle());
		m_hdcWindow = GetDC(m_pWindow->getWindowHandle());
		m_hDC = CreateCompatibleDC(m_hdcWindow);

		m_hbm = CreateCompatibleBitmap(m_hdcWindow, vecRenderSize.x, vecRenderSize.y);

		SelectObject(m_hDC, m_hbm);

		if (!m_hDC)
		{
			MessageBox(NULL, L"ERROR 1", L"A", MB_OK);
			return;
		}

		int bits = 32;
		static PIXELFORMATDESCRIPTOR pfd =	// pfd Tells Windows How We Want Things To Be
		{
			sizeof(PIXELFORMATDESCRIPTOR),	// Size Of This Pixel Format Descriptor
			1,								// Version Number
											/*PFD_DRAW_TO_WINDOW |*/			// Format Must Support Window
											PFD_DRAW_TO_BITMAP |
											//PFD_SUPPORT_GDI
			PFD_SUPPORT_OPENGL, // |			// Format Must Support OpenGL
								//PFD_DOUBLEBUFFER,				// Must Support Double Buffering
			PFD_TYPE_RGBA,					// Request An RGBA Format
			bits,							// Select Our Color Depth
			0, 0, 0, 0, 0, 0,				// Color Bits Ignored
			0,								// No Alpha Buffer
			0,								// Shift Bit Ignored
			0,								// No Accumulation Buffer
			0, 0, 0, 0,						// Accumulation Bits Ignored
			16,								// 16Bit Z-Buffer (Depth Buffer)
			0,								// No Stencil Buffer
			0,								// No Auxiliary Buffer
			PFD_MAIN_PLANE,					// Main Drawing Layer
			0,								// Reserved
			0, 0, 0							// Layer Masks Ignored
		};

		GLuint PixelFormat = ChoosePixelFormat(m_hDC, &pfd);
		if (!PixelFormat)
		{
			MessageBox(NULL, L"ERROR 2", L"A", MB_OK);
			return;
		}

		BOOL bResult = SetPixelFormat(m_hDC, PixelFormat, &pfd);
		if (!bResult)
		{
			MessageBox(NULL, L"ERROR 3", L"A", MB_OK);
			return;
		}

		HGLRC hRC = wglCreateContext(m_hDC);
		if (!hRC)
		{
			MessageBox(NULL, L"ERROR 4", L"A", MB_OK);
			return;
		}

		bResult = wglMakeCurrent(m_hDC, hRC);
		if (!bResult)
		{
			MessageBox(NULL, L"ERROR 5", L"A", MB_OK);
			return;
		}



		glViewport(0, 0, vecRenderSize.x, vecRenderSize.y);

		//glEnable(GL_CULL_FACE);
		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		glEnable(GL_TEXTURE_2D);
		//glShadeModel(GL_FLAT);
		//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		//glShadeModel(GL_SMOOTH);
		//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		//glClearDepth(1.0f);                         // Depth Buffer Setup
		//glEnable(GL_DEPTH_TEST);                        // Enables Depth Testing

		glEnable(GL_DEPTH_TEST);
		//glDisable(GL_ALPHA_TEST);
		//glDisable(GL_STENCIL_TEST);
		//glDisable(GL_SCISSOR_TEST);

		glDepthFunc(GL_LEQUAL);                         // The Type Of Depth Test To Do
														//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);          // Really Nice Perspective Calculations

		float32 fHighestDistance = 1.5f;
		float32 fDistanceMultiplier = 2.0f;
		m_vecCameraPosition = { -2.0f, -2.0f, 2.0f };
		//vecCameraPosition = { 0.0f, 0.0f, 0.0f };
		//vecCameraPosition = Math::getPositionInFrontOfPosition(vecCameraPosition, Math::convertDegreesToRadians(45.0f), fHighestDistance * fDistanceMultiplier);
		//vecCameraRotation = { 0.0f, Math::convertDegreesToRadians(45.0f + 90), 0.0f };





		if (m_pTXDFile)
		{
			vector<RWSection*> vecTextures = m_pTXDFile->getSectionsByType(RW_SECTION_TEXTURE_NATIVE);
			uint32 uiTextureCount = vecTextures.size();

			textureIDs = new GLuint[uiTextureCount];
			textureIndices.clear();

			// Create multiple OpenGL textures
			glGenTextures(uiTextureCount, &textureIDs[0]);

			uint32 i = 0;
			for (RWSection *pRWSection : vecTextures)
			{
				RWSection_TextureNative *pTextureNative = (RWSection_TextureNative*)pRWSection;
				string strTextureRasterData = pTextureNative->getMipMaps().getFirstEntry()->getRasterDataBGRA32();
				string strTextureNameLower = String::toLowerCase(pTextureNative->getDiffuseName());

				// "Bind" the newly created texture : all future texture functions will modify this texture
				glBindTexture(GL_TEXTURE_2D, textureIDs[i]);

				//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

				//
				//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
				//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);

				// Give the image to OpenGL
				char * a = new char[strTextureRasterData.length()];
				memcpy(a, strTextureRasterData.c_str(), strTextureRasterData.length());
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, pTextureNative->getImageSize().x, pTextureNative->getImageSize().y, 0, GL_BGRA, GL_UNSIGNED_BYTE, a);
				
				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				if (pTextureNative->getEntryCount() > 1)
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
				else
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

				textureIndices[strTextureNameLower] = textureIDs[i];

				i++;
			}

			//GLuint Texture = loadBMP_custom("uvtemplate.bmp");



			/*
			string strVertexShader = File::getFileContent(string("C:\\Users\\James Baxter\\Desktop\\GitHub Repos\\IMGF\\Code\\IMGF\\GUI\\Editor\\Editors\\Tab\\Shader\\VertexShader.glsl"));
			string strFragmentShader = File::getFileContent(string("C:\\Users\\James Baxter\\Desktop\\GitHub Repos\\IMGF\\Code\\IMGF\\GUI\\Editor\\Editors\\Tab\\Shader\\FragmentShader.glsl"));
			const GLcharARB *pVertexShader = (GLcharARB *)strVertexShader.c_str();
			const GLcharARB *pFragmentShader = (GLcharARB *)strFragmentShader.c_str();
			const GLint iVertexShaderLength = strVertexShader.length();
			const GLint iFragmentShaderLength = strFragmentShader.length();
			
			GLuint vertexShader, fragmentShader;
			vertexShader = glCreateShader(GL_VERTEX_SHADER);
			fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

			glShaderSourceARB(vertexShader, 1, &pVertexShader, &iVertexShaderLength);
			glShaderSourceARB(fragmentShader, 1, &pFragmentShader, &iFragmentShaderLength);

			glCompileShaderARB(vertexShader);
			glCompileShaderARB(fragmentShader);

			//GLint compiled;
			//glGetObjectParameteriv(ShaderObject, GL_COMPILE_STATUS, &compiled);
			//if (compiled)
			//{
			//	//... // yes it compiled!
			//}

			

			GLuint uiProgramObject = glCreateProgram();

			glAttachShader(uiProgramObject, vertexShader);
			glAttachShader(uiProgramObject, fragmentShader);

			glLinkProgram(uiProgramObject);

			//GLint linked;
			//glGetProgramiv(uiProgramObject, GL_LINK_STATUS, &linked);
			//if (linked)
			//{
			//}
			*/
		}





		m_bInitialized = true;
	}
	mutexInitializing3DRender_ModelEditor.unlock();

	//mutexRendering.lock();



	//HANDLE hOld = SelectObject(hDC, hbm);


	update3DRenderSize(vecRenderSize);


	//prepare2DRender();
	//if (glGetError()) Input::showMessage("test1.5 error", "Error"); 
	//renderBackground();

	//if (glGetError()) Input::showMessage("test2 error", "Error");

	//prepare3DRender();

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);         // Clear The Screen And The Depth Buffer
	//glClear(GL_COLOR_BUFFER_BIT);
	//glLoadIdentity();


	renderCamera();
	renderAxis();
	renderModel();

	//glTranslatef(vecCameraPosition.x, vecCameraPosition.z, vecCameraPosition.y);

	//glTranslatef(vecCameraPosition.x, vecCameraPosition.z, vecCameraPosition.y);

	//if (glGetError()) Input::showMessage("test3 error", "Error");

	//prepare2DRender();
	//if (glGetError()) Input::showMessage("test3.5 error", "Error");
	//render2DObjects();

	//if (glGetError()) Input::showMessage("test4 error", "Error");

	//glDisable(GL_SCISSOR_TEST);

	//glDrawBuffers(1, GetBuffer(GL_BACK);



	glFinish();

	//SwapBuffers(m_hdcWindow);


	BitBlt(m_hdcWindow, 139 + 139 + 250, 192, vecRenderSize.x, vecRenderSize.y, m_hDC, 0, 0, SRCCOPY);




	//SelectObject(hDC, hOld);
	//DeleteObject(hbm);
	//DeleteDC(hDC);




	//mutexRendering.unlock();
}

void						ModelEditorTab::update3DRenderSize(Vec2u& vecRenderSize)
{
	//mutexRendering.lock();

	const float64 ar = ((float64)vecRenderSize.x) / ((float64)vecRenderSize.y);

	/*
	glViewport(0, 0, vecRenderSize.x, vecRenderSize.y);
	//glScissor(x, y, w, h);
	//glEnable(GL_SCISSOR_TEST);
	//glClear(GL_DEPTH_BUFFER_BIT);
	GLenum a = glGetError();
	if (a != GL_NO_ERROR)
	{
	//MessageBox(NULL, L"AAA", L"BBB", MB_OK);
	}
	*/

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, vecRenderSize.x, vecRenderSize.y);

	//glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	//gluPerspective(60.0, ar, 0.1, 100.0);
	//gluPerspective(50.0, 1.0, 1.0, 50.0);
	perspectiveGL_ModelEditor(45.0, ar, 1.0, 1500.0);

	//glLoadMatrixf(fData);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//mutexRendering.unlock();
}

// utility
void						perspectiveGL_ModelEditor(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
	const GLdouble pi = 3.1415926535897932384626433832795;
	GLdouble fW, fH;

	//fH = tan( (fovY / 2) / 180 * pi ) * zNear;
	fH = tan(fovY / 360 * pi) * zNear;
	fW = fH * aspect;

	glFrustum(-fW, fW, -fH, fH, zNear, zFar);
}

// camera
void						ModelEditorTab::zoomCamera(float32 fRadius)
{
	Vec3f vecCameraRotation = getCameraRotation();
	float32 fXAngle = vecCameraRotation.x;// Math::convertDegreesToRadians(90.0f);
	float32 fZAngle = vecCameraRotation.z - Math::convertDegreesToRadians(90.0f);
	Vec3f vecCameraPositionOffset = Math::getCartesianFromSpherical(fRadius, fXAngle, fZAngle);
	vecCameraPositionOffset.z = -vecCameraPositionOffset.z;
	m_vecCameraPosition = m_vecCameraPosition + vecCameraPositionOffset;
	m_vecCameraLookAtPosition = m_vecCameraLookAtPosition + vecCameraPositionOffset;
}

Vec3f						ModelEditorTab::getCameraRotation(void)
{
	Vec3f vecCameraRotation = Vec3f{
		Math::getAngleBetweenPoints(Vec3f(m_vecCameraPosition.x, m_vecCameraPosition.z, 0.0f), Vec3f(m_vecCameraLookAtPosition.x, m_vecCameraLookAtPosition.z, 0.0f)) + Math::convertDegreesToRadians(90.0f), // X
		0.0f, // Y
		Math::getAngleBetweenPoints(m_vecCameraPosition, m_vecCameraLookAtPosition) + Math::convertDegreesToRadians(90.0f) // Z
	};
	while (vecCameraRotation.x > 3.142) vecCameraRotation.x -= 3.142;
	while (vecCameraRotation.x < -3.142) vecCameraRotation.x += 3.142;
	while (vecCameraRotation.y > 3.142) vecCameraRotation.y -= 3.142;
	while (vecCameraRotation.y < -3.142) vecCameraRotation.y += 3.142;
	while (vecCameraRotation.z > 3.142) vecCameraRotation.z -= 3.142;
	while (vecCameraRotation.z < -3.142) vecCameraRotation.z += 3.142;
	return vecCameraRotation;
}

float32						ModelEditorTab::getCameraZRotation(void)
{
	return Math::getAngleBetweenPoints(m_vecCameraPosition, m_vecCameraLookAtPosition) + Math::convertDegreesToRadians(90.0f); // Z
}

// render 3d components
void						ModelEditorTab::renderCamera(void)
{
	Vec3f vecCameraRotation = getCameraRotation();
	//f += 0.03f;

	//vecCameraRotation.z = -vecCameraRotation.z;

	// camera rotation
	glRotatef(Math::convertRadiansToDegrees(vecCameraRotation.x), 1.0f, 0.0f, 0.0f); // Rotate our camera on the x-axis (looking up and down)
	glRotatef(Math::convertRadiansToDegrees(vecCameraRotation.z), 0.0f, 1.0f, 0.0f); // Rotate our camera on the y-axis (looking left and right)
	glRotatef(Math::convertRadiansToDegrees(vecCameraRotation.y), 0.0f, 0.0f, 1.0f);

	// camera position
	glTranslatef(-m_vecCameraPosition.x, -m_vecCameraPosition.z, -m_vecCameraPosition.y);

	//vecCameraRotation.x += Math::convertDegreesToRadians(0.1f);
	//vecCameraRotation.z += Math::convertDegreesToRadians(0.1f);
	//vecCameraRotation.z += Math::convertDegreesToRadians(0.03f);
}

void						ModelEditorTab::renderAxis(void)
{
	glBegin(GL_LINE_STRIP);
	glColor3ub(255, 0, 0);
	glVertex3f(-5000.0f, 0.0f, 0.0f);
	glVertex3f(5000.0f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3ub(0, 255, 0);
	glVertex3f(0.0f, 0.0f, -5000.0f);
	glVertex3f(0.0f, 0.0f, 5000.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3ub(0, 0, 255);
	glVertex3f(0.0f, -5000.0f, 0.0f);
	glVertex3f(0.0f, 5000.0f, 0.0f);
	glEnd();
}

void						ModelEditorTab::renderModel(void)
{
	vector<RWSection*> vecAtomics = m_pDFFFile->getSectionsByType(RW_SECTION_ATOMIC);
	unordered_map<uint32, RWSection_Atomic*> umapAtomics;
	unordered_map<uint32, uint32> umapGeometryIndices;
	for (RWSection *pRWSection : vecAtomics)
	{
		RWSection_Atomic *pAtomic = (RWSection_Atomic *)pRWSection;
		int32 iFrameIndex = pAtomic->getFrameIndex();
		umapAtomics[iFrameIndex] = pAtomic;
		umapGeometryIndices[iFrameIndex] = pAtomic->getGeometryIndex();
	}

	RWSection_FrameList *pFrameList = (RWSection_FrameList *)m_pDFFFile->getSectionsByType(RW_SECTION_FRAME_LIST)[0];

	uint32 uiFrameIndex = 0;
	for (RWSection *pRWSection : m_pDFFFile->getSectionsByType(RW_SECTION_FRAME))
	{
		RWSection_Frame *pFrame = (RWSection_Frame*)pRWSection;
		uint32 uiParentFrameIndex = pFrameList->m_uiCurrentFrameIndex[uiFrameIndex];

		if (uiParentFrameIndex == -1)
		{
			renderFrame(uiFrameIndex, pFrame, true);
		}

		uiFrameIndex++;
	}

	glBindTexture(GL_TEXTURE_2D, 0);
}

void						ModelEditorTab::renderFrame(uint32 uiFrameIndex, RWSection_Frame *pFrame, bool bIsParentFrame)
{
	glPushMatrix();
	glColor4f(1.0, 1.0, 1.0, 1.0);

	vector<RWSection*> vecAtomics = m_pDFFFile->getSectionsByType(RW_SECTION_ATOMIC);
	unordered_map<uint32, RWSection_Atomic*> umapAtomics;
	unordered_map<uint32, uint32> umapGeometryIndices;
	for (RWSection *pRWSection : vecAtomics)
	{
		RWSection_Atomic *pAtomic = (RWSection_Atomic *)pRWSection;
		int32 iFrameIndex = pAtomic->getFrameIndex();
		umapAtomics[iFrameIndex] = pAtomic;
		umapGeometryIndices[iFrameIndex] = pAtomic->getGeometryIndex();
	}

	RWSection_FrameList *pFrameList = (RWSection_FrameList *)m_pDFFFile->getSectionsByType(RW_SECTION_FRAME_LIST)[0];

	uint32 uiParentFrameIndex = pFrameList->m_uiCurrentFrameIndex[uiFrameIndex];

	//if not TheParent then with Clump[in_clump].FrameList.Data.Frame[in_frame] do
	// rotate offset

	//uiFrameIndex = pAtomic->getFrameIndex();

	if (!bIsParentFrame)
	{
		float32 vecMultMatrix[16];

		///*
		vecMultMatrix[0] = pFrameList->m_vecMatRow1[uiFrameIndex].x;
		vecMultMatrix[1] = pFrameList->m_vecMatRow1[uiFrameIndex].z;
		vecMultMatrix[2] = pFrameList->m_vecMatRow1[uiFrameIndex].y;
		vecMultMatrix[3] = 0;

		vecMultMatrix[4] = pFrameList->m_vecMatRow3[uiFrameIndex].x;
		vecMultMatrix[5] = pFrameList->m_vecMatRow3[uiFrameIndex].z;
		vecMultMatrix[6] = pFrameList->m_vecMatRow3[uiFrameIndex].y;
		vecMultMatrix[7] = 0;

		vecMultMatrix[8] = pFrameList->m_vecMatRow2[uiFrameIndex].x;
		vecMultMatrix[9] = pFrameList->m_vecMatRow2[uiFrameIndex].z;
		vecMultMatrix[10] = pFrameList->m_vecMatRow2[uiFrameIndex].y;
		vecMultMatrix[11] = 0;

		vecMultMatrix[12] = pFrameList->m_vecPosition[uiFrameIndex].x;
		vecMultMatrix[13] = pFrameList->m_vecPosition[uiFrameIndex].z;
		vecMultMatrix[14] = pFrameList->m_vecPosition[uiFrameIndex].y;
		vecMultMatrix[15] = 1;
		//*/

		/*
		vecMultMatrix[0] = pFrameList->m_vecMatRow3[uiFrameIndex].x;
		vecMultMatrix[1] = pFrameList->m_vecMatRow3[uiFrameIndex].z;
		vecMultMatrix[2] = pFrameList->m_vecMatRow3[uiFrameIndex].y;
		vecMultMatrix[3] = 0;

		vecMultMatrix[4] = pFrameList->m_vecMatRow1[uiFrameIndex].x;
		vecMultMatrix[5] = pFrameList->m_vecMatRow1[uiFrameIndex].z;
		vecMultMatrix[6] = pFrameList->m_vecMatRow1[uiFrameIndex].y;
		vecMultMatrix[7] = 0;

		vecMultMatrix[8] = pFrameList->m_vecMatRow2[uiFrameIndex].x;
		vecMultMatrix[9] = pFrameList->m_vecMatRow2[uiFrameIndex].z;
		vecMultMatrix[10] = pFrameList->m_vecMatRow[uiFrameIndex].y;
		vecMultMatrix[11] = 0;

		vecMultMatrix[12] = pFrameList->m_vecPosition[uiFrameIndex].x;
		vecMultMatrix[13] = pFrameList->m_vecPosition[uiFrameIndex].z;
		vecMultMatrix[14] = pFrameList->m_vecPosition[uiFrameIndex].y;
		vecMultMatrix[15] = 1;
		*/

		glMultMatrixf(&vecMultMatrix[0]);
	}

	if (umapAtomics.count(uiFrameIndex) != 0)
	{
		RWSection_Atomic *pAtomic = (RWSection_Atomic*)umapAtomics[uiFrameIndex];
		uint32 uiGeometryIndex = pAtomic->getGeometryIndex();
		RWSection_BinMeshPLG *pBinMeshPLG = (RWSection_BinMeshPLG*)m_pDFFFile->getSectionsByType(RW_SECTION_BIN_MESH_PLG)[uiGeometryIndex];

		for (RWEntry_BinMeshPLG_Mesh *pMesh : pBinMeshPLG->getMeshes())
		{
			uint32 uiMaterialIndex = pMesh->getMaterialIndex();
			vector<RWSection*> vecMaterials = pBinMeshPLG->getParentNode()->getParentNode()->getSectionsByType(RW_SECTION_MATERIAL);
			RWSection_Material *pMaterial = (RWSection_Material*)vecMaterials[uiMaterialIndex];
			//RWSection_Geometry *pGeometry = (RWSection_Geometry*)pMaterial->getParentNode()->getParentNode();
			RWSection_Geometry *pGeometry = (RWSection_Geometry*)m_pDFFFile->getSectionsByType(RW_SECTION_GEOMETRY)[uiGeometryIndex];
			vector<RWSection*> vecStrings = pMaterial->getSectionsByType(RW_SECTION_STRING);
			bool bMeshUsesTexture = vecStrings.size() > 0;
			bool bUsesNormals = pGeometry->getBoundingInfo().doesHaveNormals();

			if (bMeshUsesTexture)
			{
				string strTextureName = ((RWSection_String*)vecStrings[0])->getData();
				string strTextureNameLower = String::toLowerCase(strTextureName);

				bMeshUsesTexture = strTextureName != "";
				if (bMeshUsesTexture)
				{
					bMeshUsesTexture = textureIndices.count(strTextureNameLower) > 0;

					if (bMeshUsesTexture)
					{
						GLuint uiTextureID = textureIndices[strTextureNameLower];
						glBindTexture(GL_TEXTURE_2D, uiTextureID);
					}
				}
			}

			if (pBinMeshPLG->getFlags() == 0)
			{
				// triangle list
				glBegin(GL_TRIANGLES);
			}
			else
			{
				// triangle strip
				glBegin(GL_TRIANGLE_STRIP);
			}

			uint32 uiTriangleIndex = 0;
			uint32 uiVertexIndex = 0;
			for (uint32 uiIndex : pMesh->getVertexIndices())
			{
				Vec3f& vecPoint = pGeometry->getVertexPositions()[uiIndex];
				Vec2f& vecTexCoords = pGeometry->getTextureCoordinates()[uiIndex];
				Vec3f vecNormal;
				if (bUsesNormals)
				{
					//vecNormal = pGeometry->getVertexNormals()[uiVertexIndex / 3];
					vecNormal = pGeometry->getVertexNormals()[uiIndex];
				}

				if (bMeshUsesTexture)
				{
					glTexCoord2f(vecTexCoords.x, vecTexCoords.y);
				}
				//glColor4ub(vecColour3.x, vecColour3.y, vecColour3.z, vecColour3.w);
				//glColor4ub(0, 0, 255, 255);
				if (bUsesNormals)
				{
					//if ((uiVertexIndex % 3) == 0)
					//{
					glNormal3f(vecNormal.x, vecNormal.z, vecNormal.y);
					//}
				}
				glVertex3f(vecPoint.x, vecPoint.z, vecPoint.y);
				uiVertexIndex++;
			}
			glEnd();
		}
	}

	for (uint32 uiFrameIndex2 = 0, j = pFrameList->getFrameCount(); uiFrameIndex2 < j; uiFrameIndex2++)
	{
		RWSection_Frame *pFrame = (RWSection_Frame*) m_pDFFFile->getSectionsByType(RW_SECTION_FRAME)[uiFrameIndex2];
		if (uiFrameIndex == pFrameList->m_uiCurrentFrameIndex[uiFrameIndex2])
		{
			string strFrameName = String::trim(pFrame->getData());
			uint32 uiFrameNameLength = strFrameName.length();
			if (uiFrameNameLength >= 3)
			{
				if (strFrameName.c_str()[uiFrameNameLength - 2] == '_' && (String::toUpperCase(strFrameName).c_str()[uiFrameNameLength - 1] == 'L'))
				{
					int32 iFrameValue = String::toInt32(strFrameName);
					if (iFrameValue <= 0)
					{
						renderFrame(uiFrameIndex2, pFrame, true);
					}
				}
				else if (strFrameName.substr(1, 3) != "Col")
				{
					renderFrame(uiFrameIndex2, pFrame, false);
				}
			}
			else
			{
				renderFrame(uiFrameIndex2, pFrame, false);
			}
		}
	}

	glPopMatrix();
}