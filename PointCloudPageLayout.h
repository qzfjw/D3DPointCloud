#pragma once


// CPointCloudPageLayout 对话框

class CPointCloudPageLayout : public CPropertyPage
{
	DECLARE_DYNAMIC(CPointCloudPageLayout)

public:
	CPointCloudPageLayout();
	virtual ~CPointCloudPageLayout();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_LAYOUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
