
// D3DPointCloud.h : D3DPointCloud 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CD3DPointCloudApp:
// 有关此类的实现，请参阅 D3DPointCloud.cpp
//

class CD3DPointCloudApp : public CWinApp
{
public:
	CD3DPointCloudApp();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnIdle(LONG lCount);
};

extern CD3DPointCloudApp theApp;
