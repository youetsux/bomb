#pragma once
#include "./Library/GameObject.h"
#include <vector>
#include <map>
#include <string>
#include <vector>


using std::vector;


class Stage :
    public GameObject
{
	vector<vector<STAGE_OBJ>> stageData;
public:
	Stage();
	~Stage();
	void Update() override;
	void Draw() override;
	STAGE_OBJ GetStageData(int x, int y) {return stageData[y][x];}
};

