#include "ThingHead.h"
#include "Progress.h"

ThingHead::ThingHead()
: _hpBar(nullptr)
{
}

ThingHead* ThingHead::create()
{
	ThingHead* head = new ThingHead();
	if(head && head->init())
	{
		head->autorelease();
		return head;
	}
	CC_SAFE_DELETE(head);
	return nullptr;
}

ThingHead* ThingHead::create(const char* spriteFrameName)
{
	ThingHead* head = new ThingHead();
	if(head && head->initWithSpriteFrameName(spriteFrameName))
	{
		head->autorelease();
		return head;
	}
	CC_SAFE_DELETE(head);
	return nullptr;
}

void ThingHead::initHpBar(const char* backgroundSpriteFrameName, const char* fillSpriteFrameName)
{
	_hpBar = Progress::create(backgroundSpriteFrameName, fillSpriteFrameName);
	this->addChild(_hpBar);
}

void ThingHead::initName(const std::string name)
{
}
