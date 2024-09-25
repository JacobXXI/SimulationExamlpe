// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include "utilities/ICSparkMax.h"
#include <frc/simulation/DCMotorSim.h>
#include <frc2/command/Commands.h>

class SubShooter : public frc2::SubsystemBase {
 public:
  SubShooter();
  static SubShooter& GetInstance() {
    static SubShooter inst;
    return inst;
  }

  void Periodic() override;
  void SimulationPeriodic() override;

  void StartShooter(double power);
  frc2::CommandPtr CmdStartShooter(double power);

 private:
  ICSparkMax _flyWheelMotor {2, 30_A};
  frc::sim::DCMotorSim _flyWheelSim {frc::DCMotor::Falcon500(), 1, 0.005_kg_sq_m};

};
