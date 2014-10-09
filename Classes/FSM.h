#ifndef __FSM_H__
#define __FSM_H__

#include "cocos2d.h"
#include "AnimationType.h"

class FSM :public cocos2d::Ref
{
public:
	bool init();

	//Create FSM with a initial state name and optional callback function
	static FSM* create(std::string state, std::function<void()> onEnter = nullptr);

	FSM(std::string state, std::function<void()> onEnter = nullptr);

	//add state into FSM
	void addState(std::string state, std::function<void()> onEnter = nullptr);

	//add Event into FSM
	void addAnimation(AnimationType type, std::string from, std::string to);

	//Check if the state if already in FSM
	bool isContainState(std::string stateName);

	//print a list of states.
	void printState();

	//do the event
	void doAnimation(AnimationType type);

	//check if the event can change state.
	bool candoAnimation(AnimationType type);

	//set the onEnter callback for a specified state
	void setOnEnter(std::string state, std::function<void()> onEnter);

protected:
	//change state and run callback
	void changeToState(std::string state);

private:
	std::set<std::string> _states;
	std::unordered_map<std::string, std::function<void()>> _onEnters;

	std::unordered_map<AnimationType, std::unordered_map<std::string, std::string>> _animations;

	std::string _currentState;
	std::string _previousState;
};

#endif