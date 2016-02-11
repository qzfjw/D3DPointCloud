#pragma once
#include "PointCloudPageLayout.h"

// CConfigFormView ������ͼ

class CConfigFormView : public CFormView
{
	DECLARE_DYNCREATE(CConfigFormView)

protected:
	CConfigFormView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CConfigFormView();

public:
	enum { IDD = IDD_FORMVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
protected:
	// property sheet is wired to SDI child frame and is not displayed
	CPropertySheet* m_pPropSheet;

	// one page for each menu so we can initialize controls
	// using OnInitDialog
	CPointCloudPageLayout*      m_pPageLayout;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


