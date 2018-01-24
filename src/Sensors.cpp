/*
 * Sensors.cpp
 *
 *  Created on: Jan 24, 2018
 *      Author: hank
 */

#include <Sensors.h>
#include <WPILib.h>
#include "Robot.h"

Sensors::Sensors() {
	gyro = new ADXRS450_Gyro();
	leftDriveEncoder = new Encoder(LeftEncoderDIO1, LeftEncoderDIO2);
	rightDriveEncoder = new Encoer(RightEncoderDIO1, RightEncoderDIO2);
}

int Sensors::GetLeftEncoderDistance(){
	return leftDriveEncoder->GetDistance();
}

int Sensors::GetRightEncoderDistance(){
	return rightDriveEncoder->GetDistance();
}

int Sensors::GetGyroAngle(){
	return gyro->GetAngle();
}

int Sensors::GetElevatorEncoders(){}
