#include "Chessman.h"

USING_NS_CC;

Chessman* Chessman::create(int type)
{
	Chessman* pRet = new Chessman();
	if (pRet && pRet->init(type))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool Chessman::init(int type)
{
	if (!Sprite::init())
	{
		return false;
	}

	auto sprite = Sprite::createWithSpriteFrameName(StringUtils::format("%d.png", type));
	this->addChild(sprite);

	this->type = type;
	this->isLive = true;

	return true;
}

void Chessman::setPos(int row, int col)
{
	this->m_x = row;
	this->m_y = col;
	p_x = GRID_WIDTH * col - BOARD_WIDTH / 2;
	p_y = GRID_WIDTH * (9 - row) - BOARD_HEIGHT / 2;
}

void Chessman::setPositionRC(int row, int col)
{
	this->setPos(row, col);
	this->setPosition(Vec2(p_x, p_y));
}