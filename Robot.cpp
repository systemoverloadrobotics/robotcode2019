/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
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

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/SpeedControllerGroup.h>
#include <opencv2/core/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <wpi/raw_ostream.h>
#include <wpi/raw_ostream.h>

#include "ctre/phoenix/motorcontrol/FollowerType.h" 
#include "frc/WPILib.h"
#include "ctre/Phoenix.h"
#include <frc/SpeedController.h>

#include <frc/Encoder.h>

using namespace std;
using namespace frc;
using namespace cv;
using namespace ctre;
using namespace can;
using namespace lowlevel;


/**
 * This sample program shows how to control a motor using a joystick. In the
 * operator control part of the program, the joystick is read and the value is
 * written to the motor.
 *
 * Joystick analog values range from -1 to 1 and speed controller inputs as
 * range from -1 to 1 making it easy to work together.
 */
class Robot : public frc::TimedRobot {
 public:
  void RobotInit() {
    forklift.ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0);
    forklift.Config_kF(0, 0.0);//Need to set PID and maybe F
		forklift.Config_kP(0, 0.1);
		forklift.Config_kI(0, 0.0);
		forklift.Config_kD(0, 0.0);
    forklift.SetSensorPhase(false);//VERIFY

    forklift.SetSelectedSensorPosition(forklift.GetSelectedSensorPosition(0), 0);//I think this captures that starting point and whill base all changes to postion off of this point 
  }
  
  void TeleopInit() {

  }
  void TeleopPeriodic() override { 
    if (joystick.GetRawButton() == 1) {
     forklift.Set(ControlMode::Position, heightOne * 4096);//4096 is the number of ticks counted in a full rotaion of the encoder, 
    } else if (joystick.GetRawButton() == 1) {
      forklift.Set(ControlMode::Position, heightTwo * 4096);
    } else if (joystick.GetRawButton() == 1) {
      forklift.Set(ControlMode::Position, heightThree * 4096);
    } else {
      forklift.Set(ControlMode::Position,);
    }
  }

 private:
  Faults faults = Faults();
  Joystick joystick{0};
  WPI_VictorSPX forklift{5};//NEED TO SET REAL CAN ID

  int heightOne = 1;
  int heightTwo = 2;
  int heightThree = 3;
};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
