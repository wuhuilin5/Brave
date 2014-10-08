#include "MainScene.h"
#include "Player.h"
#include "FSM.h"
#include "ThingStatus.h"

USING_NS_CC;

Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	this->setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_COLOR));

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite *background = Sprite::create("image/background.png");
	background->setPosition(origin + visibleSize/2);
	this->addChild(background);

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/role.plist", "image/role.pvr.ccz");

	_player = Player::create(ThingType::PLAYER);
	_player->setPosition(origin.x + _player->getContentSize().width/2, origin.y + visibleSize.height/2);
	this->addChild(_player);

	_enemy1 = Player::create(ThingType::ENEMY1);
	_enemy1->setPosition(origin.x + visibleSize.width - _enemy1->getContentSize().width/2, origin.y + visibleSize.height/2);
	this->addChild(_enemy1);

	_player->playAnimationForever(1);
	_enemy1->playAnimationForever(1);

	_listener_touch = EventListenerTouchOneByOne::create();
	_listener_touch->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan, this );
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener_touch, this);

	auto fsm = FSM::create(ThingStatus::IDLE,[](){cocos2d::log("Enter idle");});

    return true;
}

void MainScene::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	_customCommand.init(_globalZOrder);
	_customCommand.func = CC_CALLBACK_0(MainScene::onDraw, this, transform, flags);
	renderer->addCommand(&_customCommand);
}

void MainScene::onDraw(const cocos2d::Mat4 &transform, bool transformUpdate)
{
	auto director = Director::getInstance();
	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);

	CHECK_GL_ERROR_DEBUG();

	DrawPrimitives::setDrawColor4B(255, 0, 0, 128);
	glLineWidth(2);

	Vec2 vertices[] = {Vec2(100, 100), Vec2(300, 100), Vec2(300, 300), Vec2(100, 300)};
	DrawPrimitives::drawPoly(vertices, 4, true);

	CHECK_GL_ERROR_DEBUG();

	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

	/*auto glProgram = getGLProgram();
	glProgram->use();
	glProgram->setUniformsForBuiltins();

	auto size = Director::getInstance()->getWinSize();
	float vertices[] = {0, 0, 
		size.width, 0, 
		size.width/2, size.height/2};

	float colors[] = {0, 1, 0, 1,
		1, 0, 0, 1,
		0, 0, 1, 1};

	GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR);
	glVertexAttribPointer(GL::VERTEX_ATTRIB_FLAG_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glVertexAttribPointer(GL::VERTEX_ATTRIB_FLAG_COLOR, 4, GL_FLOAT, GL_FALSE,0, colors);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 3);

	CHECK_GL_ERROR_DEBUG();*/
}

bool MainScene::onTouchBegan(Touch* touch, Event* event)
{
	Vec2 pos = this->convertToNodeSpace(touch->getLocation());
	_player->walkTo(pos);

	return true;
}