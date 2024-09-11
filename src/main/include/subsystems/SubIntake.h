// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc2/command/Commands.h>
#include <utilities/ICSparkMax.h>

class SubIntake : public frc2::SubsystemBase {
 public:
  SubIntake();

  static SubIntake& GetInstance() {
    static SubIntake inst;
    return inst;
  }

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

  frc2::CommandPtr On();
  frc2::CommandPtr Off();


 private:
  ICSparkMax _intakeMotor {2,30_A};
};
