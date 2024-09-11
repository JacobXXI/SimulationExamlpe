// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubIntake.h"
#include <frc/smartdashboard/SmartDashboard.h>

SubIntake::SubIntake() {}

// This method will be called once per scheduler run
void SubIntake::Periodic() {
    frc::SmartDashboard::PutNumber("Intake/Power", _intakeMotor.Get());
}

frc2::CommandPtr SubIntake::On() {
    return frc2::cmd::RunOnce([this] {
        _intakeMotor.Set(1);
    });
}

frc2::CommandPtr SubIntake::Off() {
    return frc2::cmd::RunOnce([this] {
        _intakeMotor.Set(0);
    });
}