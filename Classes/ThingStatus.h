#ifndef __THING_STATUS__
#define __THING_STATUS__

#include <string>

class ThingStatus
{
public:
	static const std::string IDLE;				//idle×´Ì¬
	static const std::string WALK;			    //ÐÐ×ß×´Ì¬
	static const std::string ATTACK;			//¹¥»÷×´Ì¬
	static const std::string DEAD;				//ËÀÍö
	static const std::string ATTACKED;          //±»¹¥»÷
};

#endif