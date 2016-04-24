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
	Size size;								// ���ڴ�С
	Sprite* selected[2];					// ѡ��ͼƬ, 0 �Ǻ�ɫѡ���1 ����ɫѡ���
	Sprite* curChessman[2];					// ��ʾ��ǰ���ӷ�
	Node* board;							// ����
	Label* status;							// ��ʾ������Ϣ
	Label* status2;							// ��ʾ�����Ϣ
	EventListenerTouchOneByOne* listener;	// ��������
	void initUI();							// ��ʼ������
	void initListener();					// ��ʼ������
	void initChessman();					// ��ʼ������

	int map[10][9];							// ���̵�ͼ
	Chessman *allChessman[32];				// ��������
	bool color;								// �����ɫ��0 ��ɫ��1 ��ɫ
	bool is_wait;							// �ȴ���־
	bool is_selected;						// �Ƿ���ѡ������
	int is_resigned;						// �����־��0 ��ʾ˫���������䣬1 �Է����䣬2 ��������
	bool is_gameStart;						// ��Ϸ�Ƿ�ʼ
	int red_king_id;						// �췽��ID
	int black_king_id;						// �ڷ���ID
	ChessMove moveStep;						// �ƶ�����

	ODSocket *sockServer;					// ������sock
	ODSocket *sockClient;					// �ͻ���sock
	Message msg;							// ��Ϣ
	list<Message*> messageQueue;			// ��Ϣ����
	mutex messageQueueMutex;				// ��Ϣ��

	void accept();							// �ȴ�����
	void send();							// ������Ϣ
	void receive();							// ������Ϣ
	void cleanMessage();					// ����message

	void newChessman(int x, int y, int id, int angle = 0);	// �½�����
	void moveChessman();									// �ƶ�����
	void captureChessman();									// ����
	bool isRedOrBlack(int x, int type);						// �ж�һ�������Ǻ�ɫ���Ǻ�ɫ, 0�жϺ�ɫ, 1�жϺ�ɫ
	bool isValidMove(int toX, int toY);						// �ж�һ�����ӵ���λ�Ƿ�Ϸ�
	bool isClickOnChessman(int p_x, int p_y, int x, int y);	// �Ƿ�����������
	void setCurChessman(int type);							// ������ʾͼƬ
	void selectChessman(int type);							// ѡ������
	void unSelectChessman(int type);						// ȡ��ѡ������
	void update(float t);									// ���½��溯��

	void gameStart();										// ��Ϸ��ʼ
	void gameOver();										// ��Ϸ����
	bool isGameOver();										// ��Ϸ�Ƿ����
	void showGameOver();									// ��ʾ��Ϸ�����ַ�
	void disableGame();										// ֹͣ��Ϸ����
};

#endif // __GAME_SCENE_H__