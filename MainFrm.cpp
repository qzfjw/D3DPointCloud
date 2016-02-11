
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "D3DPointCloud.h"

#include "MainFrm.h"

#include "ConfigFormView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_APPCONFIGFORM, &CMainFrame::OnAppconfigform)
	ON_UPDATE_COMMAND_UI(ID_APPCONFIGFORM, &CMainFrame::OnUpdateAppconfigform)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}

	//if (!m_wndStatusBar.Create(this))
	//{
	//	TRACE0("δ�ܴ���״̬��\n");
	//	return -1;      // δ�ܴ���
	//}
	//m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: �������Ҫ��ͣ������������ɾ��������
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	if (!m_wndMyBar.Create(this,
		RUNTIME_CLASS (CConfigFormView),
		(CCreateContext *)(lpCreateStruct->lpCreateParams),
		_T("�����趨"), WS_CHILD | WS_VISIBLE | CBRS_TOP,
		AFX_IDW_CONTROLBAR_FIRST + 33))
	{
		TRACE0("Failed to create ViewBar\n");
		return -1;		// fail to create
	}

	m_wndMyBar.SetBarStyle(m_wndMyBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	
	m_wndMyBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndMyBar, AFX_IDW_DOCKBAR_RIGHT);//_RIGHT

	ShowControlBar(&m_wndMyBar, FALSE, FALSE);
	
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������


void CMainFrame::OnAppconfigform()
{
	// TODO: �ڴ���������������
	BOOL bShow = m_wndMyBar.IsVisible();
	ShowControlBar(&m_wndMyBar, !bShow, FALSE);
	//m_wndToolBar.ShowWindow(SW_SHOW);
}


void CMainFrame::OnUpdateAppconfigform(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable();
	pCmdUI->SetCheck(m_wndMyBar.IsVisible());
}
