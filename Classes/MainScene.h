#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class Thing;
class Progress;

class MainScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);

	virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
	
	virtual bool onTouchBegan(Touch* touch, Event* event) override;

protected:
	void onDraw(const cocos2d::Mat4 &transform, bool transformUpdate);
	CustomCommand _customCommand;

private:
	EventListenerTouchOneByOne* _listener_touch;

	Thing* _player;
	Thing* _enemy1;

	Progress* _progress;
};

#endif // __MainScene_SCENE_H__