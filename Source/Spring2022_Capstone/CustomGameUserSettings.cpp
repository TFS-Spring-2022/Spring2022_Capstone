// Created by Spring2022_Capstone team


#include "CustomGameUserSettings.h"

UCustomGameUserSettings::UCustomGameUserSettings()
{
    YSensitivity = 10;
    XSensitivity = 10;
}

UCustomGameUserSettings *UCustomGameUserSettings::GetCustomGameUserSettings()
{
    if (UGameUserSettings::GetGameUserSettings()){
        UE_LOG(LogTemp, Display, TEXT("HERE HERE 1"));
    }
    if (Cast<UCustomGameUserSettings>(UGameUserSettings::GetGameUserSettings())){
        UE_LOG(LogTemp, Display, TEXT("HERE HERE 2"));
    }
    return Cast<UCustomGameUserSettings>(UGameUserSettings::GetGameUserSettings());
}
