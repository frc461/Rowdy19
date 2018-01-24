/*
 * Sensors.h
 *
 *  Created on: Jan 24, 2018
 *      Author: hank
 */

#ifndef SRC_SENSORS_H_
#define SRC_SENSORS_H_
#include <WPILib.h>
#include "Robot.h"

class Sensors {
public:
	Sensors();
	int GetLeftEncoderDistance();
	int GetRightEncoderDistance();
	int GetGyroAngle();
	int GetElevatorEncoders();

private:
ADXRS450_Gyro *gyro;
Encoder *leftDriveEncoder;
Encoder *rightDriveEncoder;
};

#endif /* SRC_SENSORS_H_ */
