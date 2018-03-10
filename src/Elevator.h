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
	void autonStart();


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
	slowBottomThreshold = 3000,
	slowDownMultiplierTop = 0.3,
	slowDownMultiplierBottom = 0.2,
	elevatorTop = 26000;
	double raiseSpeed = 1.0, lowerSpeed = 0.8;
	int heightTolerance = 1000;
	int intakeExchangeHeight = 200;
	int switchHeight = 1300;
	int scaleHeight = 3500;
	int climbHeight = 4000,
		startHeight = 500;

};

#endif /* SRC_ELEVATOR_H_ */
