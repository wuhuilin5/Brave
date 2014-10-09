#include "Progress.h"

Progress* Progress::create(const char* background, const char* fillname)
{
	Progress* progress = new Progress();
	if(progress && progress->init(background, fillname))
	{
		progress->autorelease();
		return progress;
	}
	CC_SAFE_DELETE(progress);
	return nullptr;
}

bool Progress::init(const char* background, const char* fillname)
{
	this->initWithSpriteFrameName(background);
	_fill = ProgressTimer::create(Sprite::createWithSpriteFrameName(fillname));
	this->addChild(_fill);

	_fill->setType(ProgressTimer::Type::BAR);
	_fill->setMidpoint(Point(0,0.5));
	_fill->setBarChangeRate(Point(1.0,0));
	_fill->setPosition(this->getContentSize()/2);
	_fill->setPercentage(50);

	return true;
}