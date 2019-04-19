/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

//320x240 might help with frames per second, reddit user said they got around 20-30 fps instead of our ~4 fps

bool isPressed = false;
#include "Robot.h"

void Robot::RobotInit() {
  UsbCamera front = CameraServer::GetInstance()->StartAutomaticCapture(0);
  CameraServer::GetInstance()->GetVideo();
  //CameraServer::GetInstance()->SetSize(1);
  front.SetResolution(100,200);
  compressor.Stop();
  timer.Start();
}

void Robot::RobotPeriodic() {
  if (fightStick.GetRawButton(8) == 1) {
    compressor.Start();
  } else {
    compressor.Stop();
  }
//Vision

//Drive
  /*if (flightStick.GetRawButton(2) == 1) { //Slow
        Drive.CurvatureDrive(flightStick.GetRawAxis(1) * -1 * .5, flightStick.GetRawAxis(0) * .5, flightStick.GetRawButton(1));
  } else if (flightStick.GetRawButton(11) == 1) { // Fast
      Drive.CurvatureDrive(flightStick.GetRawAxis(1) * -1, flightStick.GetRawAxis(0) * .7, flightStick.GetRawButton(1));
  } else { //Normal
      Drive.CurvatureDrive(flightStick.GetRawAxis(1) * -1 * .7, flightStick.GetRawAxis(0) * .5, flightStick.GetRawButton(1));
    }
  /*if (flightStick.GetRawButton(2) == 1) { //Slow
    if (flightStick.GetRawAxis(1) > 0 || flightStick.GetRawAxis(1) < 0) {
      if (timer.Get()>0 && timer.Get()<3) {
        Drive.CurvatureDrive(acceleration(flightStick.GetRawAxis(1)) * -.3, flightStick.GetRawAxis(0) * .3, flightStick.GetRawButton(1));
      } else {
        Drive.CurvatureDrive(flightStick.GetRawAxis(1) * -.3, flightStick.GetRawAxis(3) * .3, flightStick.GetRawButton(1));
      }
    } else {
      timer.Reset();
    }
  } else if (flightStick.GetRawButton(11) == 1) { // Fast
    if (flightStick.GetRawAxis(1) > 0 || flightStick.GetRawAxis(1) < 0) {
      if (timer.Get()>0 && timer.Get()<3) {
        Drive.CurvatureDrive(acceleration(flightStick.GetRawAxis(1)) * -1, flightStick.GetRawAxis(0) * 1, flightStick.GetRawButton(1));
      } else {
        Drive.CurvatureDrive(flightStick.GetRawAxis(1) * -1, flightStick.GetRawAxis(0) * 1, flightStick.GetRawButton(1));
      }
    } else {
      timer.Reset();
    }
  } else { //Normal
    
    /*if (flightStick.GetRawAxis(0) > 0 || flightStick.GetRawAxis(0) < 0) {
      Drive.CurvatureDrive(flightStick.GetRawAxis(1) * 0, flightStick.GetRawAxis(0) * .5, flightStick.GetRawButton(1));
    }*/
    /*if (flightStick.GetRawAxis(1) > 0 || flightStick.GetRawAxis(1) < 0) {
      if (timer.Get()>0 && timer.Get()<3) {
        Drive.CurvatureDrive(acceleration(flightStick.GetRawAxis(1)) * -.7, flightStick.GetRawAxis(0) * .5, flightStick.GetRawButton(1));
      } else {
        Drive.CurvatureDrive(flightStick.GetRawAxis(1) * -.7, flightStick.GetRawAxis(0) * .5, flightStick.GetRawButton(1));
      }
    } else {
      timer.Reset();
    }
  }*/
  if (flightStick.GetRawButton(1) == 1) {
    Drive.ArcadeDrive(flightStick.GetRawAxis(1) * -1, flightStick.GetRawAxis(0) * 1);
  } else {
    Drive.ArcadeDrive(flightStick.GetRawAxis(1) * -.7, flightStick.GetRawAxis(0) * .7);
  }
/*Forklift Auto
  if (fightStick.GetRawButton(X) == 1) { //change here lmao loser
    for(int i; i > time.Get(10)
  } else {
  } */

//timer.HasPeriodPassed(5)
  
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
    if (fightStick.GetRawButton(6) == 1) {
      if (fightStick.GetPOV(0) == 0) {
        if (fightStick.GetRawButton(5) == 1) {
          m_forklift.Set(-.5);
        } else if (fightStick.GetRawButton(5) == 0) {
          m_forklift.Set(-.4);
        } else {
          m_forklift.Set(-.4);
        }
      } else if (fightStick.GetPOV(0) == 180) {
        if (fightStick.GetRawButton(5) == 1) {
          m_forklift.Set(-.03);
        } else if (fightStick.GetRawButton(5) == 0) {
          m_forklift.Set(-.04);//.005 is too small
        } else {
          m_forklift.Set(-.04);
        } 
      } else {
          m_forklift.Set(-.2);
        }
      } else {
        m_forklift.Set(0);
      }
  /*if (fightStick.GetPOV(0) == 315) { //Up
    if (fightStick.GetRawButton(5) == 1) {
      m_forklift.Set(-.4);
    } else {
      m_forklift.Set(1);
      //-.4
    }
  } else if (fightStick.GetPOV(0) == 225) { //Down
    if (fightStick.GetRawButton(5) == 1) {
      m_forklift.Set(-.03);
    } else {
      m_forklift.Set(1);
      //-.04
    } 
  } else if (fightStick.GetPOV(0) == 270) { //-.2
    m_forklift.Set(-.2);
  } else {
    m_forklift.Set(0);
  }*/
     
//Ball Intake
  if((fightStick.GetRawButton(1) == 1) && (fightStick.GetRawButton(X) == 1)) {//determine what x is
    m_leftIntake.Set(-1); //if inttake is fast, switch right and left intake with each other
    m_rightIntake.Set(1);
  } else if (fightStick.GetRawButton(1) == 1) {
    m_leftIntake.Set(.5);//+
    m_rightIntake.Set(-.5);
  } else if (fightStick.GetRawButton(3) == 1) {
    m_leftIntake.Set(-.5);
    m_rightIntake.Set(.5);
  } else {
    m_leftIntake.Set(0);
    m_rightIntake.Set(0);
  }
// defense system
  if(fightStick.GetRawAxis(2) == 1)
  {
    for(int i = 0; i < kdnf; i++)
    {
      
    }
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
  //Add delay and I do not know if this will display the PI value
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
