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

	//Auto logics
	void runAuto();
	void smartRun();

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
	void switchFromBack();

	//Scale auton
	void scaleFromSide();
	void scaleFromCenter();
	void scaleFromOpposite();

	//Emergency auton
	void defaultCross();

	//Data
	void resetZeroed();
	void updateStarts();
	void setAutoState(int);
	int targetHeight();



private:
	bool elevatorZeroed = false;

	int scaleHeight = 26000, switchHeight = 10000;
	int carpetConstant = 0;

	//Sensor values
	int encoderDist, gyroAngle;

	//Auton Values
	int target,
	startingPosition,
	ourSwitch,
	ourScale,
	secondChoice;

	int
		autoState = InitialStart;

		int driftConstant = 45,

		//Center Switch
		initDist = 2500,
		lTurn1 = -35,
		lTurn2 = 23,
		lDrive2 = 4500,
		lDrive3 = 3000,
		rTurn1 = 25,
		rTurn2 = -35,
		rDrive2 = 8000,
		rDrive3 = 2000,
		defaultDist = 1750,

		//L/R Switch
		switchSideDist = 12000,
		faceSwitchAngleRight = -50,
		faceSwitchAngleLeft = 45,
		driveToSwitchDist = 2000,

		//L/R Scale
		scaleSideDist = 32500,
		faceScaleLeft = 20,
		faceScaleRight = 35,
		scaleAdjustDist = 2500,

		//Default
		drivePastDist = 15000,
		driveAwayDist = 15000,

		//Platform zone
		platformToDist = 20000,
		platformTurnToRight = 35,
		platformTurnToLeft = 45,
		platformThruDist = 3000;



	bool heightReached = false;


	double autoDriveSpeed, autoTurnSpeed;

	DriveTrain* driveTrain;
	Sensors* sensors;
	ShuffleboardPoster* board;
	Elevator* elevator;
	Intake* intake;
};


#endif /* AUTONOMOUS_H_ */
