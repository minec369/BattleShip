#pragma once


class EnemyShip
{
public:

	//적 함선은 총 4척, 크기 5, 4, 3, 2
	void EnemyDestroyer();

	// 함선은 맵에 겹치지 않게 가로 또는 세로로 랜덤 배치
	void PlaceShipsRandomly(int& InPutShip);

private:


};

