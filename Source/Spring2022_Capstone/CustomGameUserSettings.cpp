// Created by Spring2022_Capstone team


#include "CustomGameUserSettings.h"

UCustomGameUserSettings::UCustomGameUserSettings()
{
    YSensitivity = 45;
    XSensitivity = 45;
}

UCustomGameUserSettings *UCustomGameUserSettings::GetCustomGameUserSettings()
{
    return Cast<UCustomGameUserSettings>(UGameUserSettings::GetGameUserSettings());
}
