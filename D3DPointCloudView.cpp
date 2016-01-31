
// D3DPointCloudView.cpp : CD3DPointCloudView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "D3DPointCloud.h"
#endif

#include "D3DPointCloudDoc.h"
#include "D3DPointCloudView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CD3DPointCloudView

IMPLEMENT_DYNCREATE(CD3DPointCloudView, CView)

BEGIN_MESSAGE_MAP(CD3DPointCloudView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CD3DPointCloudView ����/����

CD3DPointCloudView::CD3DPointCloudView()
{
	// TODO: �ڴ˴���ӹ������
	d3dapp = new CD3DAppMain();

}

CD3DPointCloudView::~CD3DPointCloudView()
{
	SAFE_DELETE(d3dapp);
	
}

BOOL CD3DPointCloudView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CD3DPointCloudView ����

void CD3DPointCloudView::OnDraw(CDC* /*pDC*/)
{
	CD3DPointCloudDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CD3DPointCloudView ��ӡ

BOOL CD3DPointCloudView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CD3DPointCloudView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CD3DPointCloudView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CD3DPointCloudView ���

#ifdef _DEBUG
void CD3DPointCloudView::AssertValid() const
{
	CView::AssertValid();
}

void CD3DPointCloudView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CD3DPointCloudDoc* CD3DPointCloudView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CD3DPointCloudDoc)));
	return (CD3DPointCloudDoc*)m_pDocument;
}
#endif //_DEBUG


// CD3DPointCloudView ��Ϣ�������


void CD3DPointCloudView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	//CRect rect;
	//GetClientRect(&rect);
	// Initialize Direct3D (e.g. acquire a IDirect3DDevice9 poniter).
	//HRESULT hr = initD3D(GetSafeHwnd(),rect.right,rect.bottom,true,D3DDEVTYPE_HAL);
	//if(FAILED(hr))
	//{
	//	::MessageBox(0,L"initD3D() - Failed", 0,0);
	//	::PostQuitMessage(0);
	//}
	//// Setup the application.
	//hr = setup(rect.right, rect.bottom);
	//if(FAILED(hr))
	//{
	//	::MessageBox(0,L"setup() - Failed", 0,0);
	//	::PostQuitMessage(0);
	//}
	d3dapp->InitD3D9(AfxGetMainWnd()->m_hWnd);//GetSafeHwnd());
}



void CD3DPointCloudView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������

}


BOOL CD3DPointCloudView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return FALSE;
	//return CView::OnEraseBkgnd(pDC);
}

void CD3DPointCloudView::FrameRender(float fTime,float fElapsedTime)
{
	if(d3dapp)
		d3dapp->FrameRender(fTime,fElapsedTime);
}

LRESULT CD3DPointCloudView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: �ڴ����ר�ô����/����û���
	//d3dapp->InitD3D9(GetSafeHwnd());
	d3dapp->HandleMessages(GetSafeHwnd(),message,wParam,lParam);
	return CView::WindowProc(message, wParam, lParam);
}
