#pragma once
#include "BattleMap.h"

class PlayerRule
{
public:
    PlayerRule(BattleMap* m);

    void PlayerGame();  // 게임 루프 실행 (플레이어 입력 받아서 공격 진행)

    ~PlayerRule() {}

private:
    BattleMap* Map;         // 게임 맵에 대한 포인터
    int RemainingAttacks = 0;   // 남은 공격 횟수 초기화
    int RemainingShips = 0;     // 남은 적 함선 수 초기화
};

