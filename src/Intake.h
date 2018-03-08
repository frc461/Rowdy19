/*
 * Intake.h
 *
 *  Created on: Jan 27, 2018
 *      Author: Hank Krutulis - 461
 */
#include <WPILib.h>
#include "Elevator.h"
#include "ctre/Phoenix.h"

#ifndef SRC_INTAKE_H_
#define SRC_INTAKE_H_

class Intake {
public:
	Intake();

	//Intake
	void takeInOuter();
	void takeInInner();
	void takeInAll();

	//Output
	void outputOuter();
	void outputInner();
	void outputAll();

	//Spins
	void spinRight();
	void spinLeft();

	//Spits
	void resetSpitCount();
	void spitInner();
	void spitCube();
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
	spinSpeed = 0.2,
	slowOutputSpeed = 0.4;
	int spitCount;

	DoubleSolenoid* intakeExtension;
	Victor* intakeInLeft;
	Victor* intakeInRight;
	Spark* intakeOutLeft;
	Spark* intakeOutRight;
};

#endif /* SRC_INTAKE_H_ */
