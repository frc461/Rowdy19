/*
 * Intake.h
 *
 *  Created on: Jan 27, 2018
 *      Author: hank
 */
#include <WPILib.h>
#include "ctre/Phoenix.h"

#ifndef SRC_INTAKE_H_
#define SRC_INTAKE_H_

class Intake {
public:
	Intake();

	void takeInOuter();
	void takeInInner();
	void takeInAll();

	void outputOuter();
	void outputInner();
	void outputAll();

	void spinRight();
	void spinLeft();

	void resetSpitCount();
	void spitInner();
	void spitCube();

	void retractIntake();
	void extendIntake();


	void PostGetValues();

	void allOff();
	int getSolenoid();
private:
	double intakeSpeed = 0.8;
	int spitCount = 0;

	DoubleSolenoid* intakeExtension;
	Talon* intakeInLeft;
	Talon* intakeInRight;
	Spark* intakeOutLeft;
	Spark* intakeOutRight;
};

#endif /* SRC_INTAKE_H_ */
