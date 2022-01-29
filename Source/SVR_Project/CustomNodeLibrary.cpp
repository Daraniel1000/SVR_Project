// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomNodeLibrary.h"
#include <stdlib.h>
#include <exception>

UClass* UCustomNodes::GetRandomizedActor(const TArray<UClass*> actors, const TArray<int32> chances)
{
	int32 percent = rand() % 100 + 1;
	int32 i;
	for (i = 0; i < actors.Num() - 1; ++i)
	{
		if (percent <= chances[i])
			break;
		percent -= chances[i];
	}
	return actors[i];
}

void UCustomNodes::SpawnHarderEnemies(TArray<int32> chances)
{
	chances[0] = std::max(chances[0] - 5, 0);
	chances[1] = chances[1] + 5;
}

float UCustomNodes::GetSpawnRate(int32 pulse)
{
	return 3 + pulse / 5;
}

int32 UCustomNodes::GetSpawnAmount(int32 pulse)
{
	return 1;
}

int32 UCustomNodes::GetPlayerPulse()
{
	time_t rawtime;
	struct tm timeinfo;
	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);

	return timeinfo.tm_sec;
}