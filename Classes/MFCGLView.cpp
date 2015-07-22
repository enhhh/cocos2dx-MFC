#include "MFCGLView.h"

NS_CC_BEGIN

MFCGLView* MFCGLView::create(HWND hWnd)
{
	MFCGLView* pRet = new MFCGLView();
	if (pRet != NULL && pRet->init(hWnd))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

MFCGLView::MFCGLView(void) : m_hWnd(NULL), m_hDC(NULL), m_hRC(NULL),
m_bCaptured(false), m_fFrameZoomFactor(1)
{
}


MFCGLView::~MFCGLView(void)
{
}


bool MFCGLView::isOpenGLReady()
{
	return (m_hDC != NULL && m_hRC != NULL);
}

void MFCGLView::end()
{
	ReleaseGL();
	release();
}

void MFCGLView::swapBuffers()
{
	if (m_hDC != NULL)
	{
		::SwapBuffers(m_hDC);
	}
}

void MFCGLView::setFrameSize(float width, float height)
{
	GLViewProtocol::setFrameSize(width, height);
	GLViewProtocol::setViewPortInPoints(100, 0, width, height);
 	setDesignResolutionSize(width, height, ResolutionPolicy::NO_BORDER);
 	cocos2d::Director::getInstance()->setProjection(cocos2d::Director::getInstance()->getProjection());
	auto scene = Director::getInstance()->getRunningScene();
	if (scene)
		scene->setContentSize(Size(width, height));
}

void MFCGLView::setIMEKeyboardState(bool bOpen)
{
}

bool MFCGLView::init(HWND hWnd)
{
	if (hWnd == NULL)
	{
		return false;
	}

	m_hWnd = hWnd;
	if (!InitGL())
	{
		return false;
	}

	return true;
}

LRESULT MFCGLView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
		if (MK_LBUTTON == wParam)
		{
			float        _mouseX = (short)LOWORD(lParam);
			float        _mouseY = (short)HIWORD(lParam);

			if (this->getViewPortRect().equals(Rect::ZERO) || this->getViewPortRect().containsPoint(Vec2(_mouseX, _mouseY)))
			{
				intptr_t id = 0;
				this->handleTouchesBegin(1, &id, &_mouseX, &_mouseY);
				m_bCaptured = true;
			}
			EventMouse event(EventMouse::MouseEventType::MOUSE_DOWN);
			//Because OpenGL and cocos2d-x uses different Y axis, we need to convert the coordinate here
			event.setCursorPosition(_mouseX, this->getViewPortRect().size.height - _mouseY);
			event.setMouseButton(0);
			Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
		}
		break;
	case WM_MOUSEMOVE:
		if (MK_LBUTTON == wParam && m_bCaptured)
		{
			POINT point = { (short)LOWORD(lParam), (short)HIWORD(lParam) };
			Vec2 pt(point.x, point.y);
			int id = 0;
			pt.x /= m_fFrameZoomFactor;
			pt.y /= m_fFrameZoomFactor;
			handleTouchesMove(1, &id, &pt.x, &pt.y);
			EventMouse event(EventMouse::MouseEventType::MOUSE_MOVE);
			//Because OpenGL and cocos2d-x uses different Y axis, we need to convert the coordinate here
			event.setCursorPosition(_mouseX, this->getViewPortRect().size.height - _mouseY);
			Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
		}
		break;
	case WM_LBUTTONUP:
		if (m_bCaptured)
		{
			POINT point = { (short)LOWORD(lParam), (short)HIWORD(lParam) };
			Vec2 pt(point.x, point.y);
			int id = 0;
			pt.x /= m_fFrameZoomFactor;
			pt.y /= m_fFrameZoomFactor;
			handleTouchesEnd(1, &id, &pt.x, &pt.y);

			ReleaseCapture();
			m_bCaptured = false;
			EventMouse event(EventMouse::MouseEventType::MOUSE_UP);
			//Because OpenGL and cocos2d-x uses different Y axis, we need to convert the coordinate here
			event.setCursorPosition(_mouseX, this->getViewPortRect().size.height - _mouseY);
			event.setMouseButton(0);
			Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
		}
		break;
	case WM_SIZE:
		switch (wParam)
		{
		case SIZE_RESTORED:
			Application::getInstance()->applicationWillEnterForeground();
			break;
		case SIZE_MINIMIZED:
			Application::getInstance()->applicationDidEnterBackground();
			break;
		}
		break;
	case WM_KEYDOWN:
	{
					   //EventKeyboard event(g_keyCodeMap[wParam], TRUE);
					   //auto dispatcher = Director::getInstance()->getEventDispatcher();
					   //dispatcher->dispatchEvent(&event);
	}
		break;
	default:
		break;
	}

	return 0;
}

bool MFCGLView::InitGL()
{
	//初始化窗口像素格式
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),  // size
		1,                          // version
		PFD_SUPPORT_OPENGL |        // OpenGL window
		PFD_DRAW_TO_WINDOW |        // render to window
		PFD_DOUBLEBUFFER,           // support double-buffering
		PFD_TYPE_RGBA,              // color type
		32,                         // preferred color depth
		0, 0, 0, 0, 0, 0,           // color bits (ignored)
		0,                          // no alpha buffer
		0,                          // alpha bits (ignored)
		0,                          // no accumulation buffer
		0, 0, 0, 0,                 // accum bits (ignored)
		24,                         // depth buffer
		8,                          // no stencil buffer
		0,                          // no auxiliary buffers
		PFD_MAIN_PLANE,             // main layer
		0,                          // reserved
		0, 0, 0,                    // no layer, visible, damage masks
	};

	m_hDC = GetDC(m_hWnd);
	int pixelFormat = ChoosePixelFormat(m_hDC, &pfd);
	SetPixelFormat(m_hDC, pixelFormat, &pfd);

	//创建渲染环境
	m_hRC = wglCreateContext(m_hDC);
	wglMakeCurrent(m_hDC, m_hRC);

	//check OpenGL version at first
	const GLubyte* glVersion = glGetString(GL_VERSION);
	log("OpenGL version = %s", glVersion);

	if (atof((const char*)glVersion) < 1.5)
	{
		log("OpenGL 1.5 or higher is required. Please upgrade the driver of your video card.");
		return false;
	}

//	setFrameSize(600, 450);

	GLenum GlewInitResult = glewInit();
	if (GLEW_OK != GlewInitResult)
	{
		log("OpenGL error\n\t%s", (char *)glewGetErrorString(GlewInitResult));
		return false;
	}

	if (GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader)
	{
		log("Ready for GLSL");
	}
	else
	{
		log("Not totally ready :(");
	}

	if (glewIsSupported("GL_VERSION_2_0"))
	{
		log("Ready for OpenGL 2.0");
	}
	else
	{
		log("OpenGL 2.0 not supported");
	}


	// Enable point size by default on windows.
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

	return true;
}

void MFCGLView::ReleaseGL()
{
	if (m_hDC != NULL && m_hRC != NULL)
	{
		wglMakeCurrent(m_hDC, NULL);
		wglDeleteContext(m_hRC);
	}
}

NS_CC_END