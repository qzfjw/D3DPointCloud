#pragma once
#include "afxwin.h"

#include "d3dx9.h"


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
	void UpdateDataFromGlobal();

	DECLARE_MESSAGE_MAP()
public:
	D3DXMATRIX rigidtransformation_mat_;
	// ���ӻ���ٵ���
	float m_edtModelStep;
	afx_msg void OnEnKillfocusModelStep();
	// X����ֵ
	float m_edtModel_X;
	// Y����ֵ
	float m_edtModel_Y;
	// Z����ֵ
	float m_edtModel_Z;
	// �Ƿ�ѡ��X��
	BOOL m_chkX;
	// �Ƿ�ѡ��Y��
	BOOL m_chkY;
	// �Ƿ�ѡ��Z��
	BOOL m_chkZ;
	afx_msg void OnEnKillfocusModelX();
	afx_msg void OnEnKillfocusModelY();
	afx_msg void OnEnKillfocusModelZ();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedMinus();
	afx_msg void OnBnClickedLoadmodel();
	// ģ���ļ����б�
	CComboBox m_cboFileList;
	afx_msg void OnCbnSelchangeComboFilelist();
	afx_msg void OnBnClickedRemovemodel();
	afx_msg void OnBnClickedRigidtransformation();
	// ��ʾ��ر任��Ϣ
	CListBox m_lstDisplay;
	// #vertex
	long m_iVertexCount;
	// #vertex
	afx_msg void OnBnClickedApplyrigidtransformation();
	// ICP��������������
	int MaximumIterations_;
	afx_msg void OnEnKillfocusMaximumiterations();
};
