#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"

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
	
	void playAnimationForever(int index);

	void walkTo(Vec2 dest);

	void initFSM();

private:
	void addAnimations();

private:
	ThingType _type;
	std::string _name;

	int _animationNum;
	std::vector<int> _animationFrameNum;
	std::vector<std::string> _animationNames;

	Sequence* _seq;
	float _speed;

	FSM* _fsm;

};

#endif