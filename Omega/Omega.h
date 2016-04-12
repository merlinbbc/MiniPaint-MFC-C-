
// Omega.h : главный файл заголовка для приложения Omega
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы
#include "ConstantsMenu.h"
#include "Elements.h"

// COmegaApp:
// О реализации данного класса см. Omega.cpp
//

class COmegaApp : public CWinAppEx
{
public:
	COmegaApp();


// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern COmegaApp theApp;
