/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>
#include <iostream>
#include <thread>
#include <vector>
#include <frc/AnalogInput.h>
#include <frc/Compressor.h>
#include <frc/DoubleSolenoid.h>
#include <frc/Drive/DifferentialDrive.h>
#include <frc/TimedRobot.h>
#include <frc/Timer.h>
#include <frc/Joystick.h>
#include <frc/PowerDistributionPanel.h>
#include <frc/PWMVictorSPX.h>
#include <frc/Smartdashboard/SendableChooser.h>
#include <frc/SpeedControllerGroup.h>
#include <opencv2/core/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <wpi/raw_ostream.h>
#include <wpi/raw_ostream.h>
#include <cameraserver/CameraServer.h>

using namepace std;

class ImageProcess : public frc::TimedRobot {
    void makeGrid(cv::Mat img, int cellSize);
    cv::Mat makeGrid(char *fileName, char *result);
    void RobotInit();
    std::string getPutTextData(int count);
};

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
  static constexpr double turningSpeedFast = .7;
  static constexpr double turningSpeedSlow = .5;
  static constexpr double speedFast = 1;
  static constexpr double speedNormal = .7;
  static constexpr double speedSlow = .5;
  static constexpr double stall = -.2;
  static constexpr double upSpeedNormal = -.4;
  static constexpr double upSpeedFast = -.5;
  static constexpr double downSpeedNormal = -.04;
  static constexpr double downSpeedFast = -.03;
  //Analog PI (PWM)
  //frc::AnalogInput input{0};
  frc::Joystick fightStick{1};
  frc::Joystick flightStick{2};
  frc::Compressor compressor;
  frc::PWMVictorSPX m_frontLeft{0};
  frc::PWMVictorSPX m_backLeft{1};
  frc::PWMVictorSPX m_frontRight{2};
  frc::PWMVictorSPX m_backRight{3};
  frc::PWMVictorSPX m_leftIntake{4}; 
  frc::PWMVictorSPX m_rightIntake{5};
  frc::PWMVictorSPX m_forklift{6};
  frc::SpeedControllerGroup m_left{m_frontLeft, m_backLeft};
  frc::SpeedControllerGroup m_right{m_frontRight, m_backRight}; 
  frc::DifferentialDrive Drive{m_left, m_right};
  frc::DoubleSolenoid s_panelLauncherBottom{0, 1};
  frc::DoubleSolenoid s_panelLauncherTop{2, 3};
  frc::DoubleSolenoid s_HABfront{4, 5};
  frc::DoubleSolenoid s_HABback{6, 7};
};
