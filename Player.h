#pragma once
#include "./Library/GameObject.h"
#include "./globals.h"

class Player :
    public GameObject
{
    int playerImage;
    int x, y;
public:
	Player();
    ~Player();
    void Update() override;
    void Draw() override;
	bool CheckHit(const Rect& me,const Rect& other);
};

