#include "BattleMap.h"
#include "BattleShipProject.h"
#include <cstdio>   
#include <cstdlib>  
#include <ctime>    


BattleMap::BattleMap()
{
    for (int R = 0; R < MAP_SIZE; R++) 
    {
        for (int C = 0; C < MAP_SIZE; C++) 
        {
            Grid[R][C] = '.';   // 맵을 '.'로 초기화
        }
    }
    for (int i = 0; i < SHIP_COUNT; i++)
    {
        Ships[i] = nullptr; //함선 포인터 배열 초기화
    }
    srand(time(0));
}

void BattleMap::PlaceShips()
{
    for (int i = 0; i < SHIP_COUNT; i++)
    {
        if (!Ships[i])  // i번째 함선 포인터가 유효하지 않다면 다음 함선으로 넘어감
        {
            continue;
        }

        bool Placed = false;
        while (!Placed) // 배치가 완료 될 때 까지 반복
        {
            int x = rand() % MAP_SIZE;  // 후보 시작 x 좌표(0 ~ MAP_SIZE-1)
            int y = rand() % MAP_SIZE;   // 후보 시작 y 좌표(0 ~ MAP_SIZE-1)
            bool Horiz = (rand() % 2) == 1; // 가로 배치 여부를 랜덤으로 결정(true/false)

            int Size = Ships[i]->GetShipSize(); // 현재 배치할 함선의 길이(칸 수) 조회
            bool OutX = (Horiz && (x + Size >= MAP_SIZE));  // 가로 배치 시 오른쪽 경계 초과 여부(>= 방지)
            bool OutY = (!Horiz && (y + Size >= MAP_SIZE)); // 세로 배치 시 아래쪽 경계 초과 여부(>= 방지)
            if (OutX || OutY)   // 경계를 초과하면 
            {
                continue;    // 배치 위치를 다시 뽑기 위해 루프 처음으로 이동
            }
                
            bool ok = true; // 겹침/범위 이상 없으면 true로 유지
            for (int j = 0; j < Size; j++)   // 함선 길이만큼 각 칸을 검사
            {
                int nx;  // 실제 칸의 x 좌표 변수
                int ny; // 실제 칸의 y 좌표 변수

                if (Horiz)   // 가로 배치인 경우
                {
                    nx = x + j;   // x는 시작점에서 j만큼 증가
                    ny = y;       // y는 고정
                }
                else // 세로 배치인 경우
                {
                    nx = x;          // x는 고정
                    ny = y + j;     // y는 시작점에서 j만큼 증가
                }

                // 방어적 범위 체크 (이론상 위의 outX/outY가 막지만, 안전망 추가)
                bool BadX = (nx < 0 || nx >= MAP_SIZE);  // x 좌표 범위 벗어남 여부 확인
                bool BadY = (ny < 0 || ny >= MAP_SIZE);  // y 좌표 범위 벗어남 여부 확인
                if (BadX || BadY)    // 어느 한쪽이라도 범위를 벗어나면
                {
                    ok = false;  // 배치 불가로 표시
                    break;
                }

                if (Grid[ny][nx] != '.')     // 해당 칸이 이미 사용 중('.'가 아님)이면
                {
                    ok = false;  // 배치 불가로 표시
                    break;
                }
            }

            if (!ok)     // 검사 결과 배치가 불가능하면
            {
                continue;
            }

            // === 3) 배치 확정 ===
            Ships[i]->SetPosition(x, y, Horiz); // 함선의 시작 좌표와 방향을 실제로 기록

            for (int j = 0; j < Size; j++)
            {
                int nx;
                int ny;

                if (Horiz)
                {
                    nx = x + j;
                    ny = y;
                }
                else
                {
                    nx = x;
                    ny = y + j;
                }

                // 다시 한 번 방어적 범위 체크
                bool BadX = (nx < 0 || nx >= MAP_SIZE);
                bool BadY = (ny < 0 || ny >= MAP_SIZE);
                if (BadX || BadY)
                {
                    ok = false;
                    break;
                }

                Grid[ny][nx] = 'S'; // 내부 상태로만 보관, 출력 시 숨김
            }

            if (!ok)
            {
                // 만약 이 루프에서 범위 문제가 생겼다면 재시도
                continue;
            }

            Placed = true;
        }
    }
}

// 공격 수행
// - (X, Y)가 이미 공격된 칸('※' 또는 '■')이면 false 반환(무효 공격)
// - 적중 시 '※', 빗나감 시 '■'로 표기
bool BattleMap::Attack(int X, int Y, bool& Hit, bool& Sunk, int& ShipIndex)
{
    // 입력 좌표가 이미 처리된 칸이면 무효
    if (Grid[Y][X] == 'X' || Grid[Y][X] == 'O') {
        return false;
    }

    Hit = false;
    Sunk = false;
    ShipIndex = -1;

    // 모든 함선에 대해 적중 여부를 확인
    for (int i = 0; i < SHIP_COUNT; i++)
    {
        if (!Ships[i])
        {
            continue;
        }
        if (Ships[i]->IsHit(X, Y))
        {
            Ships[i]->RegisterHit(X, Y);
            Hit = true;
            ShipIndex = i;
            if (Ships[i]->IsSunk())
            {
                Sunk = true;
            }
            Grid[Y][X] = 'X';
            return true; // 유효 공격
        }
    }

    // 어떤 함선도 맞지 않음
    Grid[Y][X] = 'O';
    return true; // 유효 공격
}

// 플레이어에게 보여줄 맵을 출력합니다.
void BattleMap::PrintMap() const
{
    // 열 헤더
    printf("   ");
    for (int c = 0; c < MAP_SIZE; c++)
    {
        printf("%d ", c);
    }
    printf("\n");

    for (int r = 0; r < MAP_SIZE; r++)
    {
        printf("%2d ", r); // 행 헤더
        for (int c = 0; c < MAP_SIZE; c++)
        {
            char ch = Grid[r][c];
            if (ch == 'S')  // - 내부적으로 'S'(함선)는 보이지 않게 '□'로 숨깁니다.
            {
                ch = '.';
            } // 함선은 숨김
            printf("%c ", ch);
        }
        printf("\n");
    }
}

// 패배 시 호출되어 실제 함선 위치를 포함한 맵을 공개합니다.
// - 'S'는 그대로 보여 줍니다.
void BattleMap::RevealShips() const
{
    // 열 헤더
    printf("   ");
    for (int c = 0; c < MAP_SIZE; c++) {
        printf("%d ", c);
    }
    printf("\n");

    for (int r = 0; r < MAP_SIZE; r++)
    {
        printf("%2d ", r); // 행 헤더
        for (int c = 0; c < MAP_SIZE; c++)
        {
            printf("%c ", Grid[r][c]);
        }
        printf("\n");
    }
}

void BattleMap::SetShip(int Index, EnemyShip* s)
{
    if (Index >= 0 && Index < SHIP_COUNT)
    {
        Ships[Index] = s;
    }
}
