// PointCloudPageLayout.cpp : 实现文件
//

#include "stdafx.h"
#include "D3DPointCloud.h"
#include "PointCloudPageLayout.h"
#include "afxdialogex.h"
#include "GlobalVariable.h"

extern CGlobalVariable gGlobalPara;

// CPointCloudPageLayout 对话框

IMPLEMENT_DYNAMIC(CPointCloudPageLayout, CPropertyPage)

CPointCloudPageLayout::CPointCloudPageLayout()
	: CPropertyPage(CPointCloudPageLayout::IDD)
	, m_edtModelStep(10)
	, m_edtModel_X(0)
	, m_edtModel_Y(0)
	, m_edtModel_Z(0)
	, m_chkX(TRUE)
	, m_chkY(FALSE)
	, m_chkZ(FALSE)
{
	m_edtModelStep = gGlobalPara.m_edtModelStep;
	m_edtModel_X = gGlobalPara.m_edtModel_X;
	m_edtModel_Y = gGlobalPara.m_edtModel_Y;
	m_edtModel_Z = gGlobalPara.m_edtModel_Z;
	m_chkX = gGlobalPara.m_chkX;
	m_chkY = gGlobalPara.m_chkY;
	m_chkZ = gGlobalPara.m_chkZ;

}
void CPointCloudPageLayout::UpdateDataFromGlobal()
{
	m_edtModel_X = gGlobalPara.m_edtModel_X;
	m_edtModel_Y = gGlobalPara.m_edtModel_Y;
	m_edtModel_Z = gGlobalPara.m_edtModel_Z;
	UpdateData(FALSE); //用变量值更新控件值

}
CPointCloudPageLayout::~CPointCloudPageLayout()
{
}

void CPointCloudPageLayout::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MODEL_STEP, m_edtModelStep);
	DDV_MinMaxFloat(pDX, m_edtModelStep, 0, 100);
	DDX_Text(pDX, IDC_MODEL_X, m_edtModel_X);
	DDX_Text(pDX, IDC_MODEL_Y, m_edtModel_Y);
	DDX_Text(pDX, IDC_MODEL_Z, m_edtModel_Z);
	DDX_Check(pDX, IDC_CHECK_X, m_chkX);
	DDX_Check(pDX, IDC_CHECK_Y, m_chkY);
	DDX_Check(pDX, IDC_CHECK_Z, m_chkZ);
	DDX_Control(pDX, IDC_COMBO_FILELIST, m_cboFileList);
}


BEGIN_MESSAGE_MAP(CPointCloudPageLayout, CPropertyPage)
	ON_EN_KILLFOCUS(IDC_MODEL_STEP, &CPointCloudPageLayout::OnEnKillfocusModelStep)
	ON_EN_KILLFOCUS(IDC_MODEL_X, &CPointCloudPageLayout::OnEnKillfocusModelX)
	ON_EN_KILLFOCUS(IDC_MODEL_Y, &CPointCloudPageLayout::OnEnKillfocusModelY)
	ON_EN_KILLFOCUS(IDC_MODEL_Z, &CPointCloudPageLayout::OnEnKillfocusModelZ)
	ON_BN_CLICKED(IDC_ADD, &CPointCloudPageLayout::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_MINUS, &CPointCloudPageLayout::OnBnClickedMinus)
	ON_BN_CLICKED(IDC_LOADMODEL, &CPointCloudPageLayout::OnBnClickedLoadmodel)
	ON_CBN_SELCHANGE(IDC_COMBO_FILELIST, &CPointCloudPageLayout::OnCbnSelchangeComboFilelist)
	ON_BN_CLICKED(IDC_REMOVEMODEL, &CPointCloudPageLayout::OnBnClickedRemovemodel)
END_MESSAGE_MAP()


// CPointCloudPageLayout 消息处理程序


void CPointCloudPageLayout::OnEnKillfocusModelStep()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	UpdateData(FALSE);
}


void CPointCloudPageLayout::OnEnKillfocusModelX()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	UpdateData(FALSE);
}


void CPointCloudPageLayout::OnEnKillfocusModelY()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	UpdateData(FALSE);
}


void CPointCloudPageLayout::OnEnKillfocusModelZ()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	UpdateData(FALSE);
}


void CPointCloudPageLayout::OnBnClickedAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	UpdateData(FALSE);
	if(m_chkX) m_edtModel_X += m_edtModelStep;
	if(m_chkY) m_edtModel_Y += m_edtModelStep;
	if(m_chkZ) m_edtModel_Z += m_edtModelStep;
	UpdateData(FALSE); //用变量值更新控件值

	gGlobalPara.meshes_.GetAt(gGlobalPara.nActiveMesh_).SetPos(D3DXVECTOR3(m_edtModel_X,m_edtModel_Y,m_edtModel_Z));


}


