#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Thing.h"

class Player : public Thing
{
public:
	Player();
	static Player* create();

protected:
	virtual bool init() override;
	virtual void initAnimationInfos() override;

private:

};

#endif