
// D3DPointCloud.h : D3DPointCloud Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CD3DPointCloudApp:
// �йش����ʵ�֣������ D3DPointCloud.cpp
//

class CD3DPointCloudApp : public CWinApp
{
public:
	CD3DPointCloudApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnIdle(LONG lCount);
};

extern CD3DPointCloudApp theApp;
