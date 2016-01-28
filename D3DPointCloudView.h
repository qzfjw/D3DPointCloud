
// D3DPointCloudView.h : CD3DPointCloudView 类的接口
//

#pragma once
#include <d3dx9.h>
#include "DXUT.h"
#include "DXUTcamera.h"
#include "meshloader.h"
class CD3DPointCloudView : public CView
{
private:
	CModelViewerCamera    g_Camera;               // Camera for navigation
	CMeshArcBall          g_ArcBall;
	CMeshLoader           g_MeshLoader;            // Loads a mesh from an .obj file
	ID3DXEffect*          g_pEffect;        // D3DX effect interface
	//--------------------------------------------------------------------------------------
	// Effect parameter handles
	//--------------------------------------------------------------------------------------
	D3DXHANDLE                  g_hAmbient;
	D3DXHANDLE                  g_hDiffuse;
	D3DXHANDLE                  g_hSpecular;
	D3DXHANDLE                  g_hOpacity;
	D3DXHANDLE                  g_hSpecularPower;
	D3DXHANDLE                  g_hLightColor;
	D3DXHANDLE                  g_hLightPosition;
	D3DXHANDLE                  g_hCameraPosition;
	D3DXHANDLE                  g_hTexture;
	D3DXHANDLE                  g_hTime;
	D3DXHANDLE                  g_hWorld;
	D3DXHANDLE                  g_hWorldViewProjection;
private:
	IDirect3DDevice9* _device;
	D3DPRESENT_PARAMETERS _d3dpp;
	ID3DXMesh* _teapot;
private:
	HRESULT initD3D(HWND hwnd,int width,int height,bool windowed,D3DDEVTYPE deviceType);
	HRESULT setup(int width, int height);
	HRESULT cleanup();
	void    RenderSubset( UINT iSubset );
public:
	HRESULT update(float fElapsedTime);
	HRESULT render(double fTime, float fElapsedTime);

protected: // 仅从序列化创建
	CD3DPointCloudView();
	DECLARE_DYNCREATE(CD3DPointCloudView)

// 特性
public:
	CD3DPointCloudDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CD3DPointCloudView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};

#ifndef _DEBUG  // D3DPointCloudView.cpp 中的调试版本
inline CD3DPointCloudDoc* CD3DPointCloudView::GetDocument() const
   { return reinterpret_cast<CD3DPointCloudDoc*>(m_pDocument); }
#endif

