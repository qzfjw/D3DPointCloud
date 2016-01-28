
// D3DPointCloudView.h : CD3DPointCloudView ��Ľӿ�
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

protected: // �������л�����
	CD3DPointCloudView();
	DECLARE_DYNCREATE(CD3DPointCloudView)

// ����
public:
	CD3DPointCloudDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CD3DPointCloudView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};

#ifndef _DEBUG  // D3DPointCloudView.cpp �еĵ��԰汾
inline CD3DPointCloudDoc* CD3DPointCloudView::GetDocument() const
   { return reinterpret_cast<CD3DPointCloudDoc*>(m_pDocument); }
#endif

