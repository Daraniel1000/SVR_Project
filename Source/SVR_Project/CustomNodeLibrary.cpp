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