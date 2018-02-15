/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/* Author: Hank Krutulis - 461                                                */
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
#include "XboxJoystickMap.h"
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
	Joystick *operatorController;

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
		operatorController = new Joystick(2);


		sensors = new Sensors();
		driveTrain = new DriveTrain(*sensors);
		boardHandler = new ShuffleboardPoster(*driveTrain,*sensors);
		elevator = new Elevator(*sensors);
		intake = new Intake();
		auton = new Autonomous(*driveTrain, *sensors, *boardHandler, *elevator, *intake);
	}


	void AutonomousInit() override {
		boardHandler->ShufflePeriodic();
		driveTrain->ResetEncoders();
		sensors->ResetGyro();
		auton->ResetZeroed();
		auton->SetAutoState(InitialStart);
		elevator->periodicValues();
		intake->PeriodicValues();
		intake->extendIntake();
		intake->resetSpitCount();
	}


	void AutonomousPeriodic() {
//		if(!sensors->getElevatorBottom()){
//			intake->retractIntake();
//		}
		elevator->periodicValues();
		boardHandler->ShufflePeriodic();
		intake->PeriodicValues();
		auton->RunAuto();
	}

	void TeleopInit() {
		driveTrain->ResetEncoders();
		intake->extendIntake();
		intakeIn = false;
		elevator->BrakeRelease();
		intake->resetSpitCount();
	}

	void TeleopPeriodic() {
		boardHandler->ShufflePeriodic();
		elevator->periodicValues();

		double forwardR = rightJoystick->GetRawAxis(yAxisJS);
//		double forwardL = leftJoystick->GetRawAxis(yAxisJS);
		double rotate  = leftJoystick->GetRawAxis(xAxisJS);
		double strafe  = rightJoystick->GetRawAxis(xAxisJS);
		driveTrain->ArcadeDrive(forwardR, rotate, strafe);

		if(operatorController->GetRawButton(XboxButtonX)){
			intake->takeInAll();
		} else if (operatorController->GetRawButton(XboxButtonB)){
			intake->outputAll();
		} else if (operatorController->GetRawButton(XboxButtonY)){
			intake->spitInner();
		} else if (operatorController->GetRawButton(XboxButtonA)){
			intake->spinRight();
		} else {
			intake->allOff();
		}

		if(operatorController->GetRawAxis(XboxAxisLeftStickY) < 0){
			elevator->goUp();
		} else if (operatorController->GetRawAxis(XboxAxisLeftStickY) > 0){
			elevator->goDown();
		} else {
			elevator->haltMotion();
		}

		if (operatorController->GetRawButton(XboxButtonRightBumper)){
			if (!previouslyToggled){
				intakeIn = !intakeIn;
			}
		}
		previouslyToggled = operatorController->GetRawButton(XboxButtonRightBumper);

		if (operatorController->GetRawButton(XboxButtonLeftBumper)){
			driveTrain->ResetEncoders();
			sensors->ResetGyro();
			elevator->resetEncoder();
		}

		if (operatorController->GetRawButton(rightThumbOrange)){
			intake->retractIntake();
		} else {
			if(intakeIn){
				intake->retractIntake();
			} else {
				intake->extendIntake();
			}
		}

		SmartDashboard::PutBoolean("intakeToggled", intakeIn);

	}

	void TestPeriodic() {}


private:

};

START_ROBOT_CLASS(Robot)
