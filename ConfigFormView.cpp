// ConfigFormView.cpp : ʵ���ļ�
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
}

void CConfigFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CConfigFormView, CFormView)
END_MESSAGE_MAP()


// CConfigFormView ���

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


// CConfigFormView ��Ϣ�������
