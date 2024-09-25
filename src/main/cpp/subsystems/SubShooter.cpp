// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubShooter.h"
#include <frc/smartdashboard/SmartDashboard.h>

SubShooter::SubShooter() {
    _flyWheelMotor.SetPIDFF(1,0,0);
    frc::SmartDashboard::PutNumber("Shooter/Flywheel rotation (turns)", 0);
    frc::SmartDashboard::PutNumber("Shooter/Flywheel velocity (tps)", 0);
}

// This method will be called once per scheduler run
void SubShooter::Periodic() {
    frc::SmartDashboard::PutNumber("Shooter/Flywheel rotation (turns)",_flyWheelMotor.GetPosition().value());
    frc::SmartDashboard::PutNumber("Shooter/Flywheel velocity (tps)",_flyWheelMotor.GetVelocity().value());
}

void SubShooter::SimulationPeriodic() {
    _flyWheelSim.SetInputVoltage(_flyWheelMotor.GetSimVoltage());
    _flyWheelSim.Update(20_ms);
    _flyWheelMotor.UpdateSimEncoder(_flyWheelSim.GetAngularPosition(),_flyWheelSim.GetAngularVelocity());
}

void SubShooter::StartShooter(double power) {
    power = std::clamp(power, -1.0, 1.0);
    _flyWheelMotor.Set(power);
}

frc2::CommandPtr SubShooter::CmdStartShooter(double power) {
    return Run([this, power] {
        StartShooter(power);
    });
}