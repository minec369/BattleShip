#include "BattleMap.h"
#include <string>

void BattleMap::SeaBattlefield()
{
	int TempBattleField[Height][Width] =
	{
		{1,1,1,1,1,1,1,1,1,1,},
		{1,1,1,1,1,1,1,1,1,1,},
		{1,1,1,1,1,1,1,1,1,1,},
		{1,1,1,1,1,1,1,1,1,1,},
		{1,1,1,1,1,1,1,1,1,1,},
		{1,1,1,1,1,1,1,1,1,1,},
		{1,1,1,1,1,1,1,1,1,1,},
		{1,1,1,1,1,1,1,1,1,1,},
		{1,1,1,1,1,1,1,1,1,1,},
		{1,1,1,1,1,1,1,1,1,1,}
	};

	for (int y = 0; y < Height; y++)
	{
		for (int x = 0; x < Width; x++)
		{
			BattleField[y][x] = TempBattleField[y][x];
		}
		printf("\n");
	}

}

void BattleMap::PrintBattlefield()
{
	for (int y = 0; y < Height; y++)
	{
		for (int x = 0; x < Width; x++)
		{
			printf("бр");
		}
		printf("\n");
	}
}

 