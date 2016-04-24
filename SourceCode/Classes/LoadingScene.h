#ifndef __LOADING_SCENE_H__
#define __LOADING_SCENE_H__

#include"cocos2d.h"

class LoadingScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene();
	virtual bool init();
	CREATE_FUNC(LoadingScene);
	virtual void onEnter();

private:
	void jumpToGame(cocos2d::Texture2D *texture);	//³¡¾°Ìø×ªº¯Êý
};

#endif