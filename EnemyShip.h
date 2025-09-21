#pragma once
#include <string>


class EnemyShip {


public:
    EnemyShip(int S);                                       // ������: ũ�⸦ �޾� �Լ� �ʱ�ȭ


    /// <summary>
    /// �Լ� ��ġ ����
    /// </summary>
    /// <param name="X">X ��ǥ</param>
    /// <param name="Y">Y ��ǥ</param>
    /// <param name="Horiz"> ���� ����</param>
    void SetPosition(int X, int Y, bool Horiz);


    /// <summary>
    /// ������ ��ǥ (X, Y)�� �������� ���θ� �Ǵ��մϴ�.
    /// </summary>
    /// <param name="X">Ȯ���� X ��ǥ�Դϴ�.</param>
    /// <param name="Y">Ȯ���� Y ��ǥ�Դϴ�.</param>
    /// <returns>��ǥ�� �����̸� true, �ƴϸ� false�� ��ȯ�մϴ�.</returns>
    bool IsHit(int X, int Y);

    /// <summary>
    /// ���� ��ǥ�� �¾Ҵٸ� ���� Ƚ�� ����
    /// </summary>
    /// <param name="X">Ȯ���� X ��ǥ�Դϴ�.</param>
    /// <param name="Y">Ȯ���� Y ��ǥ�Դϴ�.</param>
    void RegisterHit(int X, int Y);


    /// <summary>
    /// �� ��ü�� ħ���ߴ��� ���θ� Ȯ���մϴ�.
    /// </summary>
    /// <returns>��ü�� ħ���� ��� true, �׷��� ������ false�� ��ȯ�մϴ�.</returns>
    bool IsSunk() const;


    /// <summary>
    /// �Լ��� ũ�⸦ ��ȯ�մϴ�.
    /// </summary>
    /// <returns>�Լ��� ũ�⸦ ��Ÿ���� �������� ��ȯ�մϴ�.</returns>
    int GetShipSize() const;


    /// <summary>
    ///  �ε����� �ش��ϴ� ��ǥ(X, Y)�� ��ȯ�մϴ�.
    /// </summary>
    /// <param name="Index">��ǥ�� ������ �ε��� ���Դϴ�.</param>
    /// <param name="X">����� ��ȯ�� X ��ǥ�� ������ ���� �����Դϴ�.</param>
    /// <param name="Y">����� ��ȯ�� Y ��ǥ�� ������ ���� �����Դϴ�.</param>
    void GetCoords(int Index, int& X, int& Y) const;

private:
    int Size;                // �Լ��� ũ�� (ĭ ��)
    int HitCount;            // ���� Ƚ��
    int StartX, StartY;      // ���� ��ǥ
    bool Horizontal;         // ���� ��ġ ����
    int Coords[5][2];        // �Լ��� ������ �ϴ� (�ִ� ũ�� 5)

};

