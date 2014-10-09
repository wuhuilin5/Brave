#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "AnimationType.h"

USING_NS_CC;

class FSM;

enum ThingType
{
	PLAYER,
	ENEMY1,
	ENEMY2
};

class Player : public Sprite
{
public:
	
	Player();

	static Player* create(ThingType type);

	bool initWithThingType(ThingType type);
	
	void initAnimationInfos(int framenum[]);

	void playAnimationForever(AnimationType type);

	void walkTo(Vec2 dest);

	void initFSM();

	ThingType getType();

	Animate* getAnimateByType(AnimationType type);

	const char* getAnimationNameByType(AnimationType type);

private:
	void addAnimations();
	
	void onIdle();
	void onWalk(Vec2 dest);
	void onAttack();
	void onAttacked();
	void onDie();

private:
	ThingType _type;
	std::string _name;
	float _speed;
	FSM* _fsm;

	std::set<AnimationType> _animations;
	std::vector<int> _animationFrameNum;
	static std::unordered_map<AnimationType, std::string> _animationNames;
};

#endif