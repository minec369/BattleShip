#pragma once
#include "BattleMap.h"

class PlayerRule
{
public:
    PlayerRule(BattleMap* m);

    void PlayerGame();  // ���� ���� ���� (�÷��̾� �Է� �޾Ƽ� ���� ����)

    ~PlayerRule() {}

private:
    BattleMap* Map;         // ���� �ʿ� ���� ������
    int RemainingAttacks = 0;   // ���� ���� Ƚ�� �ʱ�ȭ
    int RemainingShips = 0;     // ���� �� �Լ� �� �ʱ�ȭ
};

