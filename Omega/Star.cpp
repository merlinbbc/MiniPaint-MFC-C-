#include "stdafx.h"
#include "Star.h"

IMPLEMENT_SERIAL(CStar, CElement, 1)

CStar::~CStar()
{
}

CStar::CStar()
{
}

void CStar::Serialize(CArchive & arch)
{
	CElement::Serialize(arch);
	if (arch.IsStoring())
	{
		arch << m_StartPoint << m_EndPoint << ID;
	}
	else
	{
		arch >> m_StartPoint >> m_EndPoint >> ID;
	}
}

CStar::CStar(const CPoint& start, const CPoint& end, int id)
{
	ID = id;
	m_PenWidth = 1;
	m_StartPoint = start;
	m_EndPoint = end;
	//описывающий четырехугольник
	m_EnclosingRect = CRect(m_StartPoint, m_EndPoint);
	//нормализация
	m_EnclosingRect.NormalizeRect();

}

void CStar::Draw(CDC* pDC, COLORREF color)
{
	m_EnclosingRect = CRect(m_StartPoint, m_EndPoint);
	CPen aPen;//объект перо
	//если не удалось создать перо, то сообщение и выход
	if (!aPen.CreatePen(PS_SOLID, m_PenWidth, color))
	{
		AfxMessageBox(_T("не удалось создать перо для звезды"), MB_OK);
		AfxAbort();
	}
	CPoint start = m_StartPoint;
	CPoint end = m_EndPoint;

	m_StartPoint.x = min(start.x, end.x);
	m_StartPoint.y = min(start.y, end.y);

	m_EndPoint.x = max(start.x, end.x);
	m_EndPoint.y = max(start.y, end.y);
	//выбираем созданое перо и нулевую кисть
	CPen* pOldPen = pDC->SelectObject(&aPen);
	CBrush* pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);

	CPoint dot1, dot2, dot3, dot4, dot5;
	dot1.x = m_StartPoint.x + abs(m_EndPoint.x - m_StartPoint.x) / 2;
	dot1.y = m_StartPoint.y;

	dot2.x = m_EndPoint.x;
	dot2.y = m_StartPoint.y + abs(m_EndPoint.y - m_StartPoint.y) / 2;

	dot3 = m_EndPoint;

	dot4.x = m_StartPoint.x;
	dot4.y = m_EndPoint.y;

	dot5.x = m_StartPoint.x;
	dot5.y = m_StartPoint.y + abs(m_EndPoint.y - m_StartPoint.y) / 2;

	//рисуем звезду
	pDC->MoveTo(dot1);
	pDC->LineTo(dot3);
	pDC->LineTo(dot5);
	pDC->LineTo(dot2);
	pDC->LineTo(dot4);
	pDC->LineTo(dot1);


	//восстанавливаем кисть и перо
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}
