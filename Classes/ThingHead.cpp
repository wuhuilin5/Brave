#include "ThingHead.h"
#include "Progress.h"

ThingHead::ThingHead()
: _hpBar(nullptr)
{
}

ThingHead* ThingHead::create(const char* background)
{
	ThingHead* head = new ThingHead();
	if(head && head->initWithSpriteFrameName(background))
	{
		head->autorelease();
		return head;
	}
	CC_SAFE_DELETE(head);
	return nullptr;
}

void ThingHead::initHpBar(const char* background, const char* fillname)
{
	_hpBar = Progress::create(background, fillname);
	this->addChild(_hpBar);
}

void ThingHead::initName(const std::string name)
{
}
