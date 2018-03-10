/*
 * Sensors.cpp
 *
 *  Created on: Jan 24, 2018
 *      Author: Hank Krutulis - 461
 */

#include <Sensors.h>
#include <WPILib.h>
#include "Robot.h"

Sensors::Sensors() {
	gyro = new ADXRS450_Gyro();
	elevatorBottom = new DigitalInput(8);
	SmartDashboard::PutData("gyroscope", gyro);
}

int Sensors::getGyroAngle(){
	return gyro->GetAngle();
}

bool Sensors::getElevatorBottom(){
	return elevatorBottom->Get();
}

void Sensors::resetGyro(){
	gyro->Reset();
}
