#include "PlayerRule.h"
#include <stdio.h>   
#include <iostream>  

PlayerRule::PlayerRule(BattleMap* m)
{
    Map = m;
    RemainingAttacks = 50;  // 남은 공격 횟수 (기본 50)
    RemainingShips = Map->GetShipCount();   // 남은 함선 수 초기화
}

void PlayerRule::PlayerGame()
{
    while (RemainingAttacks > 0 && RemainingShips > 0)
    {
        Map->PrintMap();
        printf("남은 공격 횟수: %d\n", RemainingAttacks);
        printf("남은 적 함선 수: %d\n", RemainingShips);
        printf("공격 좌표를 입력하세요 (x y): ");

        int x, y;
        std::cin >> x >> y;

        bool InputFail = std::cin.fail();
        if (InputFail) {
            printf("\n입력이 유효하지 않습니다. 프로그램을 종료합니다.\n");
            return;
        }

        // 좌표 범위 검사
        bool OutOfRangeX = (x < 0 || x >= Map->GetMapSize());
        bool OutOfRangeY = (y < 0 || y >= Map->GetMapSize());
        if (OutOfRangeX || OutOfRangeY) {
            printf("좌표가 범위를 벗어났습니다. (0~9)\n");
            continue;
        }

        bool Hit = false;
        bool Sunk = false;
        int ShipIndex = -1;

        // 유효 공격인지 검사(이미 공격한 칸이면 false)
        if (!Map->Attack(x, y, Hit, Sunk, ShipIndex)) {
            printf("이미 공격했던 칸입니다. 다른 좌표를 선택하세요.\n");
            continue;
        }

        // 유효 공격이었으므로 공격 횟수 차감
        RemainingAttacks--;

        // 결과 안내
        if (Hit) {
            printf("명중!\n");
            if (Sunk) {
                printf("격침!\n");
                RemainingShips--;
            }
        }
        else {
            printf("실패.\n");
        }
    }

    // 게임 종료 처리
    if (RemainingShips == 0) {
        printf("\n모든 적 함선을 격침했습니다. 승리!\n");
    }
    else {
        printf("\n공격 횟수를 모두 소진했습니다. 패배...\n");
        printf("적 함선의 실제 위치는 다음과 같습니다:\n");
        Map->RevealShips();
    }
}
