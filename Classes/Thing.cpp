#include "Thing.h"
#include "FSM.h"
#include "ThingStatus.h"

std::unordered_map<AnimationType, std::string> Thing::_animationNames;

Thing::Thing(ThingType type)
: _type(type)
, _speed(100.0f)
{
}

Thing* Thing::create(ThingType type)
{
	Thing* thing = new Thing(type);
	if(thing && thing->init())
	{
		thing->autorelease();
		return thing;
	}
	CC_SAFE_DELETE(thing);
	return nullptr;
}

bool Thing::init()
{
	this->initAnimationInfos();
	this->initFSM();
	this->addAnimations();

	std::string spName = _name + "-1-1.png";
	return this->initWithSpriteFrameName(spName);
}

void Thing::initAnimationInfos()
{
	if(_animationNames.size() == 0)
	{
		_animationNames[AnimationType::WALK] = "walk";
		_animationNames[AnimationType::DIE] = "dead";
		_animationNames[AnimationType::ATTACK] = "attack";
		_animationNames[AnimationType::ATTACKED] = "hit";
		_animationNames[AnimationType::SKILL] = "skill";
	}

	_animations.insert(AnimationType::WALK);
	_animations.insert(AnimationType::ATTACK);
	_animations.insert(AnimationType::DIE);
	_animations.insert(AnimationType::ATTACKED);
}

void Thing::addAnimations()
{
	const std::string animationName = this->getAnimationNameByType(AnimationType::IDLE);
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	if(animation)
		return;

	int i = 0;
	for( auto iter = _animations.begin(); iter != _animations.end(); iter++, i++)
	{
		auto animation = Animation::create();
		animation->setDelayPerUnit(0.2f);

		for( int j=0; j < _animationFrameNum[i]; j++ )
		{
			auto sfName = String::createWithFormat("%s-%d-%d.png", _name.c_str(), i+1, j+1)->getCString();
			animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(sfName));
		}

		//put the animation into cache
		const std::string animName = this->getAnimationNameByType(*iter);
		AnimationCache::getInstance()->addAnimation(animation, animName);
	}
}

void Thing::playAnimationForever(AnimationType type)
{
	auto animate = this->getAnimateByType(type);
	if(animate != nullptr)
	{
		this->runAction(RepeatForever::create(animate));
	}
}

Animate* Thing::getAnimateByType(AnimationType type)
{
	if(_animationNames.find(type) == _animationNames.end())
	{
		log("illegal animation type!");
		return nullptr;
	}

	auto animName = this->getAnimationNameByType(type);
	auto animation = AnimationCache::getInstance()->getAnimation(animName);
	auto animate = Animate::create(animation);
	animate->setTag(static_cast<int>(type));

	return animate;
}

const char* Thing::getAnimationNameByType(AnimationType type)
{
	return String::createWithFormat("%s-%s", _name.c_str(), _animationNames[type].c_str())->getCString();
}

void Thing::walkTo(Vec2 dest)
{
	_fsm->setOnEnter(ThingStatus::WALK, CC_CALLBACK_0(Thing::onWalk, this, dest));
	_fsm->doAnimation(AnimationType::WALK);
}

void Thing::initFSM()
{
	_fsm = FSM::create(ThingStatus::IDLE);
	_fsm->retain();

	_fsm->setOnEnter(ThingStatus::IDLE, CC_CALLBACK_0(Thing::onIdle, this));
	_fsm->setOnEnter(ThingStatus::ATTACK, CC_CALLBACK_0(Thing::onAttack, this));
	_fsm->setOnEnter(ThingStatus::ATTACKED, CC_CALLBACK_0(Thing::onAttacked, this));
	_fsm->setOnEnter(ThingStatus::DEAD, CC_CALLBACK_0(Thing::onDie, this));
}

void Thing::onIdle()
{
	cocos2d::log("onIdle: Enter Idle");
	this->stopAllActions();

	auto sfname = String::createWithFormat("%s-1-1.png", _name.c_str())->getCString();
	auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(sfname);
	this->setSpriteFrame(spriteFrame);
}

void Thing::onWalk(Vec2 dest)
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
		this->_fsm->doAnimation(AnimationType::STOP);
	};

	auto callback = CallFunc::create(func);
	auto seq = Sequence::create(move, callback, nullptr);

	this->runAction(seq);
	this->playAnimationForever(AnimationType::WALK);
}

void Thing::onAttack()
{
	cocos2d::log("onAttack: Enter attack");
	auto animate = this->getAnimateByType(AnimationType::ATTACK);
	auto func = [&]()
	{
		this->_fsm->doAnimation(AnimationType::STOP);
		
	};

	auto callback = CCCallFunc::create(func);
	auto seq = Sequence::create(animate, callback, nullptr);
	this->runAction(seq);
}

void Thing::onAttacked()
{
	cocos2d::log("onAttacked: Enter attacked");
	auto animate = this->getAnimateByType(AnimationType::ATTACKED);
	auto func = [&]()
	{
		this->_fsm->doAnimation(AnimationType::STOP);
	};

	auto wait = DelayTime::create(0.6f);
	auto callback = CCCallFunc::create(func);
	auto seq = Sequence::create(wait, animate, callback, nullptr);
	this->runAction(seq);
}

void Thing::onDie()
{
	cocos2d::log("onDie: Enter die");
	auto animate = this->getAnimateByType(AnimationType::DIE);
	auto func = [&]()
	{
		if(_type != ThingType::PLAYER)
		{
			//NotificationCenter::getInstance()->postNotification("emenyDead", this);
			_eventDispatcher->dispatchCustomEvent( "emenyDead", this);
			this->removeAllChildrenWithCleanup(true);
		}
	};

	auto blink = Blink::create(3, 5);
	auto callback = CCCallFunc::create(func);
	auto seq = Sequence::create(animate, blink, callback, nullptr);
	this->runAction(seq);
}

ThingType Thing::getType()
{
	return _type;
}

void Thing::onExit()
{
	Sprite::onExit();
	_fsm->release();
	//_eventDispatcher->removeEventListener();
}