// PointCloudPageLayout.cpp : 实现文件
//

#include "stdafx.h"
#include "D3DPointCloud.h"
#include "PointCloudPageLayout.h"
#include "afxdialogex.h"


// CPointCloudPageLayout 对话框

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


// CPointCloudPageLayout 消息处理程序
