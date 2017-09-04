#pragma once

#include "GraphicsLibrary/Base/GraphicsLibrary.h"
#include <Windows.h>
#include "d3d8.h"
#include "d3dx8.h"

class bxgx::D3D8 : public bxgx::GraphicsLibrary
{
public:
	D3D8(void);

	void					init(void);

	void					onBeginRender(bxcf::Vec2u& vecBitmapSize);
	void					onResizeWindow(bxcf::Vec2i& vecSizeDifference);
	void					onRenderRectangleArea(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize);
	void					onEndRender(void);

	void					loadNewObjects(void);
	void					loadExistingObjects(void);
	
	void					drawLine(bxcf::Vec2i& vecPoint1, bxcf::Vec2i& vecPoint2);
	
	void					drawRectangleFill(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize);
	void					drawRectangleBorder(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize);
	
	void					drawCircleFill(bxcf::Vec2i& vecPosition, float32 fRadius);
	void					drawCircleBorder(bxcf::Vec2i& vecPosition, float32 fRadius);
	
	void					drawEllipseFill(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize);
	void					drawEllipseBorder(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize);

	void					drawText(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, std::string& strText, bxcf::Vec2u vecTextSize = bxcf::Vec2u(0, 0));
	void					drawText(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, bxgx::SizedString& sizedString);
	bxcf::Vec2u				getTextSize(LPD3DXFONT pFont, std::string& strText);
	bxcf::Vec2u				getTextSize(std::string& strText);
	
	void					drawImage(bxcf::Vec2i& vecPosition, std::string& strImagePath, bxcf::Vec2u vecSize = bxcf::Vec2u(0, 0));

	void					drawPolygonBorder(std::vector<bxcf::Vec2i>& vecPoints);
	void					drawPolygonFill(std::vector<bxcf::Vec2i>& vecPoints);

private:
	IDirect3D8*				m_pDirect3D;
	IDirect3DDevice8*		m_pDevice;
};

typedef HRESULT(WINAPI* CreateDevice_Prototype)        (LPDIRECT3D8, UINT, D3DDEVTYPE, HWND, DWORD, D3DPRESENT_PARAMETERS*, LPDIRECT3DDEVICE8*);
typedef HRESULT(WINAPI* Reset_Prototype)               (LPDIRECT3DDEVICE8, D3DPRESENT_PARAMETERS*);
typedef HRESULT(WINAPI* EndScene_Prototype)            (LPDIRECT3DDEVICE8);
typedef HRESULT(WINAPI* DrawIndexedPrimitive_Prototype)(LPDIRECT3DDEVICE8, D3DPRIMITIVETYPE, UINT, UINT, UINT, UINT);

HRESULT WINAPI Direct3DCreate8_VMTable(VOID);
//HRESULT WINAPI CreateDevice_Pointer(LPDIRECT3D8, UINT, D3DDEVTYPE, HWND, DWORD, D3DPRESENT_PARAMETERS*, LPDIRECT3DDEVICE8*);
HRESULT WINAPI CreateDevice_Detour(LPDIRECT3D8, UINT, D3DDEVTYPE, HWND, DWORD, D3DPRESENT_PARAMETERS*, LPDIRECT3DDEVICE8*);
HRESULT WINAPI Reset_Detour(LPDIRECT3DDEVICE8, D3DPRESENT_PARAMETERS*);
HRESULT WINAPI EndScene_Detour(LPDIRECT3DDEVICE8);
HRESULT WINAPI DrawIndexedPrimitive_Detour(LPDIRECT3DDEVICE8, D3DPRIMITIVETYPE, UINT, UINT, UINT, UINT);