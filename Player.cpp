#include "Player.h"
#include "./Source/Input.h"
#include "./Stage.h"
#include "globals.h"

namespace {
	enum DIR
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		NONE,
		MAXDIR
	};
	DIR inputDir = NONE;
	int CheckHitRegion(const Rect& me, const Rect& other)
	{
		if (me.x > other.x)
		{
			if (abs(me.x - other.x) < CHA_WIDTH / 4)
			{
				//左にニョロ
				return 0;
			}
		}
		else
		{
			if (abs(me.x - other.x) < CHA_WIDTH / 4)
			{
				return 1;
				//右にニョロ
			}
		}
		if (me.y > other.y)
		{
			if (abs(me.y - other.y) < CHA_HEIGHT / 4)
			{
				return 2;
				//上にニョロ
			}
		}
		else
		{
			if (abs(me.y - other.y) < CHA_HEIGHT / 4)
			{
				//下にニョロ
				return 3;
			}
		}
		return -1;
	}
}


Player::Player()
	: x(CHA_WIDTH), y(CHA_HEIGHT)
{
}

Player::~Player()
{
}

void Player::Update()
{
	int ox = x, oy = y;
	
	if (Input::IsKeepKeyDown(KEY_INPUT_UP))
	{
		y--;
		inputDir = UP;
	}
	if (Input::IsKeepKeyDown(KEY_INPUT_DOWN))
	{
		y++;
		inputDir = DOWN;
	}
	if (Input::IsKeepKeyDown(KEY_INPUT_LEFT))
	{
		x--;
		inputDir = LEFT;
	}
	if (Input::IsKeepKeyDown(KEY_INPUT_RIGHT))
	{
		x++;
		inputDir = RIGHT;
	}

	Stage* stage = (Stage*)FindGameObject<Stage>();
	Rect playerRect = { x, y, CHA_WIDTH, CHA_HEIGHT };

	for(auto& obj : stage->GetStageRects())
	{
		//Rect objRect = { obj.x, obj.y, CHA_WIDTH, CHA_HEIGHT };

		if (CheckHit(playerRect, obj))
		{
			Rect tmpRectX = { ox, y, CHA_WIDTH, CHA_HEIGHT };
			Rect tmpRecty = { x, oy, CHA_WIDTH, CHA_HEIGHT };
			//if (CheckHitRegion(playerRect, obj) < 0)
			//{
				if (!CheckHit(tmpRectX, obj))
				{
					x = ox;
				}
				else if (!CheckHit(tmpRecty, obj))
				{
					y = oy;
				}
				else
				{
					x = ox;
					y = oy;			
				}
				if (inputDir == LEFT || inputDir == RIGHT)
				{

				}
				else if (inputDir == UP || inputDir == DOWN)
				{

				}
//			}
		}
	}
}

void Player::Draw()
{
	DrawBox(x, y, x + CHA_WIDTH, y + CHA_HEIGHT, GetColor(255,10,10), TRUE);
}

bool Player::CheckHit(const Rect& me, const Rect& other)
{
	if (me.x < other.x + other.w &&
		me.x + me.w > other.x &&
		me.y < other.y + other.h &&
		me.y + me.h > other.y)
	{
		return true;
	}
	return false;
}
