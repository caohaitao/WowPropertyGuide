
// WowPropertyGuide.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CWowPropertyGuideApp: 
// �йش����ʵ�֣������ WowPropertyGuide.cpp
//

class CWowPropertyGuideApp : public CWinApp
{
public:
	CWowPropertyGuideApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CWowPropertyGuideApp theApp;