
// OmegaView.cpp : реализация класса COmegaView
#include "stdafx.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "Omega.h"
#endif

#include "Star.h"
#include "OmegaDoc.h"
#include "OmegaView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// COmegaView
IMPLEMENT_DYNCREATE(COmegaView, CView)
BEGIN_MESSAGE_MAP(COmegaView, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &COmegaView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_FILE_SAVE, &COmegaView::OnFileSave)
	ON_COMMAND(ID_FILE_OPEN, &COmegaView::OnFileOpen)
END_MESSAGE_MAP()

// создание/уничтожение COmegaView

COmegaView::COmegaView() : m_StartPoint(0), m_EndPoint(0), m_pTempElement(nullptr), fromID(0), toID(0), ID(0),
choose(false), fromPoint(0), toPoint(0)
{
	// TODO: добавьте код создания

}

COmegaView::~COmegaView()
{
	POSITION pos = Elements_List.GetHeadPosition();
	for (int i = 0; i < Elements_List.GetSize(); i++)
	{
		auto var = Elements_List.GetNext(pos);///////////////////////////////////////
		//pos = Elements_List.Find(var);
		delete var;//memory list realese
		var = nullptr;
	}
}

BOOL COmegaView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}
// рисование COmegaView
void COmegaView::OnDraw(CDC* pDC)
{
	COmegaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	POSITION pos = Elements_List.GetHeadPosition();
	for (int i = 0; i < Elements_List.GetSize(); i++)
	{
		auto var = Elements_List.GetNext(pos);///////////////////////////////////////
		var->Draw(pDC, BLACK);//redraw objects BLACK
		
	}
}
// печать COmegaView
void COmegaView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL COmegaView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void COmegaView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void COmegaView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}

void COmegaView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void COmegaView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

// диагностика COmegaView

#ifdef _DEBUG
void COmegaView::AssertValid() const
{
	CView::AssertValid();
}

void COmegaView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COmegaDoc* COmegaView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COmegaDoc)));
	return (COmegaDoc*)m_pDocument;
}
#endif //_DEBUG
// обработчики сообщений COmegaView


void COmegaView::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetCapture();//перехватывать все последующие сообщения
	m_StartPoint = point;//точка нажатия мышки
	//CElement* element = getElement(point);
	COmegaDoc* pDoc = GetDocument();
	if ((pDoc->GetElementType() == ARROW))
	{
		CElement* element = getElement(point);
		if (element)
		{
			if (!choose)
			{
				element->GetRuntimeClass();
				fromID = element->GetID();
				fromPoint.x = element->GetEndPoint().x - (element->GetEndPoint().x - element->GetStartPoint().x) / 2;
				fromPoint.y = element->GetEndPoint().y - (element->GetEndPoint().y - element->GetStartPoint().y) / 2;
				choose = !choose;
			}
			else
			{
				if (fromID != element->GetID())
				{
					toID = element->GetID();
					toPoint.x = element->GetEndPoint().x - (element->GetEndPoint().x - element->GetStartPoint().x) / 2;
					toPoint.y = element->GetEndPoint().y - (element->GetEndPoint().y - element->GetStartPoint().y) / 2;
					choose = !choose;
				}
			}
		}
	}
}


