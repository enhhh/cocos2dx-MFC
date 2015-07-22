#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include <string>
#include "cocos2d.h"
USING_NS_CC;
class TestInstance
{
public:
	static TestInstance * getInstance();

	void setCurrentSelectClassName(const std::string &str);
protected:
	TestInstance();
};
#endif // !__HELLOWORLD_SCENE_H__
