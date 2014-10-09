#ifndef __THING_MANAGER_H__
#define __THING_MANAGER_H__

#include "cocos2d.h"
#include "Thing.h"

class ThingManager : public cocos2d::Ref
{
public:
	ThingManager();
	~ThingManager();

	static ThingManager* getInstance();

	Thing* createThing(ThingType type);
	
private:
	static ThingManager* _instance;
};

#endif