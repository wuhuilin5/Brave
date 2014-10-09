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
	switch (type)
	{
	case PLAYER:
		return Player::create();
		break;
	case ENEMY:
		return Creature::create();
		break;
	case NPC:
		break;
	case CREATURE:
		return Creature::create();
		break;
	default:
		break;
	}

	return nullptr;
}