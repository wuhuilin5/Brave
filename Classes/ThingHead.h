#ifndef __THING_HEAD_H__
#define __THING_HEAD_H__

#include "cocos2d.h"
USING_NS_CC;

class Progress;

class ThingHead : public Sprite
{
public:
	ThingHead();

	static ThingHead* create();
	static ThingHead* create(const char* spriteFrameName);
	
	//virtual bool init() override;

	void initName(const std::string name);
	void initHpBar(const char* backgroundSpriteFrameName, const char* fillSpriteFrameName);

private:
	Progress* _hpBar;
};

#endif