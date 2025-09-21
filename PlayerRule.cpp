#include "PlayerRule.h"
#include <stdio.h>   
#include <iostream>  

PlayerRule::PlayerRule(BattleMap* m)
{
    Map = m;
    RemainingAttacks = 50;  // ���� ���� Ƚ�� (�⺻ 50)
    RemainingShips = Map->GetShipCount();   // ���� �Լ� �� �ʱ�ȭ
}

void PlayerRule::PlayerGame()
{
    while (RemainingAttacks > 0 && RemainingShips > 0)
    {
        Map->PrintMap();
        printf("���� ���� Ƚ��: %d\n", RemainingAttacks);
        printf("���� �� �Լ� ��: %d\n", RemainingShips);
        printf("���� ��ǥ�� �Է��ϼ��� (x y): ");

        int x, y;
        std::cin >> x >> y;

        bool InputFail = std::cin.fail();
        if (InputFail) {
            printf("\n�Է��� ��ȿ���� �ʽ��ϴ�. ���α׷��� �����մϴ�.\n");
            return;
        }

        // ��ǥ ���� �˻�
        bool OutOfRangeX = (x < 0 || x >= Map->GetMapSize());
        bool OutOfRangeY = (y < 0 || y >= Map->GetMapSize());
        if (OutOfRangeX || OutOfRangeY) {
            printf("��ǥ�� ������ ������ϴ�. (0~9)\n");
            continue;
        }

        bool Hit = false;
        bool Sunk = false;
        int ShipIndex = -1;

        // ��ȿ �������� �˻�(�̹� ������ ĭ�̸� false)
        if (!Map->Attack(x, y, Hit, Sunk, ShipIndex)) {
            printf("�̹� �����ߴ� ĭ�Դϴ�. �ٸ� ��ǥ�� �����ϼ���.\n");
            continue;
        }

        // ��ȿ �����̾����Ƿ� ���� Ƚ�� ����
        RemainingAttacks--;

        // ��� �ȳ�
        if (Hit) {
            printf("����!\n");
            if (Sunk) {
                printf("��ħ!\n");
                RemainingShips--;
            }
        }
        else {
            printf("����.\n");
        }
    }

    // ���� ���� ó��
    if (RemainingShips == 0) {
        printf("\n��� �� �Լ��� ��ħ�߽��ϴ�. �¸�!\n");
    }
    else {
        printf("\n���� Ƚ���� ��� �����߽��ϴ�. �й�...\n");
        printf("�� �Լ��� ���� ��ġ�� ������ �����ϴ�:\n");
        Map->RevealShips();
    }
}
