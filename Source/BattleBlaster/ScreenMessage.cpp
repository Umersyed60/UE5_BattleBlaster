// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenMessage.h"

//Function To Set Widget UI Text Message
void UScreenMessage::SetMessageText(FString Message)
{
	FText MessageText = FText::FromString(Message);
	//Setting UI Text Message
	MessageTextBlock->SetText(MessageText);
}
