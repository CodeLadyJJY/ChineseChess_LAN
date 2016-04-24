#include "LoadingScene.h"
#include "SettingScene.h"

USING_NS_CC;

Scene* LoadingScene::createScene()
{
	auto scene = Scene::create();
	auto layer = LoadingScene::create();
	scene->addChild(layer);
	return scene;
}

bool LoadingScene::init()
{
	if (!Layer::init())
		return false;

	auto size = Director::getInstance()->getWinSize();

	TTFConfig config("fonts/Marker Felt.ttf", 80);

	//游戏名称
	auto GameName = Label::createWithTTF(config, "Chinese Chess");
	GameName->setColor(Color3B::WHITE);
	GameName->setPosition(Point(size.width / 2, size.height * 3 / 5));
	this->addChild(GameName);

	//作者
	auto author = Label::createWithTTF(config, "Game By CodeLadyJJY");
	author->setColor(Color3B::WHITE);
	author->setScale(0.5);
	author->setPosition(Point(size.width / 2, size.height / 3));
	this->addChild(author);
	
	return true;
}

void LoadingScene::onEnter()
{
	//异步加载图片
	Director::getInstance()->getTextureCache()->addImageAsync("chinesechess.png", CC_CALLBACK_1(LoadingScene::jumpToGame, this));
}

void LoadingScene::jumpToGame(Texture2D *texture)
{
	//预加载帧缓存纹理
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("chinesechess.plist", texture);

	//场景跳转
	auto scene = SettingScene::createScene();
	TransitionScene *transition = TransitionFade::create(2, scene);
	Director::getInstance()->replaceScene(transition);
}