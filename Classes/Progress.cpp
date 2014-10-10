#include "Progress.h"

Progress* Progress::create(const char* backgroundSpriteFrameName, const char* fillSpriteFrameName)
{
	Progress* progress = new Progress();
	if(progress && progress->init(backgroundSpriteFrameName, fillSpriteFrameName))
	{
		progress->autorelease();
		return progress;
	}
	CC_SAFE_DELETE(progress);
	return nullptr;
}

bool Progress::init(const char* backgroundSpriteFrameName, const char* fillSpriteFrameName)
{
	this->initWithSpriteFrameName(backgroundSpriteFrameName);
	_fill = ProgressTimer::create(Sprite::createWithSpriteFrameName(fillSpriteFrameName));
	this->addChild(_fill);

	_fill->setType(ProgressTimer::Type::BAR);
	_fill->setMidpoint(Point(0,0.5));
	_fill->setBarChangeRate(Point(1.0,0));
	_fill->setPosition(this->getContentSize()/2);
	_fill->setPercentage(100);

	return true;
}