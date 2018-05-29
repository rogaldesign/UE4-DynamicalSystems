#pragma once

#include "CoreMinimal.h"
#include "NetClient.h"
#include "Runtime/Engine/Classes/Components/ActorComponent.h"
#include "NetRigidBody.generated.h"

UCLASS( ClassGroup=(DynamicalSystems), meta=(BlueprintSpawnableComponent) )
class DYNAMICALSYSTEMS_API UNetRigidBody : public UActorComponent
{
	GENERATED_BODY()

public:

	UNetRigidBody();

	virtual void BeginPlay() override;
	
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetRigidBody")
    ANetClient* NetClient = NULL;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetRigidBody")
    int NetID = 0;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetRigidBody")
    int NetOwner = 0;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetRigidBody")
    bool Driving = false;
    
    bool SyncTarget = false;
    FVector TargetLocation;
    FVector TargetLinearVelocity;
	FRotator TargetRotation;
	FVector TargetAngularVelocity;
    
private:
    
};

