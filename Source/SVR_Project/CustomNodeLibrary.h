// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <string>
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CustomNodeLibrary.generated.h"

/**
 * 
 */
UCLASS()
class SVR_PROJECT_API UCustomNodes : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "Custom Nodes")
	static UClass* GetRandomizedActor(const TArray<UClass*> actors, const TArray<int32> chances);

	UFUNCTION(BlueprintCallable, Category = "Custom Nodes")
	static void SpawnHarderEnemies(const TArray<int32> chances);

	UFUNCTION(BlueprintCallable, Category = "Custom Nodes")
	static void FetchPlayerPulse(int32& pulse);

	UFUNCTION(BlueprintCallable, Category = "Custom Nodes")
	static float GetSpawnRate(int32 pulse);

	UFUNCTION(BlueprintCallable, Category = "Custom Nodes")
	static int32 GetSpawnAmount(int32 pulse);

	static const int32 MIN_PULSE;
	static const int32 MAX_PULSE;
	static const int32 MIN_SPAWN_PERIOD;
	static const int32 MAX_SPAWN_PERIOD;
};
