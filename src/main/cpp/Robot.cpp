/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <frc/Joystick.h>
#include <frc/TimedRobot.h>
#include <frc/drive/DifferentialDrive.h>

#include "frc/WPILib.h"
#include "ctre/Phoenix.h"

/**
 * This is a demo program showing the use of the DifferentialDrive class.
 * Runs the motors with arcade steering.
 */
class Robot : public frc::TimedRobot {
	WPI_VictorSPX * rightFront = new WPI_VictorSPX(3);//ID needs to be set
	WPI_VictorSPX * leftFront = new WPI_VictorSPX(4);//ID needs to be set
  WPI_VictorSPX * rightBack = new WPI_VictorSPX(5);//ID needs to be set
  WPI_VictorSPX * leftBack = new WPI_VictorSPX(6);//ID needs to be set
  rightBack -> Follow(rightFront::PercentOutput);
  frc::DifferentialDrive m_robotDrive{*rightFront, *leftFront};
  frc::Joystick m_stick{0};

 public:
  void TeleopPeriodic() {
    // Drive with arcade style
    m_robotDrive.ArcadeDrive(m_stick.GetY(), m_stick.GetX());
  }
};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
