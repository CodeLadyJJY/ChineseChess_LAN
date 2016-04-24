#include "SettingScene.h"
#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;
using namespace std;
using namespace cocostudio::timeline;

Scene* SettingScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = SettingScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool SettingScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("SettingScene.csb");
	addChild(rootNode);

	CheckBox *checkbox_host = (CheckBox*)rootNode->getChildByTag(1);
	CheckBox *checkbox_client = (CheckBox*)rootNode->getChildByTag(2);
	TextField *textfield_ip = (TextField*)rootNode->getChildByTag(3);
	TextField *textfield_port = (TextField*)rootNode->getChildByTag(4);
	Button *button_ok = (Button*)rootNode->getChildByTag(5);
	Text *text_status = (Text*)rootNode->getChildByTag(10);

	// 如有保存设置，则载入设置
	string filepath = UserDefault::getInstance()->getXMLFilePath();
	bool is_set = UserDefault::getInstance()->getBoolForKey("IsSet");
	if (is_set)
	{
		is_host = UserDefault::getInstance()->getBoolForKey("IsHost");
		ip = UserDefault::getInstance()->getStringForKey("IP");
		port = UserDefault::getInstance()->getStringForKey("Port");

		if (is_host)
		{
			checkbox_host->setSelectedState(true);
			checkbox_client->setSelectedState(false);
		}
		else
		{
			checkbox_host->setSelectedState(false);
			checkbox_client->setSelectedState(true);
		}

		textfield_ip->setString(ip);
		textfield_port->setString(port);
	}
	else
	{
		// 初始化选中主机选项
		is_host = true;
		checkbox_host->setSelectedState(true);
		checkbox_client->setSelectedState(false);
		textfield_ip->setString("127.0.0.1");
		textfield_ip->setEnabled(false);
	}


	// 主机选项触摸监听
	checkbox_host->addTouchEventListener([=](Ref *pSender, Widget::TouchEventType type) {
		switch (type)
		{
		case Widget::TouchEventType::BEGAN:
			is_host = true;
			textfield_ip->setString("127.0.0.1");
			textfield_ip->setEnabled(false);
		case Widget::TouchEventType::ENDED:
			checkbox_client->setSelectedState(false);
			break;
		default:
			break;
		}
	});

	// 客户机选项触摸监听
	checkbox_client->addTouchEventListener([=](Ref *pSender, Widget::TouchEventType type) {
		switch (type)
		{
		case Widget::TouchEventType::BEGAN:
			is_host = false;
			textfield_ip->setEnabled(true);
			textfield_ip->setString("");
		case Widget::TouchEventType::ENDED:
			checkbox_host->setSelectedState(false);
			break;
		default:
			break;
		}
	});

	// 确认按钮触摸监听
	button_ok->addTouchEventListener([=](Ref *pSender, Widget::TouchEventType type) {
		switch (type)
		{
		case Widget::TouchEventType::BEGAN:
			isInfoValid = true;

			// 检查ip
			ip = textfield_ip->getStringValue();

			if (ip.size() > 0)
			{
				if (!isIpValid())
				{
					text_status->setString("please input correct ip and port");
					isInfoValid = false;
				}
			}
			else
			{
				text_status->setString("please input ip and port");
				isInfoValid = false;
			}

			// 检查端口
			port = textfield_port->getStringValue();

			if (port.size() > 0)
			{
				if (!isPortValid())
				{
					text_status->setString("please input correct ip and port");
					isInfoValid = false;
				}
			}
			else
			{
				text_status->setString("please input ip and port");
				isInfoValid = false;
			}
			break;
		case Widget::TouchEventType::ENDED:
			// 信息全部合法则保存,跳转到游戏界面
			if (isInfoValid)
			{
				saveInfo();
				jumpToGame();
			}
			break;
		default:
			break;
		}
	});

	return true;
}

// 检查ip合法性
bool SettingScene::isIpValid()
{
	string temp;
	int count = 0;
	int j = 0;

	for (int i = 0; i < ip.length(); ++i)
	{
		if (ip.at(i) >= '0' && ip.at(i) <= '9')
		{
			temp[j++] = ip[i];
		}
		else if (ip.at(i) == '.')
		{
			count++;
			if (count >= 4)
				return false;
			if (atoi(temp.c_str()) < 0 || atoi(temp.c_str()) > 255)
				return false;
			temp = "";
			j = 0;
		}
		else
			return false;
	}

	if (count < 3)
		return false;
	if (atoi(temp.c_str()) < 0 || atoi(temp.c_str()) > 255)
		return false;

	return true;
}

// 检查端口合法性
bool SettingScene::isPortValid()
{
	// 检查端口是否都是数字
	for (int i = 0; i < port.length(); ++i)
		if (!(port.at(i) >= '0' && port.at(i) <= '9'))
			return false;

	// 检查数字是否在正确的范围内
	if (atoi(port.c_str()) < 0 || atoi(port.c_str()) > 65535)
		return false;

	return true;
}

// 保存设置信息，以备下次使用
void SettingScene::saveInfo()
{
	UserDefault::getInstance()->setBoolForKey("IsSet", true);
	UserDefault::getInstance()->setBoolForKey("IsHost", is_host);
	UserDefault::getInstance()->setStringForKey("IP", ip);
	UserDefault::getInstance()->setStringForKey("Port", port);
	UserDefault::getInstance()->flush();
	string filepath = UserDefault::getInstance()->getXMLFilePath();
	log(filepath.c_str());
}

// 跳转到游戏界面
void SettingScene::jumpToGame()
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}