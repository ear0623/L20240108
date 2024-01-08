// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGS.h"
#include "Net/UnrealNetwork.h"
#include "LobbyPC.h"
#include "Kismet/GameplayStatics.h"
#include "LobbyWidgetBase.h"

void ALobbyGS::IncreasePlayerCount()
{
	PlayerCount++;
	UE_LOG(LogTemp, Warning, TEXT("%d"), PlayerCount);
}

void ALobbyGS::DecreasePlayerCount()
{
	PlayerCount--;
	UE_LOG(LogTemp, Warning, TEXT("%d"), PlayerCount);
}

//server 빼고 실행 c++에서는//서버에선 또 불러올필욘 없으니까//메모리값이 바뀌여도 nettowrk는 모름
void ALobbyGS::OnRep_PlayerCount()
{
	ALobbyPC* PC=Cast<ALobbyPC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC&& PC->LobbyWidgetObject)
	{
		PC->LobbyWidgetObject->UpdatePlayerCount(PlayerCount);
	}
}

void ALobbyGS::S2A_UpdateLeftTime_Implementation(int InLeftTime)
{
	LeftTime = InLeftTime;
	ALobbyPC* PC = Cast<ALobbyPC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC && PC->LobbyWidgetObject)
	{
		PC->LobbyWidgetObject->UpdateLeftTime(LeftTime);
	}
}

void ALobbyGS::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALobbyGS, PlayerCount);//조건도 있으니 찾아보자.
	//DOREPLIFETIME_CONDITION(ALobbyGS, PlayerCount,COND_InitialOnly) -> 조건입력해서 넣을 수 있ㅇ므
}
