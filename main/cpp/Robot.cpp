/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

//320x240 might help with frames per second, reddit user said they got around 20-30 fps instead of our ~4 fps

#include "Robot.h"


void Robot::RobotInit() {
  compressor.Stop ();
  timer.Start();
}

void Robot::RobotPeriodic() {
//Vision
  UsbCamera floorCamera = CameraServer::GetInstance()->StartAutomaticCapture(0);
  UsbCamera driverCamera = CameraServer::GetInstance()->StartAutomaticCapture(1);
  driverCamera.SetResolution(320, 240);
  floorCamera.SetResolution(640, 480);
  //The rest of these do not name a specific camera need to fix that
  CvSink cvSink = CameraServer::GetInstance()->GetVideo();
  CvSource outputStream = CameraServer::GetInstance()->PutVideo("Rectangle", 640, 480);
  Mat mat;
  while (true) {
    if (cvSink.GrabFrame(mat) == 0) {
        outputStream.NotifyError(cvSink.GetError());
      }
      rectangle(mat, Point(100, 100), Point(400, 400), Scalar(255, 255, 255), 5);
      outputStream.PutFrame(mat);
    }

//Compressor
  if (fightStick.GetRawButton(8) == 1) {
    compressor.Start();
  } else {
    compressor.Stop();
  }
  
//Drive
  if (flightStick.GetRawButton(2) == 1) { //Slow
    if (flightStick.GetRawAxis(1) > 0 || flightStick.GetRawAxis(1) < 0) {
      if (0<timer.Get()<(f/2)) {
        Drive.CurvatureDrive(flightStick.GetRawAxis(1) / 2  *sin((((2 * M_PI) / f) * timer.Get() - M_PI_2) + flightStick.GetRawAxis(1) / 2) * -1 * speedSlow, flightStick.GetRawAxis(2) * turningSpeedSlow, flightStick.GetRawButton(1));
      } else {
        Drive.CurvatureDrive(flightStick.GetRawAxis(1) * -1 * speedSlow, flightStick.GetRawAxis(2) * turningSpeedSlow, flightStick.GetRawButton(1));
      }
    } else {
      timer.Reset();
    }
  } else if (flightStick.GetRawButton(11/*Will Change*/) == 1) { // Fast
    if (flightStick.GetRawAxis(1) > 0 || flightStick.GetRawAxis(1) < 0) {
      if (0<timer.Get()<(f/2)) {
        Drive.CurvatureDrive(flightStick.GetRawAxis(1)/2*sin((((2 * M_PI)/f)*timer.Get() - M_PI_2)+flightStick.GetRawAxis(1)/2) * -1 * speedFast, flightStick.GetRawAxis(2) * turningSpeedFast, flightStick.GetRawButton(1));
      } else {
        Drive.CurvatureDrive(flightStick.GetRawAxis(1) * -1 * speedFast, flightStick.GetRawAxis(2) * turningSpeedFast, flightStick.GetRawButton(1));
      }
    } else {
      timer.Reset();
    }
  } else { //Normal
    if (flightStick.GetRawAxis(1) > 0 || flightStick.GetRawAxis(1) < 0) {
      if (0<timer.Get()<(f/2)) {
        Drive.CurvatureDrive(flightStick.GetRawAxis(1)/2*sin((((2 * M_PI)/f)*timer.Get() - M_PI_2)+flightStick.GetRawAxis(1)/2) * -1 * speedNormal, flightStick.GetRawAxis(2) * turningSpeedSlow, flightStick.GetRawButton(1));
      } else {
        Drive.CurvatureDrive(flightStick.GetRawAxis(1) * -1 * speedNormal, flightStick.GetRawAxis(2) * turningSpeedSlow, flightStick.GetRawButton(1));
      }
    } else {
      timer.Reset();
    }
  }   
//HAB Lift(???)
  //Font
  if (flightStick.GetRawButton(7) == 1) {
    s_HABfront.Set(DoubleSolenoid::kForward);
  } else if (flightStick.GetRawButton(7) == 0) {
    s_HABfront.Set(DoubleSolenoid::kReverse);
  } else {
    s_HABfront.Set(DoubleSolenoid::kOff);
  }
  //Back
  if (flightStick.GetRawButton(8) == 1) {
    s_HABback.Set(DoubleSolenoid::kForward);
  } else if (flightStick.GetRawButton(8) == 0) {
    s_HABback.Set(DoubleSolenoid::kReverse);
  } else {
    s_HABback.Set(DoubleSolenoid::kOff);
  }

//Forklift Thomas special clutch idea for forklift
    //POV is 0=UP 90=Right 180=Down 270=Left and 45 for all the angles
    //.GetPOV("0") is the number for the POV system things switch
  if (fightStick.GetPOV(0) == 315) { //Up
    if (fightStick.GetRawButton(5) == 1) {
      m_forklift.Set(upSpeedFast);
    } else {
      m_forklift.Set(upSpeedNormal);
    }
  } else if (fightStick.GetPOV(0) == 225) { //Down
    if (fightStick.GetRawButton(5) == 1) {
      m_forklift.Set(downSpeedFast);
    } else {
      m_forklift.Set(downSpeedNormal);
    } 
  } else if (fightStick.GetPOV(0) == 270) { //Stall
    m_forklift.Set(stall);
  } else {
    m_forklift.Set(0);
  }
     
//Ball Intake
  if (fightStick.GetRawButton(1) == 1) {
    m_leftIntake.Set(flywheelIntake);//+
    m_rightIntake.Set(-1 * flywheelIntake);
  } else if (fightStick.GetRawButton(3) == 1) {
    m_leftIntake.Set(-1 * flywheelOutake);
    m_rightIntake.Set(flywheelOutake);
  } else {
    m_leftIntake.Set(0);
    m_rightIntake.Set(0);
  }

//Hatch Panel Launcher
  //They are set backwards if timerr is avaible would like to switch them around in both the code and wiring
  if (fightStick.GetRawButton(4) == 0) {
    s_panelLauncherBottom.Set(DoubleSolenoid::kForward);
    s_panelLauncherTop.Set(DoubleSolenoid::kForward);
  } else if (fightStick.GetRawButton(4) == 1) {
    s_panelLauncherBottom.Set(DoubleSolenoid::kReverse);
    s_panelLauncherTop.Set(DoubleSolenoid::kReverse);
  } else {
    s_panelLauncherBottom.Set(DoubleSolenoid::kForward);
    s_panelLauncherTop.Set(DoubleSolenoid::kForward);
  }
  SmartDashboard::PutNumber("Pi Value", pi.GetVoltage());
  //Add delay
}

void Robot::AutonomousInit() {
//NO AUTONOMOUS
}

void Robot::AutonomousPeriodic() {
//Nothing
}

void Robot::TeleopInit() {
//Nothing
}

void Robot::TeleopPeriodic() {
//Nothing
}

void Robot::TestPeriodic() {
//Nothing
}

#ifndef RUNNING_FRC_TESTS
int main() { return StartRobot<Robot>(); }
#endif
