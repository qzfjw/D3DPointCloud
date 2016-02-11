#pragma once
#include "afxwin.h"



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
	void UpdateDataFromGlobal();

	DECLARE_MESSAGE_MAP()
public:
	// 增加或减少的量
	float m_edtModelStep;
	afx_msg void OnEnKillfocusModelStep();
	// X坐标值
	float m_edtModel_X;
	// Y坐标值
	float m_edtModel_Y;
	// Z坐标值
	float m_edtModel_Z;
	// 是否选中X轴
	BOOL m_chkX;
	// 是否选中Y轴
	BOOL m_chkY;
	// 是否选中Z轴
	BOOL m_chkZ;
	afx_msg void OnEnKillfocusModelX();
	afx_msg void OnEnKillfocusModelY();
	afx_msg void OnEnKillfocusModelZ();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedMinus();
	afx_msg void OnBnClickedLoadmodel();
	// 模型文件名列表
	CComboBox m_cboFileList;
	afx_msg void OnCbnSelchangeComboFilelist();
	afx_msg void OnBnClickedRemovemodel();
};
