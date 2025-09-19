#pragma once
#include <string>

class BattleMap
{
public:
	
	// 적이 실제로 숨어 있는 맵 함수
	void SeaBattlefield();

	// 플레이어가 보는 맵 함수
	void PrintBattlefield();

	
	

	enum SeaTile
	{
		Sea = 1,	// □
		Blank = 2,	// ■
		Enemy = 3	// ※
	};
	



private:
	// 맵 가로가 10
	static constexpr int Width = 10;

	// 맵 세로가 10
	static constexpr int Height = 10;


	int BattleField[Height][Width];


};

