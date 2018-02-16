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

	//Limit Switches
	bool getElevatorBottom();

	//Gyro stuff
	int getGyroAngle();
	void resetGyro();

private:
ADXRS450_Gyro *gyro;
DigitalInput *elevatorBottom;

};

#endif /* SRC_SENSORS_H_ */
