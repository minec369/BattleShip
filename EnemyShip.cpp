#include "EnemyShip.h"

EnemyShip::EnemyShip(int S)
{
    // 크기 Size를 받아 내부 상태를 초기화
    // 아직 배치 전이므로 좌표는 -1로 채움
    Size = S;
    HitCount = 0;
    StartX = StartY = 0;
    Horizontal = true;
    for (int i = 0; i < 5; i++) {
        Coords[i][0] = -1;
        Coords[i][1] = -1;
    }
}


// 함선의 시작 위치와 배치 방향(가로/세로)을 설정하고,
// 실제로 차지하는 좌표들을 Coords 배열에 기록합니다.
void EnemyShip::SetPosition(int X, int Y, bool Horiz)
{
    StartX = X;
    StartY = Y;
    Horizontal = Horiz;

    for (int i = 0; i < Size; i++) {
        // 가로면 x가 증가, 세로면 y가 증가
        if (Horiz)
        {
            Coords[i][0] = X + i;
            Coords[i][1] = Y;
        }
        // 세로면 Y 좌표 증가
        else 
        {
            Coords[i][0] = X;
            Coords[i][1] = Y + i;
        }
    }
}

// 전달된 (x, y) 좌표가 이 함선의 임의 칸과 일치하는지 확인합니다.
bool EnemyShip::IsHit(int X, int Y)
{
    for (int i = 0; i < Size; i++)
    {
        if ((Coords[i][0] == X) && (Coords[i][1] == Y))
        {
            return true;
        }
    }
    return false;
}

// (X, Y)가 이 함선에 해당하면 맞은 개수를 증가시킵니다.
// 중복 타격 방지는 Map 쪽에서 처리(같은 칸 재공격 불가)하므로 단순 증가합니다.
void EnemyShip::RegisterHit(int X, int Y)
{
    if (IsHit(X, Y))
    {
        HitCount++;
    }
}

bool EnemyShip::IsSunk() const
{
    return HitCount >= Size;    // 맞은 개수가 크기와 같거나 크면 격침
}
inline void EnemyShip::GetCoords(int Index, int& X, int& Y) const   // i번째(0<=i<size) 칸의 실제 보드 좌표를 반환합니다.
{
    if (Index >= 0 && Index < Size)
    {
        X = Coords[Index][0];
        Y = Coords[Index][1];
    }
}

int EnemyShip::GetShipSize() const  // 함선의 크기를 반환
{
	return Size;
}
