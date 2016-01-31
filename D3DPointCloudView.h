
// D3DPointCloudView.h : CD3DPointCloudView 类的接口
//

#pragma once
#include <d3dx9.h>
#include "DXUT.h"
#include "DXUTcamera.h"
#include "meshloader.h"
#include "PlyMeshLoader.h"

class CD3DPointCloudView : public CView
{
private:
	CModelViewerCamera    g_Camera;               // Camera for navigation
	CMeshArcBall          g_ArcBall;
	CMeshLoader           g_MeshLoader;            // Loads a mesh from an .obj file
	CPlyMeshLoader        g_PlyMeshLoader;
	ID3DXEffect*          g_pEffect;        // D3DX effect interface
	int m_iWidth;   //width and height of window
	int m_iHeight;
	D3DXMATRIX m_matTranslation;
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
	IDirect3DDevice9* m_pd3dDevice;
	D3DPRESENT_PARAMETERS m_d3dpp;
	//ID3DXMesh* _teapot;
private:
	HRESULT InitD3D(HWND hwnd,int width,int height,bool windowed,D3DDEVTYPE deviceType);
	void    RenderSubset( UINT iSubset );
	void    RenderPoly();
public:

	//--------------------------------------------------------------------------------------
	// This callback function will be called immediately after the Direct3D device has been 
	// created, which will happen during application initialization and windowed/full screen 
	// toggles. This is the best location to create D3DPOOL_MANAGED resources since these 
	// resources need to be reloaded whenever the device is destroyed. Resources created  
	// here should be released in the OnDestroyDevice callback. 
	//--------------------------------------------------------------------------------------
	HRESULT CreateDevice(int width, int height);

	//--------------------------------------------------------------------------------------
	// This callback function will be called immediately after the Direct3D device has 
	// been destroyed, which generally happens as a result of application termination or 
	// windowed/full screen toggles. Resources created in the OnCreateDevice callback 
	// should be released here, which generally includes all D3DPOOL_MANAGED resources. 
	//--------------------------------------------------------------------------------------
    void DestroyDevice();

	//--------------------------------------------------------------------------------------
	// This callback function will be called immediately after the Direct3D device has been 
	// reset, which will happen after a lost device scenario. This is the best location to 
	// create D3DPOOL_DEFAULT resources since these resources need to be reloaded whenever 
	// the device is lost. Resources created here should be released in the OnLostDevice 
	// callback. 
	//--------------------------------------------------------------------------------------
	HRESULT ResetDevice(int width, int height);

	//--------------------------------------------------------------------------------------
	// This callback function will be called immediately after the Direct3D device has 
	// entered a lost state and before IDirect3DDevice9::Reset is called. Resources created
	// in the OnResetDevice callback should be released here, which generally includes all 
	// D3DPOOL_DEFAULT resources. See the "Lost Devices" section of the documentation for 
	// information about lost devices.
	//--------------------------------------------------------------------------------------
	void LostDevice();

	HRESULT FrameMove(double fTime, float fElapsedTime);
	HRESULT FrameRender(double fTime, float fElapsedTime);
	
	

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

