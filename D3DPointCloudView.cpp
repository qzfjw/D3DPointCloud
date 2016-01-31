
// D3DPointCloudView.cpp : CD3DPointCloudView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CD3DPointCloudView 构造/析构

CD3DPointCloudView::CD3DPointCloudView()
{
	// TODO: 在此处添加构造代码
	d3dapp = new CD3DAppMain();

}

CD3DPointCloudView::~CD3DPointCloudView()
{
	SAFE_DELETE(d3dapp);
	
}

BOOL CD3DPointCloudView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CD3DPointCloudView 绘制

void CD3DPointCloudView::OnDraw(CDC* /*pDC*/)
{
	CD3DPointCloudDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CD3DPointCloudView 打印

BOOL CD3DPointCloudView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CD3DPointCloudView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CD3DPointCloudView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CD3DPointCloudView 诊断

#ifdef _DEBUG
void CD3DPointCloudView::AssertValid() const
{
	CView::AssertValid();
}

void CD3DPointCloudView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CD3DPointCloudDoc* CD3DPointCloudView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CD3DPointCloudDoc)));
	return (CD3DPointCloudDoc*)m_pDocument;
}
#endif //_DEBUG


// CD3DPointCloudView 消息处理程序


void CD3DPointCloudView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
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

	// TODO: 在此处添加消息处理程序代码

}


BOOL CD3DPointCloudView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
	// TODO: 在此添加专用代码和/或调用基类
	//d3dapp->InitD3D9(GetSafeHwnd());
	d3dapp->HandleMessages(GetSafeHwnd(),message,wParam,lParam);
	return CView::WindowProc(message, wParam, lParam);
}
