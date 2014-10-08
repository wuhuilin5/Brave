#include "Player.h"
#include "FSM.h"
#include "ThingStatus.h"

Player::Player()
: _seq(nullptr)
, _speed(100.0f)
{

}

bool Player::initWithThingType(ThingType type)
{
	std::string spName = "";
	_type = type;
	int animationFrameNum[5] = {4, 4, 4, 2, 4};
	int animationFrameNum2[5] = {3, 3, 3, 2, 0};

	switch( type )
	{
		case ThingType::PLAYER:
			spName = "player1-1-1.png";
			_name = "player1";
			_animationNum = 5;
			_animationFrameNum.assign(animationFrameNum,animationFrameNum + 5);
			break;
		case ThingType::ENEMY1:
			spName = "enemy1-1-1.png";
			_name = "enemy1";
			_animationNum = 4;
			_animationFrameNum.assign(animationFrameNum2,animationFrameNum2 + 5);
			break;
		case ThingType::ENEMY2:
			spName = "enemy2-1-1.png";
			_name = "enemy2";
			_animationNum = 4;
			_animationFrameNum.assign(animationFrameNum2,animationFrameNum2 + 5);
			break;
	}

	this->initWithSpriteFrameName(spName);

	std::string animationNames[5]= {"walk", "attack", "dead", "hit", "skill"};
	_animationNames.assign(animationNames, animationNames + 5 );

	this->addAnimations();

	return true;
}

Player* Player::create(ThingType type )
{
	Player* player = new Player();
	if(player && player->initWithThingType(type))
	{
		player->autorelease();
		return player;
	}
	else
	{
		delete player;
		player = nullptr;
		return nullptr;
	}
}

void Player::addAnimations()
{
	const std::string animationName = String::createWithFormat("%s-%s", _name.c_str(),_animationNames[0])->getCString();
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	if(animation)
		return;

	for(int i=0; i < _animationNum; i++ )
	{
		auto animation = Animation::create();
		animation->setDelayPerUnit(0.2f);

		for( int j=0; j < _animationFrameNum[i]; j++ )
		{
			auto sfName = String::createWithFormat("%s-%d-%d.png", _name.c_str(), i+1, j+1)->getCString();
			animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(sfName));
		}

		//put the animation into cache
		const std::string animName = String::createWithFormat("%s-%s", _name.c_str(), _animationNames[i])->getCString();
		AnimationCache::getInstance()->addAnimation(animation, animName);
	}
}

void Player::playAnimationForever(int index)
{
	if(index < 0 || index >= _animationNum)	
	{
		log("illegal animation index!");
		return;
	}

	auto animName = String::createWithFormat("%s-%s", _name.c_str(), _animationNames[index])->getCString();
	auto animation = AnimationCache::getInstance()->getAnimation(animName);
	auto animate = Animate::create(animation);
	this->runAction(RepeatForever::create(animate));
}

void Player::walkTo(Vec2 dest)
{
	this->stopAllActions();
	/*if(_seq)
		this->stopAction(_seq);
*/
	auto currPos = this->getPosition();
	this->setFlippedX(currPos.x > dest.x ? true : false );
	
	auto diff = dest - currPos;
	auto time = diff.length()/_speed;
	auto move = MoveTo::create(time, dest);

	//lambda function
	auto func = [&]()  //void()
	{
		this->stopAllActions();
		_seq = nullptr;
	};

	auto callback = CallFunc::create(func);
	_seq = Sequence::create(move, callback, nullptr);

	this->runAction(_seq);
	this->playAnimationForever(0);
}

void Player::initFSM()
{
	_fsm = FSM::create(ThingStatus::IDLE);

}