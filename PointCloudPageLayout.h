#pragma once


// CPointCloudPageLayout �Ի���

class CPointCloudPageLayout : public CPropertyPage
{
	DECLARE_DYNAMIC(CPointCloudPageLayout)

public:
	CPointCloudPageLayout();
	virtual ~CPointCloudPageLayout();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_LAYOUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
