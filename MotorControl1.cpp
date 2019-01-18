#include <frc/Joystick.h>
#include <frc/PWMVictorSPX.h>
#include <frc/TimedRobot.h>
#include <iostream>

// The above libraries were included in the example, so I put them in with the addition of iostream.
// Below is the new motor control class

class MotorControl : public frc::chaosControl {

public:

//This function sets what the motor is doing 

void MotorStart() {

DifferentialDrive.Set(m_stick.GetRawAxis(1))

//I am getting the value of the Y axis on the left stick
//I forgot what it was called so m_stick is a placeholder name

double AB = m_stick.GetRawXAxis(1)

//for easier use I set the value I called earlier to AB

if(AB > 0 && AB < 1){

//If the sick isnt tilted all the way forward, it runs at 25% speed

victorSRX.Set(.25);
}

else if (AB = 1){

//If the stick is all the way forward, it runs at half. I was told to set a limit to avoid a brownout,
//and I dont know how powerful the motorsare

victorSRX.SET(.5)
}

else if (AB < 0 && AB > -1){

//If the stick is down it runs at 25% speed backwards

victorSRX.SET(-.25)

}

else if (AB = -1){

//If the stick is all the way back it runs at 50% backwards

victorSRX.Set(-.5)
}

else {

//no input means the motor is idle
   
victorSRX.set(0)
}

}
