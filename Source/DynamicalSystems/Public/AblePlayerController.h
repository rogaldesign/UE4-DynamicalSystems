// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreUObject.h"
#include "GameplayTagContainer.h"
#include "GameplayTagAssetInterface.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/PlayerController.h"
#include "AblePlayerController.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class DYNAMICALSYSTEMS_API AAblePlayerController : public APlayerController, public IGameplayTagAssetInterface
{
	GENERATED_BODY()
	
public:
	AAblePlayerController();
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override { TagContainer = GameplayTagContainer; return; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayTags")
		FGameplayTagContainer GameplayTagContainer;
	UFUNCTION(BlueprintCallable, Category = "MIDI|Listener|GameplayTags")
		virtual bool AddGameplayTag(const FGameplayTag TagToCheck) {
		FGameplayTagContainer cnt;
		GetOwnedGameplayTags(cnt);
		if (HasMatchingGameplayTag(TagToCheck)) return false;
		GameplayTagContainer.AddTag(TagToCheck);
		return true;
	}
	UFUNCTION(BlueprintCallable, Category = "MIDI|Listener|GameplayTags")
		virtual bool RemoveGameplayTag(FGameplayTag TagToCheck) {
		FGameplayTagContainer cnt;
		GetOwnedGameplayTags(cnt);
		return GameplayTagContainer.RemoveTag(TagToCheck);
	}
};
