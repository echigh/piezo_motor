
// piezo_1.0.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cpiezo_10App: 
// �йش����ʵ�֣������ piezo_1.0.cpp
//

class Cpiezo_10App : public CWinApp
{
public:
	Cpiezo_10App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cpiezo_10App theApp;