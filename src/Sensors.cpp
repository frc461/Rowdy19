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
	intakeButtonR = new DigitalInput(6);
	intakeButtonL = new DigitalInput(7);
	wrist = new AnalogPotentiometer(3, 360, 0);
}

double Sensors::getWristAngle(){
	return wrist->Get();
}

int Sensors::getGyroAngle(){
	return gyro->GetAngle();
}

bool Sensors::getElevatorBottom(){
	return elevatorBottom->Get();
}

bool Sensors::getIntakeButtonL() {
	return intakeButtonL->Get();
}

bool Sensors::getIntakeButtonR() {
	return intakeButtonR->Get();
}

void Sensors::resetGyro(){
	gyro->Reset();
}
