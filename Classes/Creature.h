#ifndef __CREATURE_H__
#define __CREATURE_H__

#include "Thing.h"

class Creature : public Thing
{
public:
	Creature();
	static Creature* create();

protected:
	virtual bool init() override;
	virtual void initHead() override;

private:

};

#endif
