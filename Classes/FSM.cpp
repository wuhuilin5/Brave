#include "FSM.h"
#include "ThingStatus.h"

//std::set<std::string> FSM::_states;
//std::unordered_map<std::string, std::function<void()>> FSM::_onEnters;
//std::unordered_map<AnimationType, std::unordered_map<std::string, std::string>> FSM::_animations;

 FSM:: FSM(std::string state, std::function<void()> onEnter)
{
	_currentState = state;
	_previousState = state;

	this->addState(state, onEnter);
}

FSM* FSM::create(std::string state, std::function<void()> onEnter)
{
	FSM* fsm = new FSM(state, onEnter);
	if(fsm && fsm->init())
	{
		fsm->autorelease();
		return fsm;
	}
	else
	{
		CC_SAFE_DELETE(fsm);
		return nullptr;
	}
}

bool FSM::init()
{
	addState(ThingStatus::WALK,[](){cocos2d::log("Enter walk");});
	addState(ThingStatus::ATTACK,[](){cocos2d::log("Enter attack");});
	addState(ThingStatus::DEAD,[](){cocos2d::log("Enter dead");});
	addState(ThingStatus::ATTACKED,[](){cocos2d::log("Enter ATTACKED");});

	if(_animations.size() == 0)
	{
		addAnimation(AnimationType::WALK,ThingStatus::IDLE,ThingStatus::WALK);
		addAnimation(AnimationType::WALK,ThingStatus::ATTACK,ThingStatus::WALK);
		addAnimation(AnimationType::WALK,ThingStatus::WALK,ThingStatus::WALK);

		addAnimation(AnimationType::ATTACK,ThingStatus::IDLE,ThingStatus::ATTACK);
		addAnimation(AnimationType::ATTACK,ThingStatus::WALK, ThingStatus::ATTACK);
		
		addAnimation(AnimationType::ATTACKED,ThingStatus::IDLE,ThingStatus::ATTACKED);
		addAnimation(AnimationType::ATTACKED,ThingStatus::WALK,ThingStatus::ATTACKED);
		addAnimation(AnimationType::ATTACKED,ThingStatus::ATTACK,ThingStatus::ATTACKED); //can ATTACK be stoped by beHit?

		addAnimation(AnimationType::DIE,ThingStatus::IDLE,ThingStatus::DEAD);
		addAnimation(AnimationType::DIE,ThingStatus::WALK,ThingStatus::DEAD);
		addAnimation(AnimationType::DIE,ThingStatus::ATTACK,ThingStatus::DEAD);
		addAnimation(AnimationType::DIE,ThingStatus::ATTACKED,ThingStatus::DEAD);

		addAnimation(AnimationType::STOP,ThingStatus::WALK,ThingStatus::IDLE);
		addAnimation(AnimationType::STOP,ThingStatus::ATTACK,ThingStatus::IDLE);
		addAnimation(AnimationType::STOP,ThingStatus::ATTACKED,ThingStatus::IDLE);
		addAnimation(AnimationType::STOP,ThingStatus::IDLE,ThingStatus::IDLE);
	}

	 //this->doAnimation(AnimationType::WALK);     
	 //this->doAnimation(AnimationType::ATTACK);    
	 //this->doAnimation(AnimationType::NONE);     
	 //this->doAnimation(AnimationType::STOP);     
	 //this->doAnimation(AnimationType::DIE);     
	 //this->doAnimation(AnimationType::WALK);

	return true;
}

void FSM::addState(std::string state, std::function<void()> onEnter)
{
	if(state == "")
	{
		cocos2d::log("FSM::addState: state cann't be empty string!");
		return;
	}
	_states.insert(state);
	//_onEnters.insert(std::pair<std::string, std::function<void()>>(state, onEnter));
	_onEnters[state] = onEnter;
}

bool FSM::isContainState(std::string stateName)
{
	return _states.find(stateName) != _states.end();
}

void FSM::printState()
{
	cocos2d::log("FSM::printState, list of states");
	for(auto iter = _states.begin(); iter != _states.end(); iter++ )
	{
		cocos2d::log(iter->c_str());
	}
}

void FSM::changeToState(std::string state)
{
	if(isContainState(state))
	{
		_previousState = _currentState;
		_currentState = state;
		cocos2d::log("FSM::changeToState: %s -> %s", _previousState.c_str(), _currentState.c_str());

		if(_onEnters[state])
			_onEnters[state]();
	}
	else
	{
		cocos2d::log("FSM::changeToState: on such state as %s, state unchanged", state.c_str());
	}
}

void FSM::addAnimation(AnimationType type, std::string from, std::string to)
{
	if(type == AnimationType::NONE)
	{
		cocos2d::log("FSM::addAnimation: event cann't be none animation type!");
		return;
	}

	if(!isContainState(from))
	{
		cocos2d::log("FSM::addAnimation: from state %s does not exit!", from.c_str());
		return;
	}

	if(!isContainState(to))
	{
		cocos2d::log("FSM::addAnimation: to state %s does not exit!", to.c_str());
		return;
	}

	std::unordered_map<std::string, std::string>& onEvent = _animations[type];
	onEvent[from] = to;
}

bool FSM::candoAnimation(AnimationType type)
{
	return _animations[type].find(_currentState) != _animations[type].end();
}

void FSM::doAnimation(AnimationType type)
{
	if(candoAnimation(type))
	{
		cocos2d::log("FSM::doAnimation: doing event %d", static_cast<int>(type));
		this->changeToState(_animations[type][_currentState]);
	}
	else
	{
		cocos2d::log("FSM::doAnimation: cann't do event %d", static_cast<int>(type));
	}
}

void FSM::setOnEnter(std::string state, std::function<void()> onEnter)
{
	if(isContainState(state))
	{
		_onEnters[state] = onEnter;
	}
	else
	{
		cocos2d::log("FSM::setOnEnter: on state named %s!", state.c_str());
	}
}