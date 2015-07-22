#pragma once
#include "afxwin.h"
// #include "cocos2d.h"
// #include "cocos-ext.h"
// #include "AppDelegate.h"
 #include "MFCGLView.h"
 USING_NS_CC;
// USING_NS_CC_EXT;
class CocosWin :
	public CWnd
{
public:

	CocosWin();

	~CocosWin();

	BOOL createCocosWin();

	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);

protected:
	BOOL m_isInited;
	MFCGLView* m_glview;
};

