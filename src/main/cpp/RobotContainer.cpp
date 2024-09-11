// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"
#include <frc2/command/Commands.h>
#include "subsystems/SubShooter.h"
#include "subsystems/SubIntake.h"

RobotContainer::RobotContainer() {
  ConfigureBindings();
}

void RobotContainer::ConfigureBindings() {
  _mainController.X().OnTrue(SubIntake::GetInstance().On());
  _mainController.Y().OnTrue(SubIntake::GetInstance().Off());
  // _mainController.X().OnTrue(SubShooter::GetInstance().CmdStartShooter(1));
  // _mainController.Y().OnTrue(SubShooter::GetInstance().CmdStartShooter(0));
  // _mainController.A().OnTrue(SubShooter::GetInstance().CmdStartShooter(-1));
}

frc2::CommandPtr RobotContainer::GetAutonomousCommand() {
  return frc2::cmd::Print("No autonomous command configured");
}
