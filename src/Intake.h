/*
 * Intake.h
 *
 *  Created on: Jan 27, 2018
 *      Author: Hank Krutulis - 461
 */
#include <WPILib.h>
#include "Elevator.h"
#include "ctre/Phoenix.h"
#include "Sensors.h"

#ifndef SRC_INTAKE_H_
#define SRC_INTAKE_H_

class Intake {
public:
	Intake(Sensors&);

	//Intake
	void intake();
	void intakeWithRaise();

	//Output
	void output();
	void outputWithLower();

	//Spins
	void spinRight();
	void spinLeft();

	//Wrist
	void wristRotate(int);
	void wristHalt();
	void wristForward();
	void wristBack();
	void goToFourtyFive();

	//Spits
	void resetSpitCount();
	void spitInner();
	bool spitCube();
	void slowOutput();

	//Intake solenoid stuffs
	void retractIntake();
	void extendIntake();
	int getSolenoid();

	//Shuffleboard Interactions
	void putValues();
	void periodicValues();

	//Halt activity
	void allOff();

private:
	double intakeSpeed = 0.8,
	outputSpeed = 0.6,
	spinSpeed = 0.4,
	slowOutputSpeed = 0.4,
	wristSpeed = 0.7,
	slowWristSpeed = 0.4;

#ifdef COMPBOT
	int offset = 0;
#endif

#ifdef PRACBOT
	int offset = 50;
#endif

	int
	bandWidth = 30,
	downLimit = 105,
	upwardLimit = 30,
	tiltWristAngle = 90,
	wristTolerance = 5,
	spitCount,
	wristAngle;

	Sensors* sensors;
	DoubleSolenoid* intakeExtension;
	Spark* wristMotor;
	Victor* intakeInLeft;
	Victor* intakeInRight;
};

#endif /* SRC_INTAKE_H_ */
