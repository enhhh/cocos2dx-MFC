
// sceneEditorView.h : CsceneEditorView 类的接口
//

#pragma once
#include "AppDelegate.h"


class CsceneEditorView : public CView
{
protected: // 仅从序列化创建
	CsceneEditorView();
	DECLARE_DYNCREATE(CsceneEditorView)

// 特性
public:
	CsceneEditorDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CsceneEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();

	AppDelegate m_app;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};

#ifndef _DEBUG  // sceneEditorView.cpp 中的调试版本
inline CsceneEditorDoc* CsceneEditorView::GetDocument() const
   { return reinterpret_cast<CsceneEditorDoc*>(m_pDocument); }
#endif

