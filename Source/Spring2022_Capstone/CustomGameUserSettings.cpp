// Created by Spring2022_Capstone team


#include "CustomGameUserSettings.h"

UCustomGameUserSettings::UCustomGameUserSettings()
{
    YSensitivity = 50;
    XSensitivity = 50;
}

UCustomGameUserSettings *UCustomGameUserSettings::GetCustomGameUserSettings()
{
    return Cast<UCustomGameUserSettings>(UGameUserSettings::GetGameUserSettings());
}
