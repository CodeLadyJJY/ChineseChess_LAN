#ifndef  _DEFINE_H_
#define  _DEFINE_H_

#define NOCHESS		0		// 没有棋子
#define B_KING		1		// 黑帅
#define B_CAR		2		// 黑车
#define B_HORSE		3		// 黑马
#define B_CANON		4		// 黑炮
#define B_BISHOP	5		// 黑士
#define B_ELEPHANT	6		// 黑象
#define B_PAWN		7  		// 黑卒
#define B_BEGIN		B_KING
#define B_END		B_PAWN
#define R_KING		8		// 红将
#define R_CAR		9		// 红车
#define R_HORSE		10		// 红马
#define R_CANON		11		// 红炮
#define R_BISHOP	12		// 红仕
#define R_ELEPHANT	13		// 红相
#define R_PAWN		14		// 红兵
#define R_BEGIN		R_KING
#define R_END		R_PAWN

const int InitChessBoard[10][9] =
{
	{ B_CAR,   B_HORSE, B_ELEPHANT, B_BISHOP, B_KING,  B_BISHOP, B_ELEPHANT, B_HORSE, B_CAR },
	{ NOCHESS, NOCHESS, NOCHESS,    NOCHESS,  NOCHESS, NOCHESS,  NOCHESS,    NOCHESS, NOCHESS },
	{ NOCHESS, B_CANON, NOCHESS,    NOCHESS,  NOCHESS, NOCHESS,  NOCHESS,    B_CANON, NOCHESS },
	{ B_PAWN,  NOCHESS, B_PAWN,     NOCHESS,  B_PAWN,  NOCHESS,  B_PAWN,     NOCHESS, B_PAWN },
	{ NOCHESS, NOCHESS, NOCHESS,    NOCHESS,  NOCHESS, NOCHESS,  NOCHESS,    NOCHESS, NOCHESS },

	{ NOCHESS, NOCHESS, NOCHESS,    NOCHESS,  NOCHESS, NOCHESS,  NOCHESS,    NOCHESS, NOCHESS },
	{ R_PAWN,  NOCHESS, R_PAWN,     NOCHESS,  R_PAWN,  NOCHESS,  R_PAWN,     NOCHESS, R_PAWN },
	{ NOCHESS, R_CANON, NOCHESS,    NOCHESS,  NOCHESS, NOCHESS,  NOCHESS,    R_CANON, NOCHESS },
	{ NOCHESS, NOCHESS, NOCHESS,    NOCHESS,  NOCHESS, NOCHESS,  NOCHESS,    NOCHESS, NOCHESS },
	{ R_CAR,   R_HORSE, R_ELEPHANT, R_BISHOP, R_KING,  R_BISHOP, R_ELEPHANT, R_HORSE, R_CAR }
};

// 判断一个棋子是不是黑色
#define IsBlack(x) (x >= B_KING && x <= B_PAWN)
// 判断一个棋子是不是红色
#define IsRed(x) (x >= R_KING && x <= R_PAWN)
// 判断两个棋子是否同色
#define IsSameSide(x, y) ((IsBlack(x) && IsBlack(y)) || (IsRed(x) && IsRed(y)))

// 定义一个棋子位置的结构
typedef struct ChessmanPosition
{
	int x;
	int y;
}ChessmanPos;

// 定义一个棋子走步
typedef struct ChessMove
{
	int	id;				// 棋子编号
	int type;			// 棋子类型
	int eaten_id;		// 被吃子id
	ChessmanPos	from;
	ChessmanPos	to;
}ChessMove;



#define MSG_MOVE			1	// 落子消息
#define MSG_CAPTURE			2	// 吃子消息
#define MSG_RESIGN			3	// 认输消息

typedef struct
{
	int type;				// 消息类型
	ChessMove move;			// 移动信息
}Message;

#endif