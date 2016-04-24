#ifndef __SETTING_SCENE_H__
#define __SETTING_SCENE_H__

#include "cocos2d.h"

class SettingScene : public cocos2d::Layer
{
public:
	bool is_host;
	std::string ip;
	std::string port;

	bool isInfoValid;	// 信息是否合法
	bool isIpValid();	// 检查ip合法性
	bool isPortValid();	// 检查端口合法性
	void saveInfo();	// 保存设置信息，以备下次使用
	void jumpToGame();	// 跳转到游戏界面

	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(SettingScene);
};

#endif // __SETTING_SCENE_H__