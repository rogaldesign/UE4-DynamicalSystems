// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "DynamicalSystemsSettings.generated.h"

USTRUCT(BlueprintType)
struct FNetClientSettings {
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Server;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString MumbleServer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString AudioDevice;
};
/**
 * 
 */
UCLASS(config = "DynamicalSystems", defaultconfig)
class DYNAMICALSYSTEMS_API UDynamicalSystemsSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	UDynamicalSystemsSettings() {
		this->CurrentSettings = this->GetEnvSetting();
	}
	~UDynamicalSystemsSettings() {}
private:
	static UDynamicalSystemsSettings* Get() {
		return GetMutableDefault<UDynamicalSystemsSettings>();
	}
public:
	UFUNCTION(BlueprintCallable,BlueprintPure)
	static UDynamicalSystemsSettings* GetDynamicalSettings() {
		return Get();
	}
public:

	UPROPERTY(config, EditAnywhere, Category = Dynamical)
		FName CurrentEnvironment;

	UPROPERTY(config, EditAnywhere, Category = Dynamical)
		TMap<FName, FNetClientSettings> Environments;

	UFUNCTION(BlueprintGetter)
		FNetClientSettings GetEnvSetting() {

		if (!Environments.Contains(CurrentEnvironment)) {
			return FNetClientSettings();
		}
		return  *Environments.Find(CurrentEnvironment);
	}
	UPROPERTY(config,VisibleAnywhere, Category = Dynamical, BlueprintGetter = GetEnvSetting)
		FNetClientSettings CurrentSettings;

	UPROPERTY(config, EditAnywhere, Category = Dynamical)
		float PingTimeout = 1.0f;
#if WITH_EDITOR
	void PostEditChangeProperty(struct FPropertyChangedEvent& e)
	{
		FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;
		if (PropertyName == GET_MEMBER_NAME_CHECKED(UDynamicalSystemsSettings, CurrentEnvironment))
		{
			CurrentSettings = GetEnvSetting();
		}
		Super::PostEditChangeProperty(e);
	}
#endif
};
	