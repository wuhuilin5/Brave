#include "Player.h"

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

	return Thing::init();
}

void Player::initAnimationInfos()
{
	Thing::initAnimationInfos();
	_animations.insert(AnimationType::SKILL);
}