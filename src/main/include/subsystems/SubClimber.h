// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/simulation/ElevatorSim.h>
#include <frc/system/plant/DCMotor.h>
#include <frc/smartdashboard/Mechanism2d.h>
#include <frc/smartdashboard/MechanismRoot2d.h>
#include <frc/smartdashboard/MechanismLigament2d.h>
#include <frc2/command/Commands.h>
#include <numbers>
#include "Utilities/ICSparkMax.h"

class SubClimber : public frc2::SubsystemBase {
 public:
  SubClimber();

  static SubClimber& GetInstance() {
    static SubClimber inst;
    return inst; 
  }

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;
  void SimulationPeriodic() override;

  void StartClimber(double power);

  frc2::CommandPtr CmdStartClimber(double power);

  units::turn_t DistanceToTurn(units::meter_t distance);
  units::radians_per_second_t DistanceToTurn(units::meters_per_second_t distance);
  units::meter_t TurnToDistance(units::turn_t turn);

 private:

  ICSparkMax _ClimbMotor{7, 60_A};

  static constexpr double gearRatio = 45;

  static constexpr double P = 0.5, I = 0.0, D = 0.0, F = 0;

  static constexpr units::meter_t WheelCir = 0.157_m;

  static constexpr units::meter_t BaseHeight = 0.0_m;

  static constexpr units::meter_t TopHeight = 1_m;

  frc::sim::ElevatorSim ElvSim{frc::DCMotor::NEO(), gearRatio, 100_kg, (WheelCir/std::numbers::pi)/2, BaseHeight, TopHeight, true, BaseHeight};

  frc::Mechanism2d mech{4, 4};
  frc::MechanismRoot2d* mechRoot = mech.GetRoot("Climber", 2, 1);
  frc::MechanismLigament2d* mechElevator =
      mechRoot->Append<frc::MechanismLigament2d>("Elevator", 1, 90_deg);
};
