#include "FlockingManager.h"
#include "Agent.h"

#define AGENT_COUNT 25

void UFlockingManager::Init(UWorld* world, UStaticMeshComponent* mesh) {
    UE_LOG(LogTemp, Warning, TEXT("MANAGER INIT"));

    World = world;

    float incr = (PI * 2.f) / AGENT_COUNT;
    for (int i = 0; i < AGENT_COUNT; i++) {
        if (World != nullptr) {
            FRotator rotation = FRotator();

            FVector location = FVector();
            location.X = FMath::Sin(incr * i) * 500.f;
            location.Z = FMath::Cos(incr * i) * 500.f;

            AAgent* agent = World->SpawnActor<AAgent>(location, rotation);
            agent->Init(mesh, i);
            Agents.Add(agent);
        }
    }

    initialized = true;
}

void UFlockingManager::Flock() {
    for (int i = 0; i < AGENT_COUNT; i++) {
        AAgent* boid = Agents[i];

        FVector v1 = Cohesion(boid);
        FVector v2 = Separation(boid);
        FVector v3 = Alignment(boid);

        boid->Velocity = boid->Velocity + v1 + v2 + v3 + Bound(boid);
        Limit(boid);
    }
}

FVector UFlockingManager::Cohesion(AAgent* boid) {
    FVector pcenter;

    for (int i = 0; i < AGENT_COUNT; i++) {
        if (Agents[i] != boid) {
            pcenter = pcenter + Agents[i]->GetActorLocation();
        }
    }

    pcenter /= AGENT_COUNT;

    return (pcenter - boid->GetActorLocation()) / 25;
}

FVector UFlockingManager::Separation(AAgent* boid) {
    FVector c = FVector(0);

    for (int i = 0; i < AGENT_COUNT; i++) {
        if (Agents[i] != boid) {
            FVector vec = Agents[i]->GetActorLocation() - boid->GetActorLocation();
            if(vec.GetAbs().X < 25 && vec.GetAbs().Y < 25 && vec.GetAbs().Z < 25) {
                c = c - vec;
            }
        }
    }
    
    return c;
}

FVector UFlockingManager::Alignment(AAgent* boid) {
    FVector pvelocity;

    for (int i = 0; i < AGENT_COUNT; i++) {
        if (Agents[i] != boid) {
            pvelocity = pvelocity + boid->Velocity;
        }
    }

    pvelocity /= (AGENT_COUNT - 1);

    return (pvelocity - boid->Velocity) / 8;
}

void UFlockingManager::Limit(AAgent* boid) {
    float vlimit = 7.5;
    
    if (boid->Velocity.GetAbs().X > vlimit || boid->Velocity.GetAbs().Y > vlimit || boid->Velocity.GetAbs().Z > vlimit) {
        boid->Velocity = (boid->Velocity / boid->Velocity.GetAbs()) * vlimit;
    }
}

FVector UFlockingManager::Bound(AAgent* boid) {
    FVector v;

    if (boid->GetActorLocation().X < -750) {
        v.X = 10;
    }
    else if (boid->GetActorLocation().X > 750) {
        v.X = -10;
    }
    
    if (boid->GetActorLocation().Y < -750) {
        v.Y = 10;
    }
    else if (boid->GetActorLocation().Y > 750) {
        v.Y = -10;
    }

    if (boid->GetActorLocation().Z < -750) {
        v.Z = 10;
    }
    else if (boid->GetActorLocation().Z > 750) {
        v.Z = -10;
    }

    return v;
}