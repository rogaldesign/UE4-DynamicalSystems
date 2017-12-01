#include "NetVoice.h"
#include "DynamicalSystemsPrivatePCH.h"

UNetVoice::UNetVoice()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UNetVoice::BeginPlay()
{
	Super::BeginPlay();

	if (NetClient == NULL) {
		for (TActorIterator<ANetClient> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
			NetClient = *ActorItr;
			break;
		}
	}

	if (!IsValid(NetClient)) {
		return;
	}
    
    NetClient->RegisterVoice(this);
}

void UNetVoice::BeginDestroy()
{
	Super::BeginDestroy();
}

void UNetVoice::Say(uint8* Bytes, uint32 Count)
{
}

void UNetVoice::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}



