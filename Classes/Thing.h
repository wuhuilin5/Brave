#ifndef __THING_H__
#define __THING_H__

#include "cocos2d.h"
#include "AnimationType.h"

USING_NS_CC;

class FSM;
class ThingHead;

enum ThingType
{
	PLAYER,
	ENEMY,
	NPC,
	CREATURE
};

class Thing : public Sprite
{
public:
	
	Thing(ThingType type);

	static Thing* create(ThingType type);

	void playAnimationForever(AnimationType type);

	void walkTo(Vec2 dest);

	ThingType getType();

	Animate* getAnimateByType(AnimationType type);

	const char* getAnimationNameByType(AnimationType type);

	const float getSpeed(){ return _speed; }
	void setSpeed( const float speed ) { _speed = speed; }

	virtual void onExit() override;

protected:
	void addAnimations();
	
	virtual void onIdle();
	virtual void onWalk(Vec2 dest);
	virtual void onAttack();
	virtual void onAttacked();
	virtual void onDie();
	
	virtual bool init() override;
	virtual void initAnimationInfos();
	virtual void initHead(){}

	void initFSM();

protected:
	ThingType _type;
	std::string _name;
	float _speed;
	FSM* _fsm;
	ThingHead* _head;

	std::set<AnimationType> _animations;
	std::vector<int> _animationFrameNum;
	static std::unordered_map<AnimationType, std::string> _animationNames;
};

#endif