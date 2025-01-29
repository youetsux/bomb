#include "Player.h"
#include "./Source/Input.h"
#include "./Stage.h"
#include "globals.h"

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
	}
	if (Input::IsKeepKeyDown(KEY_INPUT_DOWN))
	{
		y++;
	}
	if (Input::IsKeepKeyDown(KEY_INPUT_LEFT))
	{
		x--;
	}
	if (Input::IsKeepKeyDown(KEY_INPUT_RIGHT))
	{
		x++;
	}

	Stage* stage = (Stage*)FindGameObject<Stage>();
	if (stage->GetStageData(x / CHA_WIDTH, y / CHA_HEIGHT) == STAGE_OBJ::WALL)
	{
		if (stage->GetStageData(ox / CHA_WIDTH, y / CHA_HEIGHT) == STAGE_OBJ::WALL)
		{
			x = ox;
		}
		else if (stage->GetStageData(x / CHA_WIDTH, oy / CHA_HEIGHT) == STAGE_OBJ::WALL)
		{
			y = oy;
		}
		else
		{
			x = ox;
			y = oy;
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
