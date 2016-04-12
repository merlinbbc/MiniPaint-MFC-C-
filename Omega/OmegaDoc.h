
// OmegaDoc.h : интерфейс класса COmegaDoc
//


#pragma once
#include "ConstantsMenu.h"


class COmegaDoc : public CDocument
{
protected: // создать только из сериализации
	COmegaDoc();
	DECLARE_DYNCREATE(COmegaDoc)

// Атрибуты
public:

// Операции
public:

// Переопределение
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Реализация
public:
	virtual ~COmegaDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	ElementType GetElementType();
	afx_msg void OnElementCircle();
	afx_msg void OnElementRectangle();
	afx_msg void OnElementStar();
	afx_msg void OnElementArrow();

	
private:
	ElementType elementType;
public:
	afx_msg void OnUpdateElementCircle(CCmdUI *pCmdUI);
	afx_msg void OnUpdateElementRectangle(CCmdUI *pCmdUI);
	afx_msg void OnUpdateElementStar(CCmdUI *pCmdUI);
	afx_msg void OnUpdateElementArrow(CCmdUI *pCmdUI);
	afx_msg void OnOperationMove();
	afx_msg void OnOperationDelete();
};
