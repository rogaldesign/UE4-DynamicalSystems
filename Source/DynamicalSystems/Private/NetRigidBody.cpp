#include "NetRigidBody.h"
#include "RigidBodyController.h"
#include "DynamicalSystemsPrivatePCH.h"

UNetRigidBody::UNetRigidBody()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UNetRigidBody::BeginPlay()
{
	Super::BeginPlay();
    
//AActor* Actor = GetOwner();
//if (IsValid(Actor)) {
//    TargetLocation = Actor->GetActorLocation();
//    UStaticMeshComponent* StaticMesh = Actor->FindComponentByClass<UStaticMeshComponent>();
//    if (StaticMesh) {
//        TargetLinearVelocity = StaticMesh->GetBodyInstance()->GetUnrealWorldVelocity();
//    }
//}

	AActor* Actor = GetOwner();
	TargetLocation = Actor->GetActorLocation();
	TargetRotation = Actor->GetActorRotation();
	URigidBodyController* PIDController = Actor->FindComponentByClass<URigidBodyController>();
	if (PIDController && NetOwner != NetClient->NetIndex) {
		PIDController->TargetLocation = TargetLocation;
		//PIDController->TargetRotation = TargetRotation;
	}
    
    NetClient->RegisterRigidBody(this);
}

void UNetRigidBody::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	AActor* Actor = GetOwner();
	URigidBodyController* PIDController = Actor->FindComponentByClass<URigidBodyController>();
	if (PIDController && NetOwner != NetClient->NetIndex && NetClient->NetIndex >= 0) {
		PIDController->Enabled = true;
		PIDController->TargetLocation = TargetLocation + TargetLinearVelocity * DeltaTime;
		//PIDController->TargetRotation = TargetRotation;
	}
	else if (PIDController) {
		PIDController->Enabled = false;
	}
}

