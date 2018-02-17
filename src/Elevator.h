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

	//Basic motions
	void goUp();
	void goDown();
	void move(double);
	void haltMotion();

	//Brake bois
	void brake();
	void brakeRelease();

	//Automatic height reachers
	void goToSwitchHeight();
	void goToScaleHeight();
	void goToClimbHeight();
	void goToIntakeExchangeHeight();

	//Encoder handlers
	int  encoderValue();
	void resetEncoder();


	//Shuffleboard Interactions
	void postValues();
	void periodicValues();


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
	double raiseSpeed = 0.6, lowerSpeed = 0.3;
	int heightTolerance = 250;
	int intakeExchangeHeight = 200;
	int switchHeight = 1300;
	int scaleHeight = 3500;
	int climbHeight = 4000;
};

#endif /* SRC_ELEVATOR_H_ */
