#pragma once



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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};


