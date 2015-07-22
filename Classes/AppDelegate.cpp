#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "MFCGLView.h"

USING_NS_CC;

AppDelegate::AppDelegate()
: m_uWnd(nullptr)
, cocosInited(false){

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
     auto director = Director::getInstance();
	 auto glview = director->getOpenGLView();
	 if (!glview) {
		 return false;
	 }
	 glview->setFrameSize(600, 450);
    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
	auto scene = Scene::create();
	scene->setContentSize(Director::getInstance()->getVisibleSize());
	// run
	director->runWithScene(scene);

	Rect rect(0, 0, 4096, 2048);

	Sprite* grid = Sprite::create("grid1_16x16_new_aaa.png");

	grid->setTextureRect(rect);

	Texture2D::TexParams params = {

		GL_LINEAR,

		GL_LINEAR,

		GL_REPEAT,

		GL_REPEAT

	};

	grid->getTexture()->setTexParameters(params);
	grid->setAnchorPoint(Vec2::ZERO);
	grid->setPosition(Vec2::ZERO);

	scene->addChild(grid);
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void AppDelegate::init(HWND uWind, int32_t nWidth, int32_t nHeight)
{
	m_uWnd = uWind;

	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
     if(!glview) {
         glview = MFCGLView::create(uWind);
         director->setOpenGLView(glview);
     }
	 if (!applicationDidFinishLaunching())
	{
	    return;
	}
	 cocosInited = true;
}

int AppDelegate::run()
{
	if (!m_uWnd)
		return Application::run();
	else
	{
		if (cocosInited)
			Director::getInstance()->mainLoop();
		return 1;
	}
}

void AppDelegate::onSize(int nWidth, int nHeight)
{
	auto glview = Director::getInstance()->getOpenGLView();
	if (glview)
	{
		if (cocosInited)
		{
			glview->setFrameSize(nWidth, nHeight);
		}
	}
}

void AppDelegate::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	auto glview = (MFCGLView*)Director::getInstance()->getOpenGLView();
	if (glview)
	{
		if (cocosInited)
		{
			glview->WindowProc(message, wParam, lParam);
		}
	}
}