void CPointCloudPageLayout::OnBnClickedMinus()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	UpdateData(FALSE);
	if(m_chkX) m_edtModel_X -= m_edtModelStep;
	if(m_chkY) m_edtModel_Y -= m_edtModelStep;
	if(m_chkZ) m_edtModel_Z -= m_edtModelStep;
	UpdateData(FALSE); //用变量值更新控件值

	gGlobalPara.meshes_.GetAt(gGlobalPara.nActiveMesh_).SetPos(D3DXVECTOR3(m_edtModel_X,m_edtModel_Y,m_edtModel_Z));
}


void CPointCloudPageLayout::OnBnClickedLoadmodel()
{
	// TODO: 在此添加控件通知处理程序代码
	WCHAR filename[120];
	WCHAR szFilters[]=L"ply(*.ply)|*.ply";
	CFileDialog opendlg(TRUE, L"ply",L"PointCloud",OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters,this);
	opendlg.m_pOFN->lpstrTitle = L"Open a model file";

	opendlg.m_ofn.lpstrInitialDir=L"F:\\Visual Studio Projects\\D3DPointCloud\\media"; //设置当前路径
	if(opendlg.DoModal() == IDOK)
		//_tcscpy(filename , opendlg.GetPathName().GetString());
		wcscpy_s(filename , opendlg.GetPathName().GetString());
	else
		return ;

	int nIndex = m_cboFileList.FindStringExact( 0,opendlg.GetFileName().GetString()); 

	CPlyMeshArcBall* pNewMesh=NULL;
	if(nIndex != CB_ERR)   //已经加载
	{
		m_cboFileList.SetCurSel(nIndex);
		pNewMesh =&gGlobalPara.meshes_.GetAt(nIndex);
		gGlobalPara.m_edtModel_X = pNewMesh->GetPos().x;
		gGlobalPara.m_edtModel_Y = pNewMesh->GetPos().y;
		gGlobalPara.m_edtModel_Z = pNewMesh->GetPos().z;
		UpdateDataFromGlobal();

	}
	else  // 打开文件
	{
		m_cboFileList.AddString(opendlg.GetFileName().GetString());
		m_cboFileList.SetCurSel(m_cboFileList.GetCount()-1);
		pNewMesh = new CPlyMeshArcBall();
		pNewMesh->Create(filename,gGlobalPara.pd3dDevice);
		gGlobalPara.meshes_.Add(*pNewMesh);
		gGlobalPara.m_edtModel_X = pNewMesh->GetPos().x;
		gGlobalPara.m_edtModel_Y = pNewMesh->GetPos().y;
		gGlobalPara.m_edtModel_Z = pNewMesh->GetPos().z;
		UpdateDataFromGlobal();
		SAFE_DELETE(pNewMesh);
	}
	gGlobalPara.nActiveMesh_ = m_cboFileList.GetCurSel();

}


void CPointCloudPageLayout::OnCbnSelchangeComboFilelist()
{
	// TODO: 在此添加控件通知处理程序代码
	CPlyMeshArcBall* pNewMesh = &gGlobalPara.meshes_.GetAt(m_cboFileList.GetCurSel());
	gGlobalPara.nActiveMesh_ = m_cboFileList.GetCurSel();

	gGlobalPara.m_edtModel_X = pNewMesh->GetPos().x;
	gGlobalPara.m_edtModel_Y = pNewMesh->GetPos().y;
	gGlobalPara.m_edtModel_Z = pNewMesh->GetPos().z;
	UpdateDataFromGlobal();

}


void CPointCloudPageLayout::OnBnClickedRemovemodel()
{
	// TODO: 在此添加控件通知处理程序代码
	int nIndex = m_cboFileList.GetCurSel();
	if(nIndex < 0)
		return ;
	
	gGlobalPara.meshes_.Remove(nIndex);
	m_cboFileList.DeleteString(nIndex);
	
	if(m_cboFileList.GetCount()<1)
		return ;
	if(nIndex >= m_cboFileList.GetCount()-1)
		nIndex = 0;
	
	m_cboFileList.SetCurSel(nIndex);
	gGlobalPara.nActiveMesh_ = nIndex;

	CPlyMeshArcBall* pNewMesh = &gGlobalPara.meshes_.GetAt(m_cboFileList.GetCurSel());
	gGlobalPara.m_edtModel_X = pNewMesh->GetPos().x;
	gGlobalPara.m_edtModel_Y = pNewMesh->GetPos().y;
	gGlobalPara.m_edtModel_Z = pNewMesh->GetPos().z;
	UpdateDataFromGlobal();
}
