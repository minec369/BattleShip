#include <stdio.h>
#include <time.h>
#include <random>
#include "BattleShipProject.h"
#include "BattleMap.h"


int main()
{
	srand(time(0));
	
	BattleMap SeaMap;
	SeaMap.PrintBattlefield();

	return 0;
}