void COmegaView::OnLButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();
	CClientDC aDC(this);
	COmegaDoc* pDoc = GetDocument();//получаем указатель на класс документа 
	switch (pDoc->GetElementType())
	{
	case DEL:
	{

		CElement* element_for_del = getElement(point);
		if (element_for_del)
		{
			int id = element_for_del->GetID();
			element_for_del->Draw(&aDC, WHITE);

			Elements_List.RemoveAt(Elements_List.Find(element_for_del));
			delete element_for_del;
			element_for_del = nullptr;
			POSITION pos = Elements_List.GetHeadPosition();
			for (int i = 0; i < Elements_List.GetSize(); i++)
			{
				auto elem = Elements_List.GetNext(pos);///////////////////////////////////////
				if (elem->fromID == id || (elem)->toID == id)
				{
					(elem)->Draw(&aDC, WHITE);
					Elements_List.RemoveAt(Elements_List.Find(elem));
				}
			}


		}
		break;
	}

	case MOVE:
	{
		CElement* element_for_move = getElement(m_StartPoint);
		if (element_for_move)
		{
			CPoint scale;
			scale.x = (element_for_move->GetEndPoint()).x - (element_for_move->GetStartPoint()).x;
			scale.y = (element_for_move->GetEndPoint()).y - (element_for_move->GetStartPoint()).y;
			element_for_move->Draw(&aDC, WHITE);
			element_for_move->SetStartPoint(point);
			point.x += scale.x;
			point.y += scale.y;
			element_for_move->SetEndPoint(point);
			element_for_move->Draw(&aDC, BLACK);
			POSITION pos = Elements_List.GetHeadPosition();
			for (int i = 0; i < Elements_List.GetSize(); i++)
			{

				auto var = Elements_List.GetNext(pos);////////////////////////
				if ((var->fromID > 0) || (var->toID > 0)) // it arrow
				{
					if (var->fromID == element_for_move->GetID())
					{
						var->Draw(&aDC, WHITE);

						scale.x = element_for_move->GetEndPoint().x - (element_for_move->GetEndPoint().x - element_for_move->GetStartPoint().x) / 2;
						scale.y = element_for_move->GetEndPoint().y - (element_for_move->GetEndPoint().y - element_for_move->GetStartPoint().y) / 2;

						var->SetStartPoint(scale);
						var->Draw(&aDC, BLACK);
					}
					if (var->toID == element_for_move->GetID())
					{
						var->Draw(&aDC, WHITE);
						scale.x = element_for_move->GetEndPoint().x - (element_for_move->GetEndPoint().x - element_for_move->GetStartPoint().x) / 2;
						scale.y = element_for_move->GetEndPoint().y - (element_for_move->GetEndPoint().y - element_for_move->GetStartPoint().y) / 2;

						var->SetEndPoint(scale);
						var->Draw(&aDC, BLACK);
					}
				}
			}

			element_for_move = nullptr;
		}
		break;
	}
	case ARROW:
	{
		if (!choose)
		{
			m_pTempElement = CreateElement();
			m_pTempElement->Draw(&aDC, BLACK);
			Elements_List.AddTail(m_pTempElement);
			m_pTempElement = nullptr;//обнуляем указатель
			toPoint = fromPoint = 0;
			ID++;
		}
		break;

	}
	default:
	{
		if (m_pTempElement)
		{
			ReleaseCapture();//освободить мышь 
			Elements_List.InsertAfter(Elements_List.GetTailPosition(), m_pTempElement);
			m_pTempElement = nullptr;//обнуляем указатель 
			ID++;
		}
	}
	}

	OnDraw(&aDC);
}


void COmegaView::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC aDC(this);
	COmegaDoc* pDoc = GetDocument();//получаем указатель на класс документа 
	//проверяем нажата ли кнопка мышки и курсор пренадлежит нашему виду 
	switch (pDoc->GetElementType())
	{
	case DEL:
	{
		break;
	}

	case MOVE:
	{
		break;
	}
	case ARROW:
	{
		break;
	}
	default:
	{
		if ((nFlags&MK_LBUTTON) && (this == GetCapture()))
		{
			m_EndPoint = point;
			//если нарисован элемент, то его нужно удалить 
			if (m_pTempElement)
			{
				m_pTempElement->Draw(&aDC, WHITE);//удаляем элемент 
				delete m_pTempElement;//удаляем память 
				m_pTempElement = nullptr;//обнуляем указатель 
			}
			//рисуем последний элемент 
			m_pTempElement = CreateElement();
			if (m_pTempElement)
				m_pTempElement->Draw(&aDC, BLACK);
		}
	}
	}
}

CElement* COmegaView::CreateElement()
{
	COmegaDoc* pDoc = GetDocument();//получаем указатель на класс документа
	switch (pDoc->GetElementType())
	{
	case ARROW:
		return new CArrow(fromPoint, toPoint, fromID, toID, ID);
	case RECTANGLE:
		return new CRectangle(m_StartPoint, m_EndPoint, ID);
	case CIRCLE:
		return new CCircle(m_StartPoint, m_EndPoint, ID);
	case STAR:
		return new CStar(m_StartPoint, m_EndPoint, ID);
	default:
		AfxMessageBox(_T("не известный обьект, не удалось создать [CreateElement]"), MB_OK);
		AfxAbort();//завершение программы
	}
}

CElement* COmegaView::getElement(CPoint point)
{
	POSITION pos = Elements_List.GetHeadPosition();
	for (int i = 0; i < Elements_List.GetSize(); i++)
	{
		auto var = Elements_List.GetNext(pos);////////////////////////
		if ((var->GetBoundRect()).PtInRect(point)) return var;
	}
	return nullptr;
}





void COmegaView::OnFileSave()
{
	CFileDialog dlg(FALSE);
	dlg.DoModal();
	auto PathName = dlg.GetPathName();

	CFile fileS;
	fileS.Open(PathName, CFile::modeCreate | CFile::modeWrite);
	CArchive arStore(&fileS, CArchive::store);

	Elements_List.Serialize(arStore);
	Elements_List.RemoveAll();
	arStore.Flush();
	arStore.Close();
	fileS.Flush();
	fileS.Close();
}


void COmegaView::OnFileOpen()
{
	CFileDialog dlg(TRUE);
	dlg.DoModal();
	auto PathName = dlg.GetPathName();

	CFile fileS;
	fileS.Open(PathName, CFile::modeRead);
	CArchive arStore(&fileS, CArchive::load);
	Elements_List.Serialize(arStore);
	
	CClientDC aDC(this);
	OnDraw(&aDC);

	fileS.Close();
	arStore.Close();
}
