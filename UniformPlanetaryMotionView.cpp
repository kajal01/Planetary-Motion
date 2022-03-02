// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface
// (the "Fluent UI") and is provided only as referential material to supplement the
// Microsoft Foundation Classes Reference and related electronic documentation
// included with the MFC C++ library software.
// License terms to copy, use or distribute the Fluent UI are available separately.
// To learn more about our Fluent UI licensing program, please visit
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// UniformPlanetaryMotionView.cpp : implementation of the CUniformPlanetaryMotionView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "UniformPlanetaryMotion.h"
#endif

#include "UniformPlanetaryMotionDoc.h"
#include "UniformPlanetaryMotionView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUniformPlanetaryMotionView

IMPLEMENT_DYNCREATE(CUniformPlanetaryMotionView, CView)

BEGIN_MESSAGE_MAP(CUniformPlanetaryMotionView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CUniformPlanetaryMotionView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_BUTTON_START, &CUniformPlanetaryMotionView::OnButtonStart)
	ON_COMMAND(ID_BUTTON_SUSPEND, &CUniformPlanetaryMotionView::OnButtonSuspend)
	ON_COMMAND(ID_BUTTON_RESUME, &CUniformPlanetaryMotionView::OnButtonResume)
END_MESSAGE_MAP()

// CUniformPlanetaryMotionView construction/destruction

CUniformPlanetaryMotionView::CUniformPlanetaryMotionView() noexcept
{
	// TODO: add construction code here
	m_pCurrentThread = NULL;

	x = 465;
	y = 250;
	x1 = 350 + 200 * cos(3);
	y1 = 250 + 200 * sin(3);

}

CUniformPlanetaryMotionView::~CUniformPlanetaryMotionView()
{
}

BOOL CUniformPlanetaryMotionView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CUniformPlanetaryMotionView drawing

void CUniformPlanetaryMotionView::OnDraw(CDC* pDC)
{
	CUniformPlanetaryMotionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//outer orbit
	CPen redpen;
	redpen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	CPen* pOldpen = pDC->SelectObject(&redpen);
	pDC->Ellipse(550, 450, 150, 50);

	//inner orbit
	pDC->Ellipse(470, 370, 215, 115);

	//Sun	
	CBrush sun(RGB(255, 255, 0));
	CBrush* pOldpen1 = pDC->SelectObject(&sun);
	pDC->Ellipse(370, 270, 310, 210);
	pDC->SelectObject(pOldpen1);

	//inner planet
	CBrush inner_planet(RGB(0, 0, 255));
	CBrush* pOldpen2 = pDC->SelectObject(&inner_planet);
	pDC->Ellipse(x + 10, y + 10, x - 10, y - 10);

	//outer planet
	pDC->Ellipse(x1 + 10, y1 + 10, x1 - 10, y1 - 10);
	pDC->SelectObject(pOldpen2);


	// TODO: add draw code for native data here
}


// CUniformPlanetaryMotionView printing


void CUniformPlanetaryMotionView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CUniformPlanetaryMotionView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CUniformPlanetaryMotionView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CUniformPlanetaryMotionView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CUniformPlanetaryMotionView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CUniformPlanetaryMotionView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CUniformPlanetaryMotionView diagnostics

#ifdef _DEBUG
void CUniformPlanetaryMotionView::AssertValid() const
{
	CView::AssertValid();
}

void CUniformPlanetaryMotionView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CUniformPlanetaryMotionDoc* CUniformPlanetaryMotionView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CUniformPlanetaryMotionDoc)));
	return (CUniformPlanetaryMotionDoc*)m_pDocument;
}
#endif //_DEBUG


// CUniformPlanetaryMotionView message handlers


void CUniformPlanetaryMotionView::OnButtonStart()
{
	// TODO: Add your command handler code here
	m_pCurrentThread = AfxBeginThread(CUniformPlanetaryMotionView::StartThread, this);
}


void CUniformPlanetaryMotionView::OnButtonSuspend()
{
	// TODO: Add your command handler code here
	m_pCurrentThread->SuspendThread();
}


void CUniformPlanetaryMotionView::OnButtonResume()
{
	// TODO: Add your command handler code here
	m_pCurrentThread->ResumeThread();
}


UINT CUniformPlanetaryMotionView::StartThread(LPVOID Param)
{
	// TODO: Add your implementation code here.
	CUniformPlanetaryMotionView* pView = (CUniformPlanetaryMotionView*)Param;
	CPoint MyPoint(0, 0);
	int j = 0;
	while (1)
	{
		j = j + 6;
		pView->x = 340 + 125 * cos(j);
		pView->y = 240 + 125 * sin(j);

		pView->x1 = 350 + 200 * cos(j + 3);
		pView->y1 = 250 + 200 * sin(j + 3);

		pView->Invalidate();
		Sleep(50);
	}
	return 0;
}
