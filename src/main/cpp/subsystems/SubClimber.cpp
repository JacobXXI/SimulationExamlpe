// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubClimber.h"
#include <frc/smartdashboard/SmartDashboard.h>

SubClimber::SubClimber() {
    _ClimbMotor.SetConversionFactor(1.0 / gearRatio);
    _ClimbMotor.SetIdleMode(rev::CANSparkBase::IdleMode::kBrake);
    _ClimbMotor.SetPIDFF(P,I,D,F);
    _ClimbMotor.SetInverted(false);
}

// This method will be called once per scheduler run
void SubClimber::Periodic() {
    frc::SmartDashboard::PutData("Climber/Mech Display", &mech);
    frc::SmartDashboard::PutData("Climber/Motor", (wpi::Sendable*)&_ClimbMotor);
}

void SubClimber::SimulationPeriodic() {
    ElvSim.SetInputVoltage(_ClimbMotor.GetSimVoltage());
    ElvSim.Update(20_ms);
    _ClimbMotor.UpdateSimEncoder(DistanceToTurn(ElvSim.GetPosition()),DistanceToTurn(ElvSim.GetVelocity()));

    mechElevator->SetLength(ElvSim.GetPosition().value());
}

units::turn_t SubClimber::DistanceToTurn(units::meter_t distance) {
  return distance / WheelCir * 1_tr;
}

units::radians_per_second_t SubClimber::DistanceToTurn(units::meters_per_second_t distance) {
    return distance / WheelCir * 1_tr;
}

//Unti translation from climber motor rotations(turns) to meters
units::meter_t SubClimber::TurnToDistance(units::turn_t turn) {
  return turn.value() * WheelCir;
};

void SubClimber::StartClimber(double power) {
    power = std::clamp(power, -1.0, 1.0);
    _ClimbMotor.Set(power);
}

frc2::CommandPtr SubClimber::CmdStartClimber(double power) {
    return frc2::cmd::RunOnce([this, power] {
        StartClimber(power);
    });
}