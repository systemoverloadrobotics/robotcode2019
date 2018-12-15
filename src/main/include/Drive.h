/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "Drive.h"
#include <boolean>
#include <string>
#include <iostream>
#include <SmartDashboard/SendableChooser.h>
#include <Drive/DifferentialDrive.h>
#include <IterativeRobot.h>
#include <Joystick.h>
#include <Spark.h>

using namespace frc;

class Robot : public frc::IterativeRobot {
  Joystick stick{1};
  Spark m_leftDrive{0};
  Spark m_rightDrive{1};
  Spark m_leftCannon{2};          //FIND MOTOR PIN
  Spark m_rightCannon{3};         //FIND MOTOR PIN
  Spark m_leftIntake{4};          //FIND MOTOR PIN
  Spark m_rightIntake{5};         //FIND MOTOR PIN
  Spark m_leftIntakeSUPPORT{6};   //FIND MOTOR PIN/NAME
  Spark m_rightIntakeSUPPORT{7};  //FIND MOTOR PIN/NAME
  DifferentialDrive m_Drive{m_leftDrive, m_rightDrive};
  
  public:
  void TeleopPeriodic() {
    double value1, value2, value3, value4, value5;
    boolean value1b, value2b, value3b, value4b, value5b, value6b, value7b, value8b, value9b, value10b;
    value1 = stick.GetRawAxis(1);
    value2 = stick.GetRawAxis(2);
    value3 = stick.GetRawAxis(3);
    value4 = stick.GetRawAxis(4);
    value5 = stick.GetRawAxis(5);

    value1b = stick.GetRawButton(1);
    value2b = stick.GetRawButton(2);
    value3b = stick.GetRawButton(3);
    value4b = stick.GetRawButton(4);
    value5b = stick.GetRawButton(5);
    value6b = stick.GetRawButton(6);
    value7b = stick.GetRawButton(7);
    value8b = stick.GetRawButton(8);
    value9b = stick.GetRawButton(9);
    value10b = stick.GetRawButton(10);


    m_Drive.ArcadeDrive(valueX, valueY);
    //m_cannonShoot.ArcadeDrive(valueThrottle);
  }
};
