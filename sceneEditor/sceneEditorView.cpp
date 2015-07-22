
// sceneEditorView.cpp : CsceneEditorView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "sceneEditor.h"
#endif

#include "sceneEditorDoc.h"
#include "sceneEditorView.h"
#include "MFCGLView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CsceneEditorView

IMPLEMENT_DYNCREATE(CsceneEditorView, CView)

BEGIN_MESSAGE_MAP(CsceneEditorView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CsceneEditorView 构造/析构

CsceneEditorView::CsceneEditorView()
{
	// TODO:  在此处添加构造代码

}

CsceneEditorView::~CsceneEditorView()
{
}

BOOL CsceneEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CsceneEditorView 绘制

void CsceneEditorView::OnDraw(CDC* /*pDC*/)
{
	CsceneEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
}

void CsceneEditorView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CsceneEditorView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CsceneEditorView 诊断

#ifdef _DEBUG
void CsceneEditorView::AssertValid() const
{
	CView::AssertValid();
}

void CsceneEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CsceneEditorDoc* CsceneEditorView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CsceneEditorDoc)));
	return (CsceneEditorDoc*)m_pDocument;
}
#endif //_DEBUG


// CsceneEditorView 消息处理程序


void CsceneEditorView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	RECT rc;
	::GetClientRect(m_hWnd, &rc);
	m_app.init(m_hWnd, rc.right - rc.left, rc.bottom - rc.top);
	SetTimer(1, 15, NULL);
	// TODO:  在此添加专用代码和/或调用基类
}



void CsceneEditorView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	m_app.run();
	CView::OnTimer(nIDEvent);
}


void CsceneEditorView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	m_app.onSize(cx, cy);
	// TODO:  在此处添加消息处理程序代码
}


LRESULT CsceneEditorView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO:  在此添加专用代码和/或调用基类
	m_app.WindowProc(message, wParam, lParam);
	return CView::WindowProc(message, wParam, lParam);
}
