// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "LobbyGS.generated.h"

/**
 * 
 */
UCLASS()
class CHATTING_API ALobbyGS : public AGameStateBase
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable)
	void IncreasePlayerCount();
	UFUNCTION(BlueprintCallable)
	void DecreasePlayerCount();

protected:
	UPROPERTY(ReplicatedUsing="OnRep_PlayerCount", BlueprintreadOnly, meta = (AllowprivateAccess = "true"))// 기능을 넣어준다 == 리스트업해준다.
	int32 PlayerCount;// Playercontroller 세는거 게임모드에 있다.

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	

public:
	int32 LeftTime = 60;

	UFUNCTION()
	void OnRep_PlayerCount();

	UFUNCTION(NetMulticast,Unreliable)//성능에 막대한 지장
	void S2A_UpdateLeftTime(int InLeftTime);// cakk server
	void S2A_UpdateLeftTime_Implementation(int InLeftTime);// execute all clients//어디서 실행되는지 알아야
};
