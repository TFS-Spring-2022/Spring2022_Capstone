// Created by Spring2022_Capstone team


#include "CustomGameUserSettings.h"

UCustomGameUserSettings::UCustomGameUserSettings()
{
    YSensitivity = 10;
    XSensitivity = 0;
}

UCustomGameUserSettings *UCustomGameUserSettings::GetCustomGameUserSettings()
{
    return Cast<UCustomGameUserSettings>(UGameUserSettings::GetGameUserSettings());
}
