#pragma once
#include <string>


class EnemyShip {


public:
    EnemyShip(int S);                                       // 생성자: 크기를 받아 함선 초기화


    /// <summary>
    /// 함선 위치 지정
    /// </summary>
    /// <param name="X">X 좌표</param>
    /// <param name="Y">Y 좌표</param>
    /// <param name="Horiz"> 가로 여부</param>
    void SetPosition(int X, int Y, bool Horiz);


    /// <summary>
    /// 지정된 좌표 (X, Y)가 명중인지 여부를 판단합니다.
    /// </summary>
    /// <param name="X">확인할 X 좌표입니다.</param>
    /// <param name="Y">확인할 Y 좌표입니다.</param>
    /// <returns>좌표가 명중이면 true, 아니면 false를 반환합니다.</returns>
    bool IsHit(int X, int Y);

    /// <summary>
    /// 공격 봐표가 맞았다면 맞은 횟수 증가
    /// </summary>
    /// <param name="X">확인할 X 좌표입니다.</param>
    /// <param name="Y">확인할 Y 좌표입니다.</param>
    void RegisterHit(int X, int Y);


    /// <summary>
    /// 이 객체가 침몰했는지 여부를 확인합니다.
    /// </summary>
    /// <returns>객체가 침몰한 경우 true, 그렇지 않으면 false를 반환합니다.</returns>
    bool IsSunk() const;


    /// <summary>
    /// 함선의 크기를 반환합니다.
    /// </summary>
    /// <returns>함선의 크기를 나타내는 정수값을 반환합니다.</returns>
    int GetShipSize() const;


    /// <summary>
    ///  인덱스에 해당하는 좌표(X, Y)를 반환합니다.
    /// </summary>
    /// <param name="Index">좌표를 가져올 인덱스 값입니다.</param>
    /// <param name="X">결과로 반환될 X 좌표를 저장할 참조 변수입니다.</param>
    /// <param name="Y">결과로 반환될 Y 좌표를 저장할 참조 변수입니다.</param>
    void GetCoords(int Index, int& X, int& Y) const;

private:
    int Size;                // 함선의 크기 (칸 수)
    int HitCount;            // 맞은 횟수
    int StartX, StartY;      // 시작 좌표
    bool Horizontal;         // 가로 배치 여부
    int Coords[5][2];        // 함선이 차지는 하는 (최대 크기 5)

};

