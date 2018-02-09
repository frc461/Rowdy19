/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/* Author:Hank Krutulis                                                       */
/* Created: Jan 13, 2017                                                      */
/*----------------------------------------------------------------------------*/


#include <iostream>
#include <string>

//Include WPILib and 3rd party libraries
#include "WPILib.h"
#include "ctre/Phoenix.h"
#include "AHRS.h"

//Include custom headers
#include "THRSTMSTRmap.h"
#include "Robot.h"
#include "DriveTrain.h"
#include "ShuffleboardPoster.h"
#include "Autonomous.h"
#include "Intake.h"
#include "Elevator.h"

class Robot : public frc::IterativeRobot {
public:

	//Controls
	Joystick *leftJoystick;
	Joystick *rightJoystick;
	Joystick *throttle;

	//Robot parts
	PowerDistributionPanel *pdp;
	DriveTrain *driveTrain;
	ShuffleboardPoster *boardHandler;
	Intake* intake;
	Elevator* elevator;

	Autonomous *auton;
	Sensors *sensors;	

	//Custom variables
	int startPos, target, ourSwitch, ourScale;
	bool intakeIn, previouslyToggled;


	void RobotInit() {
		leftJoystick = new Joystick(0);
		rightJoystick = new Joystick(1);
		sensors = new Sensors();
		driveTrain = new DriveTrain(*sensors);
		boardHandler = new ShuffleboardPoster(*driveTrain,*sensors);
		intake = new Intake();
		elevator = new Elevator();
		auton = new Autonomous(*driveTrain, *sensors, *boardHandler, *elevator);
	}


	void AutonomousInit() override {
		boardHandler->ShufflePeriodic();
		driveTrain->ResetEncoders();
		auton->SetAutoState(InitialStart);
	}


	void AutonomousPeriodic() {
		boardHandler->ShufflePeriodic();
		if(target == Switch){

		}
	}

	void TeleopInit() {
		driveTrain->ResetEncoders();
		intake->extendIntake();
		intakeIn = true;
		elevator->BrakeRelease();
	}

	void TeleopPeriodic() {
		boardHandler->ShufflePeriodic();
		elevator->periodicValues();
		double forwardR = rightJoystick->GetRawAxis(yAxisJS);
//		double forwardL = leftJoystick->GetRawAxis(yAxisJS);
		double rotate  = leftJoystick->GetRawAxis(xAxisJS);
		double strafe  = rightJoystick->GetRawAxis(xAxisJS);

		if(throttle->GetRawButton(topLittleFingerButton)){
			intake->takeInAll();
		} else if (throttle->GetRawButton(topRingFingerButton)){
			intake->outputAll();
		} else if (throttle->GetRawButton(flipOffTop)){
			intake->spinLeft();
		} else if (throttle->GetRawButton(flipOffBottom)){
			intake->spinRight();
		} else {
			intake->allOff();
		}

		if(throttle->GetRawAxis(paddleTR) > 0){
			elevator->goUp();
		} else if (throttle->GetRawAxis(paddleTR) < 0){
			elevator->goDown();
		} else {
			elevator->haltMotion();
		}

		if (throttle->GetRawButton(axisButton)){
			if (!previouslyToggled){
				intakeIn = !intakeIn;
			}
		}
		previouslyToggled = throttle->GetRawButton(axisButton);

		if (throttle->GetRawButton(rightThumbOrange)){
			intake->retractIntake();
		} else {
			if(intakeIn){
				intake->retractIntake();
			} else {
				intake->extendIntake();
			}
		}

		driveTrain->ArcadeDrive(forwardR, rotate, strafe);
	}

	void TestPeriodic() {}


private:

};

START_ROBOT_CLASS(Robot)
