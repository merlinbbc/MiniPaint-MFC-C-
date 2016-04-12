#pragma once
#include "Elements.h"
class CStar : public CElement
{
protected:
	CStar();
public:
	DECLARE_SERIAL(CStar);
	CStar(const CPoint& start, const CPoint& end, int id);
	void Draw(CDC* pDC, COLORREF color);//функция рисования
	~CStar();
	virtual void Serialize(CArchive& arch);
	

};


