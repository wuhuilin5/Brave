#ifndef __PROGRESS_H__
#define __PROGRESS_H__

#include "cocos2d.h"
USING_NS_CC;

class Progress : public Sprite
{
public:
	bool init(const char* background, const char* filename);

	/*
	the inputs are SpriteFrame names.
	them should be loaded into SpriteFrameCache before calling this.
	*/
	static Progress* create(const char* background, const char* fillname);

	void setFill(ProgressTimer* fill) { _fill =  fill; }

	void setProgress(float percentage){ _fill->setPercentage(percentage);}

private:
	ProgressTimer* _fill;
};
#endif