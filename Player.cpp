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
}


Player::Player()
	: x(CHA_WIDTH), y(CHA_HEIGHT),playerImage(-1)
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
	else if (Input::IsKeepKeyDown(KEY_INPUT_DOWN))
	{
		y++;
		inputDir = DOWN;
	}
	else if (Input::IsKeepKeyDown(KEY_INPUT_LEFT))
	{
		x--;
		inputDir = LEFT;
	}
	else if (Input::IsKeepKeyDown(KEY_INPUT_RIGHT))
	{
		x++;
		inputDir = RIGHT;
	}

	Stage* stage = (Stage*)FindGameObject<Stage>();
	Rect playerRect = { x, y, CHA_WIDTH, CHA_HEIGHT };

	for (auto& obj : stage->GetStageRects())
	{
		if (CheckHit(playerRect, obj))
		{
			Rect tmpRectX = { ox, y, CHA_WIDTH, CHA_HEIGHT };
			Rect tmpRecty = { x, oy, CHA_WIDTH, CHA_HEIGHT };

			if (!CheckHit(tmpRectX, obj))
			{
				x = ox;
				Point centerMe = Rect{ x, y, CHA_WIDTH, CHA_HEIGHT }.GetCenter();
				Point centerObj = obj.GetCenter();
				if (centerMe.y > centerObj.y)
				{
					y++;
				}
				if (centerMe.y < centerObj.y)
				{
					y--;
				}
			}
			else if (!CheckHit(tmpRecty, obj))
			{
				y = oy;
				Point centerMe = Rect{ x, y, CHA_WIDTH, CHA_HEIGHT }.GetCenter();
				Point centerObj = obj.GetCenter();
				if (centerMe.x > centerObj.x)
				{
					x++;
				}
				if (centerMe.x < centerObj.x)
				{
					x--;
				}
			}
			else
			{
				x = ox;
				y = oy;
			}
		}
	}
}

void Player::Draw()
{
	DrawBox(x, y, x + CHA_WIDTH, y + CHA_HEIGHT, GetColor(255, 10, 10), TRUE);
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
