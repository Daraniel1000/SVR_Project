// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
	static UClass* GetRandomizedActor(const TArray<UClass*> actors, const TArray<float> weights);
};
