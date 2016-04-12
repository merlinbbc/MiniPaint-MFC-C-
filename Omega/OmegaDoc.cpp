
// OmegaDoc.cpp : ���������� ������ COmegaDoc
//

#include "stdafx.h"
// SHARED_HANDLERS ����� ���������� � ������������ �������� ��������� ���������� ������� ATL, �������
// � ������; ��������� ��������� ������������ ��� ��������� � ������ �������.
#ifndef SHARED_HANDLERS
#include "Omega.h"
#endif

#include "OmegaDoc.h"
#include "OmegaView.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// COmegaDoc

IMPLEMENT_DYNCREATE(COmegaDoc, CDocument)

BEGIN_MESSAGE_MAP(COmegaDoc, CDocument)
	ON_COMMAND(ID_32771, &COmegaDoc::OnElementCircle)
	ON_COMMAND(ID_32772, &COmegaDoc::OnElementRectangle)
	ON_COMMAND(ID_32773, &COmegaDoc::OnElementStar)
	ON_COMMAND(ID_32774, &COmegaDoc::OnElementArrow)
	ON_UPDATE_COMMAND_UI(ID_32771, &COmegaDoc::OnUpdateElementCircle)
	ON_UPDATE_COMMAND_UI(ID_32772, &COmegaDoc::OnUpdateElementRectangle)
	ON_UPDATE_COMMAND_UI(ID_32773, &COmegaDoc::OnUpdateElementStar)
	ON_UPDATE_COMMAND_UI(ID_32774, &COmegaDoc::OnUpdateElementArrow)
	ON_COMMAND(ID_OPERATION_MOVE, &COmegaDoc::OnOperationMove)
	ON_COMMAND(ID_OPERATION_DELETE, &COmegaDoc::OnOperationDelete)
END_MESSAGE_MAP()


// ��������/����������� COmegaDoc

COmegaDoc::COmegaDoc():elementType(CIRCLE)
{
	
	// TODO: �������� ��� ��� ������������ ������ ������������
}

COmegaDoc::~COmegaDoc()
{
}

BOOL COmegaDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �������� ��� ��������� �������������
	// (��������� SDI ����� �������� ������������ ���� ��������)

	return TRUE;
}
// ������������ COmegaDoc
void COmegaDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �������� ��� ����������
	}
	else
	{
		// TODO: �������� ��� ��������
	}
}

#ifdef SHARED_HANDLERS

// ��������� ��� �������
void COmegaDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �������� ���� ��� ��� ����������� ������ ���������
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ��������� ������������ ������
void COmegaDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������� ���������� ������ �� ������ ���������. 
	// ����� ����������� ������ ����������� ������ � ������� ";"

	// ��������:  strSearchContent = _T("�����;�������������;����;������ ole;");
	SetSearchContent(strSearchContent);
}

void COmegaDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// ����������� COmegaDoc

#ifdef _DEBUG
void COmegaDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COmegaDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// ������� COmegaDoc

void COmegaDoc::OnElementCircle()
{
	elementType = CIRCLE;
}

void COmegaDoc::OnElementRectangle()
{
	elementType = RECTANGLE;
}

void COmegaDoc::OnElementStar()
{
	elementType = STAR;
}

void COmegaDoc::OnElementArrow()
{
	elementType = ARROW;
}

void COmegaDoc::OnUpdateElementCircle(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(elementType == CIRCLE);
}

void COmegaDoc::OnUpdateElementRectangle(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(elementType == RECTANGLE);
}

void COmegaDoc::OnUpdateElementStar(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(elementType == STAR);
}

void COmegaDoc::OnUpdateElementArrow(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(elementType == ARROW);
}

ElementType COmegaDoc::GetElementType()
{
	return elementType;
}

void COmegaDoc::OnOperationMove()
{
	elementType = MOVE;
}


void COmegaDoc::OnOperationDelete()
{
	elementType = DEL;
}


