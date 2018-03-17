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

//Include custom headers
#include "THRSTMSTRmap.h"
#include "XboxJoystickMap.h"
#include "Robot.h"
#include "DriveTrain.h"
#include "ShuffleboardPoster.h"
#include "Autonomous.h"
#include "Intake.h"
#include "Elevator.h"
#include "Camera.h"

#define COMP
#define DEBUGGING


class Robot : public frc::IterativeRobot {
public:

	//Controls
	Joystick *leftJoystick;
	Joystick *rightJoystick;
	Joystick *operatorController;

	//Robot parts
//	PowerDistributionPanel *pdp;
	DriveTrain *driveTrain;
	ShuffleboardPoster *boardHandler;
	Intake* intake;
	Elevator* elevator;

	//Camera
//	Camera *camera;


	Autonomous *auton;
	Sensors *sensors;	

	//Custom variables
	int startPos, target, ourSwitch, ourScale;
	bool intakeIn, previouslyToggled;


	void RobotInit() {
		leftJoystick = new Joystick(0);
		rightJoystick = new Joystick(1);
		operatorController = new Joystick(2);
//		pdp = new PowerDistributionPanel(0);
//		camera = new Camera();
		sensors = new Sensors();
		driveTrain = new DriveTrain(*sensors);
		boardHandler = new ShuffleboardPoster(*driveTrain,*sensors);
		elevator = new Elevator(*sensors);
		intake = new Intake();
		auton = new Autonomous(*driveTrain, *sensors, *boardHandler, *elevator, *intake);
		previouslyToggled = false;
		intakeIn = true;
		CameraServer::GetInstance()->StartAutomaticCapture(1);
	}


	void AutonomousInit() override {
		boardHandler->shufflePeriodic();
		driveTrain->resetEncoders();
		sensors->resetGyro();
		auton->updateStarts();
		auton->resetZeroed();
		auton->setAutoState(InitialStart);
		elevator->periodicValues();
		intake->periodicValues();
		intake->resetSpitCount();
		intake->extendIntake();
		elevator->autonStart();
	}


	void AutonomousPeriodic() {
		elevator->periodicValues();
		boardHandler->shufflePeriodic();
		intake->periodicValues();
		auton->runAuto();
	}

	void TeleopInit() {
		driveTrain->resetEncoders();
		intake->extendIntake();
		intake->resetSpitCount();
	}

	void TeleopPeriodic() {
		boardHandler->shufflePeriodic();
		elevator->periodicValues();
//		camera->cameraPeriodic(operatorController->GetRawButton(XboxButtonLeftStick));

		double forwardR = rightJoystick->GetRawAxis(yAxisJS);
//		double forwardL = leftJoystick->GetRawAxis(yAxisJS);
		double rotate  = leftJoystick->GetRawAxis(xAxisJS);
		double strafe  = rightJoystick->GetRawAxis(xAxisJS);
		int dPad = operatorController->GetPOV();

		if(intakeIn){
			intake->extendIntake();
		} else {
			intake->retractIntake();
		}

//		if(rightJoystick->GetRawButton(trigger)){
//			driveTrain->tankDrive(forwardL, forwardR, strafe);
//		} else {
			driveTrain->arcadeDrive(forwardR, rotate, strafe);
//		}

		if(operatorController->GetRawAxis(XboxAxisRightStickY) < -0.5 || operatorController->GetRawButton(XboxButtonY)){
			intake->outputAll();
		} else if (operatorController->GetRawAxis(XboxAxisRightStickY) > 0.5 || operatorController->GetRawButton(XboxButtonA)){
			intake->takeInAll();
		} else if (operatorController->GetRawAxis(XboxAxisRightStickX) < -0.5 || operatorController->GetRawButton(XboxButtonX)){
			intake->spinLeft();
		} else if (operatorController->GetRawAxis(XboxAxisRightStickX) > 0.5 || operatorController->GetRawButton(XboxButtonB)){
			intake->spinRight();
		} else if (operatorController->GetRawButton(XboxButtonRightStick)){
			intake->slowOutput();
		} else {
			intake->allOff();
		}


		SmartDashboard::PutNumber("XboxDPad", operatorController->GetPOV(0));

		if (operatorController->GetRawButton(XboxButtonRightBumper) /*|| pdp->GetVoltage() < 7*/){
			elevator->haltMotion();
		} else if	(operatorController->GetPOV(0) > XboxDPadDownLeft && operatorController->GetRawAxis(XboxDPad) < XboxDPadDownRight){
			elevator->move(1.0);
		} else if(operatorController->GetRawAxis(XboxAxisLeftStickY) < -0.5){
			elevator->goUp();
		} else if (operatorController->GetRawAxis(XboxAxisLeftStickY) > 0.5 || dPad == XboxDPadDown){
			elevator->goDown();
		} else if (dPad == XboxDPadRight){
			elevator->goToScaleHeight();
		} else if (dPad == XboxDPadLeft){
			elevator->goToSwitchHeight();
		} else if (operatorController->GetRawAxis(XboxAxisLeftTrigger) > 0.5
				&& operatorController->GetRawAxis(XboxAxisRightTrigger) > 0.5){
			elevator->move(1.0);
		} else {
			elevator->haltMotion();
		}

		if (operatorController->GetRawButton(XboxButtonStart) && operatorController->GetRawButton(XboxButtonBack)){
			if (!previouslyToggled){
				intakeIn = !intakeIn;
				previouslyToggled = true;
			}
		} else {
				previouslyToggled = false;
		}

		if (operatorController->GetRawButton(XboxButtonLeftBumper)){
			driveTrain->resetEncoders();
			sensors->resetGyro();
		}

	}

	void TestPeriodic() {

	}

	void DisabledInit() {
		elevator->haltMotion();
	}

	void DisabledPeriodic() {
//		cvSink->GrabFrame(source);
//		outputStreamStd.PutFrame(source);
	}

private:

};

START_ROBOT_CLASS(Robot)
