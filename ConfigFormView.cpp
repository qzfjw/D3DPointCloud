// ConfigFormView.cpp : 实现文件
//

#include "stdafx.h"
#include "D3DPointCloud.h"
#include "ConfigFormView.h"


// CConfigFormView

IMPLEMENT_DYNCREATE(CConfigFormView, CFormView)

CConfigFormView::CConfigFormView()
	: CFormView(CConfigFormView::IDD)
{

}

CConfigFormView::~CConfigFormView()
{
	SAFE_DELETE(m_pPageLayout);
	SAFE_DELETE(m_pPropSheet);
	
}

void CConfigFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CConfigFormView, CFormView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CConfigFormView 诊断

#ifdef _DEBUG
void CConfigFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CConfigFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CConfigFormView 消息处理程序


int CConfigFormView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_pPageLayout = new CPointCloudPageLayout;
   

	m_pPropSheet = new CPropertySheet; //CSnapPropertySheet;
	m_pPropSheet->AddPage(m_pPageLayout);
	
	// create a modeless property page
	if (!m_pPropSheet->Create(this,DS_CONTEXTHELP | DS_SETFONT | WS_CHILD | WS_VISIBLE))
	{
		DestroyWindow();
		return FALSE;
	}

	m_pPropSheet->SetWindowPos(NULL, 0, 0, 0, 0,
		SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOSIZE);

	return 0;
}
