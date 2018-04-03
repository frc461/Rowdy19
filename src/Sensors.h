/*
 * Sensors.h
 *
 *  Created on: Jan 24, 2018
 *      Author: Hank Krutulis - 461
 */

#ifndef SRC_SENSORS_H_
#define SRC_SENSORS_H_
#include <WPILib.h>
#include "Robot.h"


class Sensors {
public:
	Sensors();

	void lightUp();
	void lightDown();

	//Digital Switches
	bool getElevatorBottom();
	bool getIntakeButtonL();
	bool getIntakeButtonR();

	//Potentiometer
	double getWristAngle();

	//Gyro stuff
	int getGyroAngle();
	void resetGyro();

private:


ADXRS450_Gyro *gyro;
Potentiometer *wrist;
DigitalOutput *led;
DigitalInput *elevatorBottom;
DigitalInput *intakeButtonR;
DigitalInput *intakeButtonL;

};

#endif /* SRC_SENSORS_H_ */
