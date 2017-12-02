#pragma once

#include "nsimgf.h"
#include "nsbxgi.h"
#include "nsbxgx.h"
#include "GUI/Editor/Base/Tab/EditorTab.h"
#include "Pool/VectorPool.h"
#include "Type/Vector/Vec3f.h"

#include "GL/glew.h"
#include "GL/wglew.h"
#include <Windows.h>

void						perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar); // todo - namespace

class SolidSphere // todo - namespace
{
protected:
	std::vector<GLfloat> vertices;
	std::vector<GLfloat> normals;
	std::vector<GLfloat> texcoords;
	std::vector<GLushort> indices;

public:
	SolidSphere(float radius, unsigned int rings, unsigned int sectors)
	{
		float const R = 1. / (float)(rings - 1);
		float const S = 1. / (float)(sectors - 1);
		int r, s;

		vertices.resize(rings * sectors * 3);
		normals.resize(rings * sectors * 3);
		texcoords.resize(rings * sectors * 2);
		std::vector<GLfloat>::iterator v = vertices.begin();
		std::vector<GLfloat>::iterator n = normals.begin();
		std::vector<GLfloat>::iterator t = texcoords.begin();
		for (r = 0; r < rings; r++) for (s = 0; s < sectors; s++) {
			float const y = sin(-M_PI_2 + M_PI * r * R);
			float const x = cos(2 * M_PI * s * S) * sin(M_PI * r * R);
			float const z = sin(2 * M_PI * s * S) * sin(M_PI * r * R);

			*t++ = s*S;
			*t++ = r*R;

			*v++ = x * radius;
			*v++ = y * radius;
			*v++ = z * radius;

			*n++ = x;
			*n++ = y;
			*n++ = z;
		}

		indices.resize(rings * sectors * 4);
		std::vector<GLushort>::iterator i = indices.begin();
		for (r = 0; r < rings - 1; r++) for (s = 0; s < sectors - 1; s++) {
			*i++ = r * sectors + s;
			*i++ = r * sectors + (s + 1);
			*i++ = (r + 1) * sectors + (s + 1);
			*i++ = (r + 1) * sectors + s;
		}
	}

	void draw(GLfloat x, GLfloat y, GLfloat z)
	{
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(x, y, z);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
		glNormalPointer(GL_FLOAT, 0, &normals[0]);
		glTexCoordPointer(2, GL_FLOAT, 0, &texcoords[0]);
		glDrawElements(GL_QUADS, indices.size(), GL_UNSIGNED_SHORT, &indices[0]);
		glPopMatrix();
	}
};

class imgf::CollisionEditorTab : public imgf::EditorTab
{
public:
	CollisionEditorTab(void);

	void						bindEvents(void);
	void						unbindEvents(void);

	bool						unserializeFile(void);
	void						onFileLoaded(void);

	void						setCOLFile(bxgi::COLFormat *pCOLFile) { m_pCOLFile = pCOLFile; }
	bxgi::COLFormat*			getCOLFile(void) { return m_pCOLFile; }

	void						render(void);
	void						renderNotOnProcess(void);

	void						render2D(void);
	void						render3D(void);

	void						setFileInfoText(void);
	void						updateEntryCountText(void);

protected:
	void						addControls(void);
	void						initControls(void);

	void						onSelectDropDownItem(bxgx::DropDownItem *pItem);
	void						onLeftMouseDown(bxcf::Vec2i vecCursorPosition);
	//void						onMouseMove2(bxcf::Vec2i vecCursorPosition);
	bool						onMouseMove(bxcf::Vec2i& vecCursorPosition);
	void						onKeyDown2(uint16 uiKey);
	void						onMouseWheelMove2(int16 iRotationDistance);

	void						repositionAndResizeControls(bxcf::Vec2i& vecSizeChange);

private:
	bool						prepareRenderData(void);

	void						setActiveEntry(bxgi::COLEntry *pCOLEntry) { m_pActiveEntry = pCOLEntry; }
	bxgi::COLEntry*				getActiveEntry(void) { return m_pActiveEntry; }

	void						update3DRenderSize(bxcf::Vec2u& vecRenderSize);

	void						prepareInitial3DRender(void);
	void						prepare3DRender(void);
	void						renderCamera(void);
	void						renderAxis(void);
	void						renderCollisionObjects(void);
	void						renderBoundingSphere(void);
	void						renderBoundingCuboid(void);

	void						renderCollisionMeshes(void);
	void						renderCollisionCuboids(void);
	void						renderCollisionSpheres(void);
	void						renderCollisionLinesOrCones(void);
	void						renderCollisionCones(void);
	void						renderCollisionLines(void);

	void						moveCamera(float32 fAngleDeg, float32 fRadius);
	void						rotateCameraLookAt(float32 fZAngleDeg, float32 fXAngleDeg);
	void						zoomCamera(float32 fRadius);
	bxcf::Vec3f					getCameraRotation(void);
	float32						getCameraZRotation(void); // result is in radians

	bool						isPointOverEntryList(bxcf::Vec2i& vecPoint);

private:
	bxgi::COLFormat*			m_pCOLFile;
	bxgi::COLEntry*				m_pActiveEntry;

	bxgx::ScrollBar*			m_pVScrollBar;

	bool						m_bInitialized;
	bool						m_bPanningCamera;

	bxcf::Vec3f					m_vecCameraPosition;
	bxcf::Vec3f					m_vecCameraLookAtPosition;
	HDC							m_hdcWindow;
	HDC							m_hDC;
	HBITMAP						m_hbm;
};