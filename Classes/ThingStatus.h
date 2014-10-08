#ifndef __THING_STATUS__
#define __THING_STATUS__

#include <string>

class ThingStatus
{
public:
	static const std::string IDLE;				//idle״̬
	static const std::string WALK;			    //����״̬
	static const std::string ATTACK;			//����״̬
	static const std::string DEAD;				//����
	static const std::string ATTACKED;          //������
};

#endif