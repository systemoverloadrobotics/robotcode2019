/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#define _USE_MATH_DEFINES

#include <cmath>
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
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/SpeedControllerGroup.h>
#include <opencv2/core/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <wpi/raw_ostream.h>
#include <wpi/raw_ostream.h>
#include <cameraserver/CameraServer.h>

using namespace std;
using namespace frc;
using namespace cv;
using namespace cs;

class Robot : public frc::TimedRobot {
 /*double acceleration (double input) {
   double V;
   V = input / 2 * sin(((2 * M_PI) / 6) * timer.Get() - M_PI_2) + input / 2;
   return V;
 }*/
 
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

 private:
  AnalogInput pi{0};
  Joystick fightStick{2};
  Joystick flightStick{1};
  Compressor compressor;
  Timer timer;
  PWMVictorSPX m_frontLeft{0};
  PWMVictorSPX m_backLeft{1};
  PWMVictorSPX m_frontRight{2};
  PWMVictorSPX m_backRight{3};
  PWMVictorSPX m_leftIntake{4}; 
  PWMVictorSPX m_rightIntake{5};
  PWMVictorSPX m_forklift{6};
  SpeedControllerGroup m_left{m_frontLeft, m_backLeft};
  SpeedControllerGroup m_right{m_frontRight, m_backRight}; 
  DifferentialDrive Drive{m_left, m_right};
  DoubleSolenoid s_panelLauncherBottom{0, 1};
  DoubleSolenoid s_panelLauncherTop{2, 3};
  DoubleSolenoid s_HABfront{4, 5};
  DoubleSolenoid s_HABback{6, 7};
};
