#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <time.h>
#include "BattleShipProject.h"
#include "BattleMap.h"
#include "EnemyShip.h"
#include "PlayerRule.h"


int main()
{
    printf("=== Battleship 시작 ===\n");
    // 1) 적 함선 4척 생성 (크기: 5, 4, 3, 2)
    EnemyShip S1(5);
    EnemyShip S2(4);
    EnemyShip S3(3);
    EnemyShip S4(2);

    // 2) 맵 생성
    BattleMap Map;

    // 3) 맵에 함선 포인터 연결 (인덱스 0~3)
    Map.SetShip(0, &S1);
    Map.SetShip(1, &S2);
    Map.SetShip(2, &S3);
    Map.SetShip(3, &S4);

    // 4) 함선 랜덤 배치
    Map.PlaceShips();

    // 5) 플레이어 생성(맵 전달) 및 게임 시작
    PlayerRule P(&Map);
    P.PlayerGame();

    return 0;
}