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
	elevatorBottom = new DigitalInput(9);
}

int Sensors::GetGyroAngle(){
	return gyro->GetAngle();
}

bool Sensors::getElevatorBottom(){
	return elevatorBottom->Get();
}

void Sensors::ResetGyro(){
	gyro->Reset();
}
