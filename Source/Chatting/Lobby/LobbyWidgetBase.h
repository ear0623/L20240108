// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyWidgetBase.generated.h"


class UTextBlock;
class UScrollBox;
class UEditableTextBox;
/**
 * 
 */
UCLASS()
class CHATTING_API ULobbyWidgetBase : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	UFUNCTION()
	void ProccessChanged(const FText& Text);
	UFUNCTION()
	void ProccessCommitted(const FText& Text, ETextCommit::Type CommitMethod);

	void UpdatePlayerCount(int32 InplayerCount);

	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category ="UI")
	TObjectPtr<UTextBlock> PlayerCountTextBox;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "UI")
	TObjectPtr<UScrollBox> ChatScrollBox;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "UI")
	TObjectPtr<UEditableTextBox>ChatInputTextBox;

	UFUNCTION(BlueprintCallable)
	void AddMessage(const FString& InMessge);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "UI")
	TObjectPtr<UTextBlock> LeftTimeTextBox;

	void UpdateLeftTime(int InLeftTime);


};
