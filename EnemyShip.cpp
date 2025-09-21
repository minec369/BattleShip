#include "EnemyShip.h"

EnemyShip::EnemyShip(int S)
{
    // ũ�� Size�� �޾� ���� ���¸� �ʱ�ȭ
    // ���� ��ġ ���̹Ƿ� ��ǥ�� -1�� ä��
    Size = S;
    HitCount = 0;
    StartX = StartY = 0;
    Horizontal = true;
    for (int i = 0; i < 5; i++) {
        Coords[i][0] = -1;
        Coords[i][1] = -1;
    }
}


// �Լ��� ���� ��ġ�� ��ġ ����(����/����)�� �����ϰ�,
// ������ �����ϴ� ��ǥ���� Coords �迭�� ����մϴ�.
void EnemyShip::SetPosition(int X, int Y, bool Horiz)
{
    StartX = X;
    StartY = Y;
    Horizontal = Horiz;

    for (int i = 0; i < Size; i++) {
        // ���θ� x�� ����, ���θ� y�� ����
        if (Horiz)
        {
            Coords[i][0] = X + i;
            Coords[i][1] = Y;
        }
        // ���θ� Y ��ǥ ����
        else 
        {
            Coords[i][0] = X;
            Coords[i][1] = Y + i;
        }
    }
}

// ���޵� (x, y) ��ǥ�� �� �Լ��� ���� ĭ�� ��ġ�ϴ��� Ȯ���մϴ�.
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

// (X, Y)�� �� �Լ��� �ش��ϸ� ���� ������ ������ŵ�ϴ�.
// �ߺ� Ÿ�� ������ Map �ʿ��� ó��(���� ĭ ����� �Ұ�)�ϹǷ� �ܼ� �����մϴ�.
void EnemyShip::RegisterHit(int X, int Y)
{
    if (IsHit(X, Y))
    {
        HitCount++;
    }
}

bool EnemyShip::IsSunk() const
{
    return HitCount >= Size;    // ���� ������ ũ��� ���ų� ũ�� ��ħ
}
inline void EnemyShip::GetCoords(int Index, int& X, int& Y) const   // i��°(0<=i<size) ĭ�� ���� ���� ��ǥ�� ��ȯ�մϴ�.
{
    if (Index >= 0 && Index < Size)
    {
        X = Coords[Index][0];
        Y = Coords[Index][1];
    }
}

int EnemyShip::GetShipSize() const  // �Լ��� ũ�⸦ ��ȯ
{
	return Size;
}
