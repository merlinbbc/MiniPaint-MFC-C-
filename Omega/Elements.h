#pragma once
#include <cmath>
// CElement command target

class CElement : public CObject
{
protected:
	int ID;
	
	int m_PenWidth;//������ ����
	CRect m_EnclosingRect;//����������� ���������������
	CPoint m_StartPoint;
	CPoint m_EndPoint;

public:
	DECLARE_SERIAL(CElement)
	void Serialize(CArchive& archive);
	int toID;
	int fromID;
	int GetID()
	{
		return ID;
	}
	void SetStartPoint(CPoint point);
	void SetEndPoint(CPoint point);
	CPoint GetStartPoint();
	CPoint GetEndPoint();
	virtual ~CElement();
	virtual void Draw(CDC* pDC, COLORREF color){};//������ ������
	virtual CRect GetBoundRect();//���������� ����������� ���������������
protected:
	CElement();//�������������� ������ � �������
};

class CArrow : public CElement
{
public:
	DECLARE_SERIAL(CArrow)
protected:
	
	//CPoint m_StartPoint;
	//CPoint m_EndPoint;

public:
	void Serialize(CArchive& archive);
	~CArrow();
	void Draw(CDC* pDC, COLORREF color);//������� ���������
	//����������� ��������������
	CArrow(const CPoint& start, const CPoint& end, int fromid, int toid, int id);
protected:
	CArrow();//������ ������
};

class CRectangle : public CElement
{
protected:
	//CPoint m_StartPoint;
	//CPoint m_EndPoint;
public:
	DECLARE_SERIAL(CRectangle)
	void Serialize(CArchive& archive);
	~CRectangle();
	void Draw(CDC* pDC,COLORREF color);//������� ���������
	CRectangle(const CPoint& start, const CPoint& end, int id);
protected:
	CRectangle();
};



class CCircle : public CElement
{
protected:
	//CPoint m_StartPoint;
	//CPoint m_EndPoint;
public:
	DECLARE_SERIAL(CCircle)
	void Serialize(CArchive& archive);
	~CCircle();
	void Draw(CDC* pDC, COLORREF color);
	CCircle(const CPoint& start, const CPoint& end, int id);
protected:
	CCircle();//������ ������
};

