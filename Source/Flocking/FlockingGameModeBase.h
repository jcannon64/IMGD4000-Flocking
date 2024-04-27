

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FlockingManager.h"
#include "FlockingGameModeBase.generated.h"

UCLASS()
class FLOCKING_API AFlockingGameModeBase : public AGameModeBase
{
    GENERATED_BODY()
    AFlockingGameModeBase();

public:
    UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "2.5"))
    float Speed;

private:
    UPROPERTY(EditAnywhere)
    class UStaticMeshComponent* AgentMesh;

    UPROPERTY() UFlockingManager* Manager;

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
};