#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class Player : public Sprite
{
public:
	enum PlayerType
	{
		PLAYER,
		ENEMY1,
		ENEMY2
	};

	Player();

	static Player* create(PlayerType type);

	bool initWithPlayerType(PlayerType type);
	
	void playAnimationForever(int index);

	void walkTo(Vec2 dest);

private:
	void addAnimations();

private:
	PlayerType _type;
	std::string _name;

	int _animationNum;
	std::vector<int> _animationFrameNum;
	std::vector<std::string> _animationNames;

	Sequence* _seq;
	float _speed;
};

#endif