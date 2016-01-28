
// D3DPointCloudView.h : CD3DPointCloudView 类的接口
//

#pragma once
#include <d3dx9.h>
#include "DXUT.h"
#include "DXUTcamera.h"
class CD3DPointCloudView : public CView
{
private:
	CModelViewerCamera    g_Camera;               // Camera for navigation
	CMeshArcBall          g_ArcBall;
private:
	IDirect3DDevice9* _device;
	D3DPRESENT_PARAMETERS _d3dpp;
	ID3DXMesh* _teapot;
private:
	HRESULT initD3D(HWND hwnd,int width,int height,bool windowed,D3DDEVTYPE deviceType);
	HRESULT setup(int width, int height);
	HRESULT cleanup();
public:
	HRESULT update(float timeDelta);
	HRESULT render();

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

