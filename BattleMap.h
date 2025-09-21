#pragma once
#include <string>
#include "EnemyShip.h"

class BattleMap
{
public:

public:
    BattleMap();


    /// <summary>
    /// 모든 함선을 맵에 랜덤 배치
    /// </summary>
    void PlaceShips();


    /// <summary>
    /// 지정된 좌표에 공격을 수행하고 결과를 반환합니다.
    /// </summary>
    /// <param name="X">공격할 위치의 X 좌표입니다.</param>
    /// <param name="Y">공격할 위치의 Y 좌표입니다.</param>
    /// <param name="Hit">공격이 적함에 명중했는지 여부를 저장하는 참조 변수입니다.</param>
    /// <param name="Sunk">공격으로 인해 적함이 침몰했는지 여부를 저장하는 참조 변수입니다.</param>
    /// <param name="ShipIndex">명중 또는 침몰한 함선의 인덱스를 저장하는 참조 변수입니다.</param>
    /// <returns>공격이 유효하게 수행되었으면 true, 그렇지 않으면 false를 반환합니다.</returns>
    bool Attack(int X, int Y, bool& Hit, bool& Sunk, int& ShipIndex);


    /// <summary>
    /// 플레이어에게 보이는 맵 출력 (함선은 안 보임)
    /// </summary>
    void PrintMap() const;


    /// <summary>
    /// 게임 종료 후 실제 함선 위치 공개
    /// </summary>
    void RevealShips() const;


    /// <summary>
    /// 특정 인덱스에 적 함선을 설정합니다.
    /// </summary>
    /// <param name="index">적 함선을 설정할 위치의 인덱스입니다.</param>
    /// <param name="s">설정할 EnemyShip 객체에 대한 포인터입니다.</param>
    void SetShip(int Index, EnemyShip* s);


    /// <summary>
    /// 현재 설정된 선박의 수를 반환합니다.
    /// </summary>
    /// <returns>설정된 선박의 수를 나타내는 정수값을 반환합니다.</returns>
    int GetShipCount() const { return SHIP_COUNT; }


    /// <summary>
    /// 맵 크기의 값을 반환합니다.
    /// </summary>
    /// <returns>맵 크기 상수의 값을 반환합니다.</returns>
    int GetMapSize() const { return MAP_SIZE; }

    

private:
    static const int MAP_SIZE = 10;     // 맵 크기 (10*10)
    static const int SHIP_COUNT = 4;    // 배치되는 함선 수
    char Grid[MAP_SIZE][MAP_SIZE];      // 맵 상태 ('□' = 빈칸, 'S'=함선, '※'=명중, '■'=실패)
    EnemyShip* Ships[SHIP_COUNT];       // 배치된 함선들의 포인터 배열

};

