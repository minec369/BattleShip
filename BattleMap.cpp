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
            Grid[R][C] = '.';   // ���� '.'�� �ʱ�ȭ
        }
    }
    for (int i = 0; i < SHIP_COUNT; i++)
    {
        Ships[i] = nullptr; //�Լ� ������ �迭 �ʱ�ȭ
    }
    srand(time(0));
}

void BattleMap::PlaceShips()
{
    for (int i = 0; i < SHIP_COUNT; i++)
    {
        if (!Ships[i])  // i��° �Լ� �����Ͱ� ��ȿ���� �ʴٸ� ���� �Լ����� �Ѿ
        {
            continue;
        }

        bool Placed = false;
        while (!Placed) // ��ġ�� �Ϸ� �� �� ���� �ݺ�
        {
            int x = rand() % MAP_SIZE;  // �ĺ� ���� x ��ǥ(0 ~ MAP_SIZE-1)
            int y = rand() % MAP_SIZE;   // �ĺ� ���� y ��ǥ(0 ~ MAP_SIZE-1)
            bool Horiz = (rand() % 2) == 1; // ���� ��ġ ���θ� �������� ����(true/false)

            int Size = Ships[i]->GetShipSize(); // ���� ��ġ�� �Լ��� ����(ĭ ��) ��ȸ
            bool OutX = (Horiz && (x + Size >= MAP_SIZE));  // ���� ��ġ �� ������ ��� �ʰ� ����(>= ����)
            bool OutY = (!Horiz && (y + Size >= MAP_SIZE)); // ���� ��ġ �� �Ʒ��� ��� �ʰ� ����(>= ����)
            if (OutX || OutY)   // ��踦 �ʰ��ϸ� 
            {
                continue;    // ��ġ ��ġ�� �ٽ� �̱� ���� ���� ó������ �̵�
            }
                
            bool ok = true; // ��ħ/���� �̻� ������ true�� ����
            for (int j = 0; j < Size; j++)   // �Լ� ���̸�ŭ �� ĭ�� �˻�
            {
                int nx;  // ���� ĭ�� x ��ǥ ����
                int ny; // ���� ĭ�� y ��ǥ ����

                if (Horiz)   // ���� ��ġ�� ���
                {
                    nx = x + j;   // x�� ���������� j��ŭ ����
                    ny = y;       // y�� ����
                }
                else // ���� ��ġ�� ���
                {
                    nx = x;          // x�� ����
                    ny = y + j;     // y�� ���������� j��ŭ ����
                }

                // ����� ���� üũ (�̷л� ���� outX/outY�� ������, ������ �߰�)
                bool BadX = (nx < 0 || nx >= MAP_SIZE);  // x ��ǥ ���� ��� ���� Ȯ��
                bool BadY = (ny < 0 || ny >= MAP_SIZE);  // y ��ǥ ���� ��� ���� Ȯ��
                if (BadX || BadY)    // ��� �����̶� ������ �����
                {
                    ok = false;  // ��ġ �Ұ��� ǥ��
                    break;
                }

                if (Grid[ny][nx] != '.')     // �ش� ĭ�� �̹� ��� ��('.'�� �ƴ�)�̸�
                {
                    ok = false;  // ��ġ �Ұ��� ǥ��
                    break;
                }
            }

            if (!ok)     // �˻� ��� ��ġ�� �Ұ����ϸ�
            {
                continue;
            }

            // === 3) ��ġ Ȯ�� ===
            Ships[i]->SetPosition(x, y, Horiz); // �Լ��� ���� ��ǥ�� ������ ������ ���

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

                // �ٽ� �� �� ����� ���� üũ
                bool BadX = (nx < 0 || nx >= MAP_SIZE);
                bool BadY = (ny < 0 || ny >= MAP_SIZE);
                if (BadX || BadY)
                {
                    ok = false;
                    break;
                }

                Grid[ny][nx] = 'S'; // ���� ���·θ� ����, ��� �� ����
            }

            if (!ok)
            {
                // ���� �� �������� ���� ������ ����ٸ� ��õ�
                continue;
            }

            Placed = true;
        }
    }
}

// ���� ����
// - (X, Y)�� �̹� ���ݵ� ĭ('��' �Ǵ� '��')�̸� false ��ȯ(��ȿ ����)
// - ���� �� '��', ������ �� '��'�� ǥ��
bool BattleMap::Attack(int X, int Y, bool& Hit, bool& Sunk, int& ShipIndex)
{
    // �Է� ��ǥ�� �̹� ó���� ĭ�̸� ��ȿ
    if (Grid[Y][X] == 'X' || Grid[Y][X] == 'O') {
        return false;
    }

    Hit = false;
    Sunk = false;
    ShipIndex = -1;

    // ��� �Լ��� ���� ���� ���θ� Ȯ��
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
            return true; // ��ȿ ����
        }
    }

    // � �Լ��� ���� ����
    Grid[Y][X] = 'O';
    return true; // ��ȿ ����
}

// �÷��̾�� ������ ���� ����մϴ�.
void BattleMap::PrintMap() const
{
    // �� ���
    printf("   ");
    for (int c = 0; c < MAP_SIZE; c++)
    {
        printf("%d ", c);
    }
    printf("\n");

    for (int r = 0; r < MAP_SIZE; r++)
    {
        printf("%2d ", r); // �� ���
        for (int c = 0; c < MAP_SIZE; c++)
        {
            char ch = Grid[r][c];
            if (ch == 'S')  // - ���������� 'S'(�Լ�)�� ������ �ʰ� '��'�� ����ϴ�.
            {
                ch = '.';
            } // �Լ��� ����
            printf("%c ", ch);
        }
        printf("\n");
    }
}

// �й� �� ȣ��Ǿ� ���� �Լ� ��ġ�� ������ ���� �����մϴ�.
// - 'S'�� �״�� ���� �ݴϴ�.
void BattleMap::RevealShips() const
{
    // �� ���
    printf("   ");
    for (int c = 0; c < MAP_SIZE; c++) {
        printf("%d ", c);
    }
    printf("\n");

    for (int r = 0; r < MAP_SIZE; r++)
    {
        printf("%2d ", r); // �� ���
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
