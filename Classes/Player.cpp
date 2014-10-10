#include "Player.h"
#include "ThingHead.h"

Player::Player()
:Thing(ThingType::PLAYER)
{
}

Player* Player::create()
{
	Player* player = new(std::nothrow) Player();
	if(player && player->init())
	{
		player->autorelease();
		return player;
	}
	CC_SAFE_DELETE(player);
	return nullptr;
}

bool Player::init()
{
	_name = "player1";
	int animationFrameNum[5] = {4, 4, 4, 2, 4};
	_animationFrameNum.assign(animationFrameNum, animationFrameNum + 5 );

	if(!Thing::init())
		return false;

	this->initHead();
	return true;
}

void Player::initAnimationInfos()
{
	Thing::initAnimationInfos();
	_animations.insert(AnimationType::SKILL);
}

void Player::initHead()
{
	_head = ThingHead::create();
	this->addChild(_head);

	_head->initHpBar("small-enemy-progress-bg.png", "small-enemy-progress-fill.png");
	_head->setPosition(this->getContentSize().width/2, this->getContentSize().height);
}