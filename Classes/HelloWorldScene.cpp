#include "HelloWorldScene.h"

static TestInstance * s_pTestInstance = nullptr;

TestInstance * TestInstance::getInstance()
{
	if (!s_pTestInstance)
		s_pTestInstance = new TestInstance();
	return s_pTestInstance;
}

TestInstance::TestInstance()
{

}

void TestInstance::setCurrentSelectClassName(const std::string &str)
{
	auto scene = Director::getInstance()->getRunningScene();
	if (!scene)
		return;
	Label *tf = (Label*)scene->getChildByName("className");
	if (!tf)
	{
		tf = Label::createWithSystemFont("", "", 24);
		scene->addChild(tf, 10, "className");
		
	}
	tf->setPosition(Vec2(scene->getContentSize().width / 2, scene->getContentSize().height / 2));
	tf->setString(str);
}





