/*
 * Elevator.h
 *
 *  Created on: Jan 27, 2018
 *      Author: Hank Krutulis - 461
 */
#include <WPILib.h>
#include "ctre/Phoenix.h"
#include "Sensors.h"
#include "Robot.h"

#ifndef SRC_ELEVATOR_H_
#define SRC_ELEVATOR_H_

class Elevator {
public:
	Elevator(Sensors&);
	void goUp();
	void goDown();
	void move(double);
	void goToSwitchHeight();
	void goToScaleHeight();
	void goToClimbHeight();
	void goToIntakeExchangeHeight();
	void haltMotion();
	void resetEncoder();
	void postValues();
	void periodicValues();
	void Brake();
	void BrakeRelease();

private:
	TalonSRX* elevator1;
	VictorSPX* elevator2;
	VictorSPX* elevator3;
	DoubleSolenoid* elevatorBrake;
	Sensors* sensors;

	double encoderVal,
	slowTopThreshold = 3000,
	slowBottomThreshold = 5000,
	slowDownMultiplierTop = 0.3,
	slowDownMultiplierBottom = 0.2,
	elevatorTop = 23000;
	double raiseSpeed = 1, lowerSpeed = 0.7;
	double heightTolerance = 250;
	double intakeExchangeHeight = 200;
	double switchHeight = 1300;
	double scaleHeight = 3500;
	double climbHeight = 4000;
};

#endif /* SRC_ELEVATOR_H_ */
