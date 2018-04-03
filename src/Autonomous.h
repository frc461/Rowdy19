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
	void shuffleCheck();

	//Elevator operator
	void elevatorAutoRun();

	//Switch autons
	void switchFromSide();
	void switchRightAuto();
	void switchLeftAuto();
	void switchFromMiddle();
	void switchFromOpposite();

	//Scale auton
	void scaleFromSide();
	void scaleFromCenter();
	void scaleFromOpposite();

	//Emergency auton
	void defaultCross();

	//Test autos
	void driveStraight();
	void turnRight();
	void turnLeft();

	//Data
	void resetZeroed();
	void updateStarts();
	void setAutoState(int);
	int targetHeight();



private:
	bool elevatorZeroed = false;

	int scaleHeight = 24000, switchHeight = 12000, postCount = 0;
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
		autoState = InitialStart, wristCount = 0, waitCount = 0;

		double driftConstant = 45, encoderAdjust = 15.0/11.0,

		//Center Switch
		initDist = 1250 * encoderAdjust,
		lTurn1 = -35,
		lTurn2 = 45,
		lDrive2 = 8000 * encoderAdjust,
		lDrive3 = 2500 * encoderAdjust,
		rTurn1 = 25,
		rTurn2 = -30,
		rDrive2 = 2000 * encoderAdjust,
		rDrive3 = 6000 * encoderAdjust,
		defaultDist = 1750 * encoderAdjust,

		//L/R Switch
		switchSideDist = 10000 * encoderAdjust,
		faceSwitchAngleRight = -50,
		faceSwitchAngleLeft = 45,
		driveToSwitchDist = 1000 * encoderAdjust,
		driveToSwitchRight = 2000 * encoderAdjust,

		//L/R Scale
		scaleSideDist = 29240,
		faceScaleLeft = 20,
		faceScaleRight = 45,
		scaleAdjustDist = 750,
		scaleAdjustRight = 1500,

		//Default
		drivePastDist = 13000,
		driveAwayDist = 15000,

		//Platform zone
		platformToDist = 21000,
		platformToOtherAlley = 20000,

		//Scale
		turnRightAngle = 35,
		turnLeftAngle = 45,
		scaleAdjustOppLeft = 2000,
		scaleAdjustOppRight = 2000,
		scaleBackOff = 1000,

		//Switch
		leftSwitchAdjust = 2000,
		rightSwitchAdjust = 2000;




	bool heightReached = false;
	int dropCounter = 0;


	double autoDriveSpeed = -0.8, autoTurnSpeed = -0.6;

	DriveTrain* driveTrain;
	Sensors* sensors;
	ShuffleboardPoster* board;
	Elevator* elevator;
	Intake* intake;
};


#endif /* AUTONOMOUS_H_ */
