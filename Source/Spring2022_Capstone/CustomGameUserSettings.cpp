// Created by Spring2022_Capstone team


#include "CustomGameUserSettings.h"

UCustomGameUserSettings::UCustomGameUserSettings()
{
    YSensitivity = 45;
    XSensitivity = 45;

    MasterVolumeValue = 0.5f;
    SFXVolumeValue = 1.f;
    MusicVolumeValue = 1.f;
    VoiceVolumeValue = 1.f;
}

UCustomGameUserSettings *UCustomGameUserSettings::GetCustomGameUserSettings()
{
    return Cast<UCustomGameUserSettings>(UGameUserSettings::GetGameUserSettings());
}
