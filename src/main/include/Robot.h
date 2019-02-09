/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

 private:
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;

   //Declartions
  frc::Joystick gamePad{0};
  frc::Timer timer;
  frc::Encoder encoder1{0, 1};
  frc::LiveWindow& m_lw = *frc::LiveWindow::GetInstance();

  //Motors
  //Drivebase
  frc::PWMVictorSPX m_frontLeft{0};
  frc::PWMVictorSPX m_backLeft{1};
  frc::PWMVictorSPX m_frontRight{2};
  frc::PWMVictorSPX m_backRight{3};
  //HAB Lift
  frc::PWMVictorSPX m_frontLift{4};
  frc::PWMVictorSPX m_backLift{5};
  //Elevator Lift
  frc::PWMVictorSPX m_firstLayer{6}; // This may be 1 or 2 motors, not yet decided, set for 2 motors
  frc::PWMVictorSPX m_secondLayer{7}; 
  //BAG Motor Ball Thinging
  frc::PWMVictorSPX m_leftWheel{8};
  frc::PWMVictorSPX m_rightWheel{9};
  //Groups
  //Drivebase
  frc::SpeedControllerGroup m_left{m_frontLeft, m_backLeft};
  frc::SpeedControllerGroup m_right{m_frontRight, m_backRight}; 
  frc::SpeedControllerGroup m_ball{m_leftWheel, m_rightWheel};
  //Setting Drive
  frc::DifferentialDrive Drive{m_left, m_right};

  //Pneumatics/Solenoids
  //Hatch Panel Grabber(trying both on one solenoid)
  frc::DoubleSolenoid s_panelGrabber{1, 2};
  //Hatch Panel Launcher(trying 3 on one solenoid)
  frc::DoubleSolenoid s_panelLauncher{3, 4};
  //Hatch Panel Grabber F/B Setters
  static constexpr int panelGrabberForward = 1;
  static constexpr int panelGrabberReverse = 2;
  //Hatch Panel Launcher F/B Setters
  static constexpr int panelLauncherForward = 3;
  static constexpr int panelLauncherReverse = 4;
};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
};
