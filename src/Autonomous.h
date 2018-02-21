/*
 * Autonomous.h
 *
 *  Created on: Jan 23, 2018
 *      Author: Hank Krutulis - 461
 */

#ifndef AUTONOMOUS_H_
#define AUTONOMOUS_H_
#include <WPILib.h>
#include "DriveTrain.h"
#include "Robot.h"
#include "Sensors.h"
#include "ShuffleboardPoster.h"
#include "Elevator.h"
#include "Intake.h"

class Autonomous {
public:
	Autonomous(DriveTrain&, Sensors&, ShuffleboardPoster&, Elevator&, Intake&);
	void runAuto();

	//Shuffleboard interactions
	void autonPostValues();
	void autonPeriodicValues();

	//Elevator operator
	void elevatorAutoRun();

	//Switch autons
	void switchFromSide();
	void switchRightAuto();
	void switchLeftAuto();
	void switchFromMiddle();

	//Scale auton
	void scaleFromSide();
	void scaleFromCenter();

	//Emergency auton
	void defaultCross();

	//Data
	void resetZeroed();
	void updateStarts();
	void setAutoState(int);
	int targetHeight();



private:
	bool elevatorZeroed = false;

	int scaleHeight = 21000, switchHeight = 10000;
	int encoderDist, gyroAngle,
	initDist = 5000,
	lTurn1 = -35,
	lTurn2 = 23,
	lDrive2 = 6000,
	lDrive3 = 2000,
	rTurn1 = 25,
	rTurn2 = -45,
	rDrive2 = 8000,
	rDrive3 = 2000,
	defaultDist = 1750,
	switchSideDist = 12000,
	faceSwitchAngleRight = 45,
	faceSwitchAngleLeft = -35,
	driveToSwitchDist = 2500,

	scaleSideDist = 25000,
	faceScaleLeft = 20,
	faceScaleRight = 45,
	scaleAdjustDist = 2500,

	autoState = InitialStart;

	int drivePastDist = 7000,
	driveAwayDist = 15000;

	int target, startingPosition, ourSwitch, ourScale;

	bool heightReached = false;


	double autoDriveSpeed, autoTurnSpeed;

	DriveTrain* driveTrain;
	Sensors* sensors;
	ShuffleboardPoster* board;
	Elevator* elevator;
	Intake* intake;
};


#endif /* AUTONOMOUS_H_ */
