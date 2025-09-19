#include "EnemyShip.h"

void EnemyShip::EnemyDestroyer()
{
	const int EnemyBattelShip1[5] = { '※', '※', '※', '※', '※' };
	const int EnemyBattelShip2[4] = { '※', '※', '※', '※'};
	const int EnemyBattelShip3[3] = { '※', '※', '※'};
	const int EnemyBattelShip4[2] = { '※', '※'};
}

void EnemyShip::PlaceShipsRandomly(int& InPutShip)
{

}

//함선은 맵에 겹치지 않게 가로 또는 세로로 랜덤 배치
// 일단 랜덤으로 가로로 배열에 설정 -> 되면 끝
// 안 되면 랜덤으로 세로로 배열에 설정 -> 되면 끝
// 안 되면 다시 위의 과정을 무한 반복 (될 때 까지)