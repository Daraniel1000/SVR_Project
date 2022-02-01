// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomNodeLibrary.h"
#include <stdlib.h>
#include <exception>
#include <string>
#include "HttpModule.h"
#include "Runtime/Online/HTTP/Public/Interfaces/IHttpResponse.h"

const int32 UCustomNodes::MIN_PULSE = 70;
const int32 UCustomNodes::MAX_PULSE = 170;
const int32 UCustomNodes::MIN_SPAWN_PERIOD = 4;
const int32 UCustomNodes::MAX_SPAWN_PERIOD = 12;

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

void UCustomNodes::FetchPlayerPulse(int32& pulse)
{
	auto request = FHttpModule::Get().CreateRequest();

	request->SetVerb("GET");
	request->SetHeader("Content-Type", "text/plain");
	request->SetURL("http://localhost:8080/");

	request->OnProcessRequestComplete().BindLambda(
		[&](FHttpRequestPtr request, FHttpResponsePtr response, bool success) -> void {
			if (success) {
				pulse = std::stoi(TCHAR_TO_UTF8(*response->GetContentAsString()));
			}
			else {
				pulse = MAX_PULSE;
			}
		});

	request->ProcessRequest();
}

float UCustomNodes::GetSpawnRate(int32 pulse)
{
	return MIN_SPAWN_PERIOD + ((pulse - MIN_PULSE) / (MAX_PULSE - MIN_PULSE)) * (MAX_SPAWN_PERIOD - MIN_SPAWN_PERIOD);
}

int32 UCustomNodes::GetSpawnAmount(int32 pulse)
{
	return 1;
}