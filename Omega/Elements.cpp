// Elements.cpp : implementation file
//

#include "stdafx.h"
#include "Omega.h"
#include "Elements.h"
IMPLEMENT_SERIAL(CElement, CObject, 1)
IMPLEMENT_SERIAL(CCircle, CElement, 1)
IMPLEMENT_SERIAL(CRectangle, CElement, 1)
IMPLEMENT_SERIAL(CArrow, CElement, 1)
// CElement

CElement::CElement()
{
}
CElement::~CElement()
{
}
CArrow::CArrow()
{
}
CArrow::~CArrow()
{
}
CRectangle::CRectangle()
{
}
CRectangle::~CRectangle()
{
}

void CElement::SetEndPoint(CPoint point)
{
	m_EndPoint = point;
}
void CElement::SetStartPoint(CPoint point)
{
	m_StartPoint = point;
}
CPoint CElement::GetStartPoint()
{
	return m_StartPoint;
}
CPoint CElement::GetEndPoint()
{
	return m_EndPoint;
}

// CElement member functions
CRect CElement::GetBoundRect()
{
	CRect r(m_EnclosingRect);//конструирование
	r.InflateRect(m_PenWidth, m_PenWidth);//увеличиваем четырехугольник на ширину пера
	return r;//возврат описывающего четырехугольника
}

void CElement::Serialize(CArchive & arch)
{
	CObject::Serialize(arch);
	if (arch.IsStoring())
	{
		arch << m_StartPoint << m_EndPoint << ID;
	}
	else
	{
		arch >> m_StartPoint >> m_EndPoint >> ID;
	}

}

CArrow::CArrow(const CPoint& start, const CPoint& end, int fromid, int toid, int id)
{
	fromID = fromid;
	toID = toid;
	m_StartPoint = start;//перва€ точка
	m_EndPoint = end;
	ID = id;
	m_PenWidth = 2;//ширина
}

void CArrow::Serialize(CArchive & arch)
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

void CArrow::Draw(CDC* pDC, COLORREF color)
{
	m_EnclosingRect = CRect(m_StartPoint, m_EndPoint);//описывающий четырехугольник
	CPen aPen;
	if (!aPen.CreatePen(PS_SOLID, m_PenWidth, color))
	{
		//выводим сообщение о неудаче и завершаем программу 
		AfxMessageBox(_T("Ќе удалось создать перо дл€ линии"), MB_OK);
		AfxAbort();//завершение программы 
	}
	//выбираем новое перо и сохран€ем старое 
	CPen* pOldPen = pDC->SelectObject(&aPen);

	double x3 = m_EndPoint.x, y3 = m_EndPoint.y, PI = 3.14, LenNodVLine = -10, AngNodVLine = 10;
	double alpha = atan(double(m_EndPoint.y - m_StartPoint.y) / double(m_EndPoint.x - m_StartPoint.x));
	if ((m_EndPoint.x - m_StartPoint.x) >= 0) alpha += PI;
	double x4 = x3 + LenNodVLine*cos(alpha - AngNodVLine);
	double x5 = x3 + LenNodVLine*cos(alpha + AngNodVLine);
	double y4 = y3 + LenNodVLine*sin(alpha - AngNodVLine);
	double y5 = y3 + LenNodVLine*sin(alpha + AngNodVLine);
	CPoint LINK[4];
	LINK[0].x = (long)x3;
	LINK[0].y = (long)y3;
	LINK[1].x = (long)x4;
	LINK[1].y = (long)y4;
	LINK[2].x = (long)x5;
	LINK[2].y = (long)y5;

	pDC->MoveTo(m_StartPoint.x, m_StartPoint.y);
	pDC->LineTo(m_EndPoint.x, m_EndPoint.y);
	pDC->Polygon(LINK, 3);
	pDC->SelectObject(pOldPen);
}

CRectangle::CRectangle(const CPoint& start, const CPoint& end, int id)
{
	m_StartPoint = start;//перва€ точка
	m_EndPoint = end;
	ID = id;
	m_PenWidth = 1;//ширина пера
	m_EnclosingRect = CRect(m_StartPoint, m_EndPoint);//описывающий четырехугольник
	m_EnclosingRect.NormalizeRect();//нормализаци€
}

void CRectangle::Serialize(CArchive & arch)
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

void CRectangle::Draw(CDC* pDC, COLORREF color)
{
	m_EnclosingRect = CRect(m_StartPoint, m_EndPoint);//описывающий четырехугольник
	CPen aPen;//перо
	//если неудалось создать перо, то выводим сообщение и закрываем программу
	if (!aPen.CreatePen(PS_SOLID, m_PenWidth, color))
	{
		AfxMessageBox(_T("Ќе удалось создать перо дл€ пр€моугольника"), MB_OK);//вывод сообщени€
		AfxAbort();//завершение программы
	}

	//сохран€ем старое перо и кисть
	CPen* pOldPen = pDC->SelectObject(&aPen);
	CBrush* pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);

	//рисуем
	pDC->Rectangle(m_EnclosingRect);//рисуем черырехугольник

	//восстанавливаем
	pDC->SelectObject(pOldPen);//восстановить старое перо
	pDC->SelectObject(pOldBrush);//восстановить старую кисть
}

CCircle::CCircle(const CPoint& start, const CPoint& end, int id)
{
	ID = id;
	//находим радиус
	long Radius = static_cast<long>(sqrt(static_cast<double>(
		(start.x - end.x)*(start.x - end.x) +
		(start.y - end.y)*(start.y - end.y)
		)));
	//формируем точки
	m_StartPoint.x = start.x - Radius;
	m_StartPoint.y = start.y - Radius;
	m_EndPoint.x = start.x + Radius;
	m_EndPoint.y = start.y + Radius;

	m_PenWidth = 1;

	//описывающий четырехугольник
	m_EnclosingRect = CRect(m_StartPoint, m_EndPoint);
	//нормализаци€
	m_EnclosingRect.NormalizeRect();
}

void CCircle::Serialize(CArchive & arch)
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

void CCircle::Draw(CDC* pDC, COLORREF color)
{
	m_EnclosingRect = CRect(m_StartPoint, m_EndPoint);//описывающий четырехугольник
	CPen aPen;//объект перо
	//если не удалось создать перо, то сообщение и выход
	if (!aPen.CreatePen(PS_SOLID, m_PenWidth, color))
	{
		AfxMessageBox(_T("не удалось создать перо дл€ круга"), MB_OK);
		AfxAbort();
	}

	//выбираем созданое перо и нулевую кисть
	CPen* pOldPen = pDC->SelectObject(&aPen);
	CBrush* pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);

	//рисуем элипс
	pDC->Ellipse(m_EnclosingRect);

	//восстанавливаем кисть и перо
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}

CCircle::CCircle()
{
}

CCircle::~CCircle()
{
}