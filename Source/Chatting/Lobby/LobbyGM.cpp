// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGM.h"
#include "LobbyGS.h"

void ALobbyGM::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	//Player Controller 숫자를 세어 총 인원을 계산,GameState 저장.

	ALobbyGS* GS = GetGameState<ALobbyGS>();
	if (GS)
	{
		GS->IncreasePlayerCount();
		GS->OnRep_PlayerCount();//Only server call
	}//넷트워크설정이 먼저.
}

void ALobbyGM::Logout(AController* Exiting)
{
	//Player Controller 숫자를 세어 총 인원을 계산, GameState 저장.
	ALobbyGS* GS = GetGameState<ALobbyGS>();
	if (GS)
	{
		GS->DecreasePlayerCount();
		GS->OnRep_PlayerCount();
	}
	//gamemode가 서버니까 확인할필요난 읎더

	Super::Logout(Exiting);
}

void ALobbyGM::BeginPlay()
{
	ALobbyGS* GS = GetGameState<ALobbyGS>();
	if (GS)
	{
		GS->OnRep_PlayerCount();
	}//게임모드에서 돌아가는 함수들은 서버꺼

	FTimerHandle LeftTimerHandle;
	//GetWorld()->GetTimerManager().SetTimer(LeftTimerHandle, FTimerDelegate::CreateLambda([&]() {if (GS)
	//{
	//	GS->LeftTime--;
	//	GS->S2A_UpdateLeftTime(GS->LeftTime);
	//}
	//}), 1.0f, true, -1.0f);//& 밖에 다갔다 씀.

	GetWorld()->GetTimerManager().SetTimer(LeftTimerHandle,this,&ALobbyGM::UpdateLeftTime, 1.0f, true, -1.0f);

}

void ALobbyGM::UpdateLeftTime()
{
	ALobbyGS* GS = GetGameState<ALobbyGS>();
	if (GS)
	{
		GS->LeftTime--;
		GS->S2A_UpdateLeftTime(GS->LeftTime);
	}
}
//replicateduing Or Netmulticast
//actor가 network의 최소단위
