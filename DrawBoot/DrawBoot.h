
// DrawBoot.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDrawBootApp: 
// �йش����ʵ�֣������ DrawBoot.cpp
//

class CDrawBootApp : public CWinApp
{
public:
	CDrawBootApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDrawBootApp theApp;