#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "define.h"
#include "Chessman.h"
#include "ODSocket.h"

USING_NS_CC;
using namespace std;

class GameScene : public Layer
{
public:
    static Scene* createScene();
    virtual bool init();
	CREATE_FUNC(GameScene);
	void menuRestartCallBack(Ref* pSender);
	void menuResignCallBack(Ref* pSender);

private:
	Size size;								// 窗口大小
	Sprite* selected[2];					// 选择图片, 0 是红色选择框，1 是蓝色选择框
	Sprite* curChessman[2];					// 提示当前下子方
	Node* board;							// 棋盘
	Label* status;							// 显示连接信息
	Label* status2;							// 显示棋局信息
	EventListenerTouchOneByOne* listener;	// 触摸监听
	void initUI();							// 初始化界面
	void initListener();					// 初始化监听
	void initChessman();					// 初始化棋子

	int map[10][9];							// 棋盘地图
	Chessman *allChessman[32];				// 所有棋子
	bool color;								// 玩家颜色，0 黑色，1 红色
	bool is_wait;							// 等待标志
	bool is_selected;						// 是否有选择棋子
	int is_resigned;						// 认输标志，0 表示双方无人认输，1 对方认输，2 己方认输
	bool is_gameStart;						// 游戏是否开始
	int red_king_id;						// 红方将ID
	int black_king_id;						// 黑方将ID
	ChessMove moveStep;						// 移动步骤

	ODSocket *sockServer;					// 服务器sock
	ODSocket *sockClient;					// 客户端sock
	Message msg;							// 消息
	list<Message*> messageQueue;			// 消息队列
	mutex messageQueueMutex;				// 消息锁

	void accept();							// 等待接受
	void send();							// 发送消息
	void receive();							// 接受消息
	void cleanMessage();					// 清理message

	void newChessman(int x, int y, int id, int angle = 0);	// 新建棋子
	void moveChessman();									// 移动棋子
	void captureChessman();									// 吃子
	bool isRedOrBlack(int x, int type);						// 判断一个棋子是红色还是黑色, 0判断红色, 1判断黑色
	bool isValidMove(int toX, int toY);						// 判断一个棋子的走位是否合法
	bool isClickOnChessman(int p_x, int p_y, int x, int y);	// 是否点击在棋子上
	void setCurChessman(int type);							// 设置提示图片
	void selectChessman(int type);							// 选择棋子
	void unSelectChessman(int type);						// 取消选择棋子
	void update(float t);									// 更新界面函数

	void gameStart();										// 游戏开始
	void gameOver();										// 游戏结束
	bool isGameOver();										// 游戏是否结束
	void showGameOver();									// 显示游戏结束字符
	void disableGame();										// 停止游戏功能
};

#endif // __GAME_SCENE_H__
