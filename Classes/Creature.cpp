#include "Creature.h"
#include "cocos2d.h"
#include "ThingHead.h"

Creature::Creature()
:Thing(ThingType::CREATURE)
{
}

Creature* Creature::create()
{
	Creature* creature = new(std::nothrow) Creature();
	if(creature && creature->init())
	{
		return creature;
	}
	CC_SAFE_DELETE(creature);
	return nullptr;
}

bool Creature::init()
{
	_name = "enemy1";
	int animationFrameNum[5] = {3, 3, 3, 2, 0};
	_animationFrameNum.assign(animationFrameNum, animationFrameNum + 5 );

	if(!Thing::init())
		return false;

	this->initHead();
	return true;
}

void Creature::initHead()
{
	_head = ThingHead::create();
	this->addChild(_head);

	_head->initHpBar("small-enemy-progress-bg.png", "small-enemy-progress-fill.png");
	_head->setPosition(this->getContentSize().width/2, this->getContentSize().height);
}