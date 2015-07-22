#ifndef __MFC_GLVIEW__H_
#define __MFC_GLVIEW__H_



#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCGLView.h"

NS_CC_BEGIN

class MFCGLView : public GLView
{
public:
	//创建MFCGLView
	static MFCGLView* create(HWND hWnd);


	//构造析构函数
	MFCGLView(void);
	virtual ~MFCGLView(void);


	//自定义GLView必须重写的函数
	virtual bool isOpenGLReady();
	virtual void end();
	virtual void swapBuffers();
	virtual void setFrameSize(float width, float height);
	virtual void setIMEKeyboardState(bool bOpen);

	//初始化GLView
	virtual bool init(HWND hWnd);

	//窗口消息处理
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

private:
	//初始化OpenGL
	bool InitGL();

	//释放OpenGL
	void ReleaseGL();

	HWND                                m_hWnd;               //View对应的窗口句柄
	HDC                                 m_hDC;                //窗口绘图设备
	HGLRC                               m_hRC;                //OpenGL渲染环境

	bool                                m_bCaptured;          //是否捕捉鼠标
	float                               m_fFrameZoomFactor;   //帧缩放比例
};

NS_CC_END

#endif // !__MFC_GLVIEW__H_