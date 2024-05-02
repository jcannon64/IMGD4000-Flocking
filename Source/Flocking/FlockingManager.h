#pragma once

#include "CoreMinimal.h"
#include "Agent.h"
#include "FlockingManager.generated.h"

UCLASS()
class FLOCKING_API UFlockingManager : public UObject
{

public:
	GENERATED_BODY()

	void Init(UWorld* world, UStaticMeshComponent* mesh);
	void Flock();
	FVector Cohesion(AAgent* boid);
	FVector Separation(AAgent* boid);
	FVector Alignment(AAgent* boid);
	void Limit(AAgent* boid);
	FVector Bound(AAgent* boid);

private:
	UWorld* World;
	bool initialized;
	TArray<class AAgent*> Agents;
};