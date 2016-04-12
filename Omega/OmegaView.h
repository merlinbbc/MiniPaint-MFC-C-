
// OmegaView.h : интерфейс класса COmegaView
//

#pragma once
#include <list>
using namespace std;

class COmegaView : public CView
{
protected: // создать только из сериализации
	COmegaView();
	DECLARE_DYNCREATE(COmegaView)
private:
	int ID;
	int fromID;
	int toID;
	bool choose;
	CPoint fromPoint;
	CPoint toPoint;
	CPoint m_StartPoint;
	CPoint m_EndPoint;
	CElement* m_pTempElement;
	const COLORREF BLACK = RGB(0, 0, 0);
	const COLORREF WHITE = RGB(255, 255, 255);
// Атрибуты
public:
	COmegaDoc* GetDocument() const;
	CElement* CreateElement();
	CList<CElement*> Elements_List;
	
	
// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	CElement* getElement(CPoint point);

// Реализация
public:
	virtual ~COmegaView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnFileSave();
	afx_msg void OnFileOpen();
};

#ifndef _DEBUG  // отладочная версия в OmegaView.cpp
inline COmegaDoc* COmegaView::GetDocument() const
   { return reinterpret_cast<COmegaDoc*>(m_pDocument); }
#endif

