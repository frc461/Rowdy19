/*
 * Elevator.h
 *
 *  Created on: Jan 27, 2018
 *      Author: hank
 */
#include <WPILib.h>
#include "ctre/Phoenix.h"

#ifndef SRC_ELEVATOR_H_
#define SRC_ELEVATOR_H_

class Elevator {
public:
	Elevator();
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

	int encoderVal;
	double raiseSpeed = 0.3, lowerSpeed = 0.1;
	double heightTolerance = 250;
	double intakeExchangeHeight = 200;
	double switchHeight = 1300;
	double scaleHeight = 3500;
	double climbHeight = 4000;
};

#endif /* SRC_ELEVATOR_H_ */
