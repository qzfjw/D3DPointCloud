// PointCloudPageLayout.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "D3DPointCloud.h"
#include "PointCloudPageLayout.h"
#include "afxdialogex.h"


// CPointCloudPageLayout �Ի���

IMPLEMENT_DYNAMIC(CPointCloudPageLayout, CPropertyPage)

CPointCloudPageLayout::CPointCloudPageLayout()
	: CPropertyPage(CPointCloudPageLayout::IDD)
{

}

CPointCloudPageLayout::~CPointCloudPageLayout()
{
}

void CPointCloudPageLayout::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPointCloudPageLayout, CPropertyPage)
END_MESSAGE_MAP()


// CPointCloudPageLayout ��Ϣ�������
