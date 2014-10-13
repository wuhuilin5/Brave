#include "ThingManager.h"
#include "Player.h"
#include "Creature.h"

ThingManager* ThingManager::_instance = nullptr;

ThingManager::ThingManager()
{
}

ThingManager::~ThingManager()
{
}

ThingManager* ThingManager::getInstance()
{
	if(_instance == nullptr)
	{
		_instance = new ThingManager();
	}

	return _instance;
}

Thing* ThingManager::createThing(ThingType type)
{
	Thing* thing = nullptr;
	switch (type)
	{
	case PLAYER:
		thing = Player::create();
		break;
	case ENEMY:
		thing = Creature::create();
		break;
	case NPC:
		break;
	case CREATURE:
		thing = Creature::create();
		break;
	default:
		break;
	}

	return thing;
}