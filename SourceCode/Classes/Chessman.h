#ifndef _CHESSMAN_H_
#define _CHESSMAN_H_

#include "cocos2d.h"
#include "GameDefine.h"

class Chessman : public cocos2d::Sprite
{
public:
	int m_x;	// 记录棋子棋盘坐标
	int m_y;
	int p_x;	// 记录棋子物理坐标
	int p_y;
	int id;		// 棋子在allChessman中的id
	int type;	// 棋子类型
	bool isLive;// 是否存活

	void setPos(int row, int col);			// 记录位置坐标
	void setPositionRC(int row, int col);	// 设置位置

	static Chessman* create(int type);
	virtual bool init(int type);
};

#endif