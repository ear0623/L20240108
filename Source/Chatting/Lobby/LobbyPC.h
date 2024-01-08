// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LobbyPC.generated.h"

class ULobbyWidgetBase;
/**
 * 
 */
UCLASS()
class CHATTING_API ALobbyPC : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category= "UI")
	TObjectPtr<ULobbyWidgetBase> LobbyWidgetObject;//�׳� �����͸� �����ϱ� ���� ue5���� ���� �����͹���

	//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")//blueprint�� �����ϰڴٸ�//
	//TSubclassOf<ULobbyWidgetBase> LobbyWidgetClass;//���� �� add to viewport 
	//Ŭ���� ��ü�� ����ϰ�, ���.
	UFUNCTION(Server,Unreliable,WithValidation)//reliable -- packing 100%�� ��ġ�ؾ���//���� ���� �ȹ���
	void C2S_SendMessage(const FString& InMessage);//client call

	bool C2S_SendMessage_Validate(const FString& InMessage);

	void C2S_SendMessage_Implementation(const FString& InMessage);//serverexcute

	UFUNCTION(Client,Reliable)//Ŭ���̾�Ʈ���� ���� �������� ����//������ ������ ����
	void S2C_SendMessage(const FString& InMessage);//server call

	void S2C_SendMessage_Implementation(const FString& InMessage);//serverexcute
};
