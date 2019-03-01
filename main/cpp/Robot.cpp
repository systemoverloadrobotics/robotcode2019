/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

//320x240 might help with frames per second, reddit user said they got around 20-30 fps instead of our ~4 fps

#include "Robot.h"

#include <iostream>

void Robot::RobotInit() {
  compressor.Stop ();
}

void Robot::RobotPeriodic() {
  cs::UsbCamera floorCamera = frc::CameraServer::GetInstance()->StartAutomaticCapture(0);
  cs::UsbCamera driverCamera = frc::CameraServer::GetInstance()->StartAutomaticCapture(1);
  driverCamera.SetResolution(320, 240);
  floorCamera.SetResolution(640, 480);
  cs::CvSink cvSink = frc::CameraServer::GetInstance()->GetVideo();
  cs::CvSource outputStream = frc::CameraServer::GetInstance()->PutVideo("Rectangle", 640, 480);
  cv::Mat mat;
  while (true) {
    if (cvSink.GrabFrame(mat) == 0) {
        outputStream.NotifyError(cvSink.GetError());
      }
      rectangle(mat, cv::Point(100, 100), cv::Point(400, 400), cv::Scalar(255, 255, 255), 5);
      outputStream.PutFrame(mat);
    }
}

void Robot::AutonomousInit() {
//NO AUTONOMOUS
}

void Robot::AutonomousPeriodic() { //Same code for both Auto and Teleop, can't find a way to continue from one to other so both modes have the same code
//Compressor
  if (fightStick.GetRawButton(8) == 1) {
    compressor.Start();
  } else {
    compressor.Stop();
  }
  
//Drive
  if (flightStick.GetRawButton(2) == 1) { //Slow
    Drive.CurvatureDrive(flightStick.GetRawAxis(1) * -1 * speedSlow, flightStick.GetRawAxis(2) * turningSpeedFast, flightStick.GetRawButton(1));
  } else if (flightStick.GetRawButton(12/*Will Change*/) == 1) { // Fast
    Drive.CurvatureDrive(flightStick.GetRawAxis(1) * -1 * speedFast, flightStick.GetRawAxis(2) * turningSpeedFast, flightStick.GetRawButton(1));
  } else { //Normal
    Drive.CurvatureDrive(flightStick.GetRawAxis(1) * -1 * speedNormal, flightStick.GetRawAxis(2) * turningSpeedSlow, flightStick.GetRawButton(1));
  }   
//HAB Lift(???)
  //Font
  if (flightStick.GetRawButton(7) == 1) {
    s_HABfront.Set(frc::DoubleSolenoid::kForward);
  } else if (flightStick.GetRawButton(7) == 0) {
    s_HABfront.Set(frc::DoubleSolenoid::kReverse);
  } else {
    s_HABfront.Set(frc::DoubleSolenoid::kOff);
  }
  //Back
  if (flightStick.GetRawButton(8) == 1) {
    s_HABback.Set(frc::DoubleSolenoid::kForward);
  } else if (flightStick.GetRawButton(8) == 0) {
    s_HABback.Set(frc::DoubleSolenoid::kReverse);
  } else {
    s_HABback.Set(frc::DoubleSolenoid::kOff);
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
    m_leftIntake.Set(.5);//+
    m_rightIntake.Set(-.5);
  } else if (fightStick.GetRawButton(3) == 1) {
    m_leftIntake.Set(-.5);
    m_rightIntake.Set(.5);
  } else {
    m_leftIntake.Set(0);
    m_rightIntake.Set(0);
  }

//Hatch Panel Launcher
  //They are set backwards if time is avaible would like to switch them around in both the code and wiring
  if (fightStick.GetRawButton(4) == 0) {
    s_panelLauncherBottom.Set(frc::DoubleSolenoid::kForward);
    s_panelLauncherTop.Set(frc::DoubleSolenoid::kForward);
  } else if (fightStick.GetRawButton(4) == 1) {
    s_panelLauncherBottom.Set(frc::DoubleSolenoid::kReverse);
    s_panelLauncherTop.Set(frc::DoubleSolenoid::kReverse);
  } else {
    s_panelLauncherBottom.Set(frc::DoubleSolenoid::kForward);
    s_panelLauncherTop.Set(frc::DoubleSolenoid::kForward);
  }
  //input.GetVoltage();
}

void Robot::TeleopInit() {
//Nothing that I can think of
}

void Robot::TeleopPeriodic() {
//Compressor
  if (fightStick.GetRawButton(8) == 1) {
    compressor.Start();
  } else {
    compressor.Stop();
  }
  
//Drive
  if (flightStick.GetRawButton(2) == 1) { //Slow
    Drive.CurvatureDrive(flightStick.GetRawAxis(1) * -1 * speedSlow, flightStick.GetRawAxis(2) * turningSpeedFast, flightStick.GetRawButton(1));
  } else if (flightStick.GetRawButton(12/*Will Change*/) == 1) { // Fast
    Drive.CurvatureDrive(flightStick.GetRawAxis(1) * -1 * speedFast, flightStick.GetRawAxis(2) * turningSpeedFast, flightStick.GetRawButton(1));
  } else { //Normal
    Drive.CurvatureDrive(flightStick.GetRawAxis(1) * -1 * speedNormal, flightStick.GetRawAxis(2) * turningSpeedSlow, flightStick.GetRawButton(1));
  }   
//HAB Lift(???)
  //Font
  if (flightStick.GetRawButton(7) == 1) {
    s_HABfront.Set(frc::DoubleSolenoid::kForward);
  } else if (flightStick.GetRawButton(7) == 0) {
    s_HABfront.Set(frc::DoubleSolenoid::kReverse);
  } else {
    s_HABfront.Set(frc::DoubleSolenoid::kOff);
  }
  //Back
  if (flightStick.GetRawButton(8) == 1) {
    s_HABback.Set(frc::DoubleSolenoid::kForward);
  } else if (flightStick.GetRawButton(8) == 0) {
    s_HABback.Set(frc::DoubleSolenoid::kReverse);
  } else {
    s_HABback.Set(frc::DoubleSolenoid::kOff);
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
    m_leftIntake.Set(.5);//+
    m_rightIntake.Set(-.5);
  } else if (fightStick.GetRawButton(3) == 1) {
    m_leftIntake.Set(-.5);
    m_rightIntake.Set(.5);
  } else {
    m_leftIntake.Set(0);
    m_rightIntake.Set(0);
  }

//Hatch Panel Launcher
  //They are set backwards if time is avaible would like to switch them around in both the code and wiring
  if (fightStick.GetRawButton(4) == 0) {
    s_panelLauncherBottom.Set(frc::DoubleSolenoid::kForward);
    s_panelLauncherTop.Set(frc::DoubleSolenoid::kForward);
  } else if (fightStick.GetRawButton(4) == 1) {
    s_panelLauncherBottom.Set(frc::DoubleSolenoid::kReverse);
    s_panelLauncherTop.Set(frc::DoubleSolenoid::kReverse);
  } else {
    s_panelLauncherBottom.Set(frc::DoubleSolenoid::kForward);
    s_panelLauncherTop.Set(frc::DoubleSolenoid::kForward);
  }
    //input.GetVoltage();
}

void Robot::TestPeriodic() {
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
