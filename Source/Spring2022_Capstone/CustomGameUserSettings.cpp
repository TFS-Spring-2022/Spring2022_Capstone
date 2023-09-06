// Created by Spring2022_Capstone team


#include "CustomGameUserSettings.h"

UCustomGameUserSettings::UCustomGameUserSettings()
{
    YSensitivity = 0;
    XSensitivity = 0;
}

UCustomGameUserSettings *UCustomGameUserSettings::GetBetterGameUserSettings()
{
    return Cast<UCustomGameUserSettings>(UGameUserSettings::GetGameUserSettings());
}
