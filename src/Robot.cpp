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
	bool intakeIn, previouslyToggled, intakeWristUp;


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
		intake = new Intake(*sensors);
		auton = new Autonomous(*driveTrain, *sensors, *boardHandler, *elevator, *intake);
		previouslyToggled = false;
		intakeIn = true;
		CameraServer::GetInstance()->StartAutomaticCapture(0);
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
		auton->smartRun();
	}

	void TeleopInit() {
		driveTrain->resetEncoders();
		intake->extendIntake();
		intake->resetSpitCount();
	}

	void TeleopPeriodic() {
		boardHandler->shufflePeriodic();
		elevator->periodicValues();
		intake->periodicValues();
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

		if(operatorController->GetRawAxis(XboxAxisRightStickY) < -0.5){
			intake->output();
		} else if (operatorController->GetRawAxis(XboxAxisRightStickY) > 0.5){
			intake->intake();
		} else if (operatorController->GetRawAxis(XboxAxisRightStickX) < -0.5){
			intake->spinLeft();
		} else if (operatorController->GetRawAxis(XboxAxisRightStickX) > 0.5){
			intake->spinRight();
		} else if (operatorController->GetRawButton(XboxButtonRightStick)){
			intake->slowOutput();
		} else if (operatorController->GetRawButton(XboxButtonA)){
			intakeWristUp = true;
		} else {
			intake->allOff();
		}


		if(intakeWristUp){
			intake->intakeWithRaise();
		}

		SmartDashboard::PutNumber("XboxDPad", operatorController->GetPOV(0));

		if (operatorController->GetRawButton(XboxButtonRightBumper) /*|| pdp->GetVoltage() < 7*/){
			elevator->haltMotion();
		} else if(operatorController->GetRawAxis(XboxAxisLeftStickY) < -0.5){
			elevator->goUp();
		} else if (operatorController->GetRawAxis(XboxAxisLeftStickY) > 0.5){
			elevator->goDown();
		} else if (operatorController->GetRawButton(XboxButtonY)){
			elevator->goToScaleHeight();
		} else if (operatorController->GetRawButton(XboxButtonB)){
			elevator->goToSwitchHeight();
		} else if (operatorController->GetRawButton(XboxButtonX)){
			elevator->goToIntakeExchangeHeight();
		} else if (operatorController->GetRawAxis(XboxAxisLeftTrigger) > 0.5
				&& operatorController->GetRawAxis(XboxAxisRightTrigger) > 0.5){
			elevator->move(1.0);
		} else {
			elevator->haltMotion();
		}

		if(dPad != -1 && !operatorController->GetRawButton(XboxButtonA)){
			intakeWristUp = false;
		}

		if(!intakeWristUp){
			if (dPad == XboxDPadRight){
				intake->wristRotate(1);
			} else if (dPad == XboxDPadLeft){
				intake->wristRotate(-1);
			}else if (dPad == XboxDPadUp){
				intake->wristForward();
			} else if (dPad == XboxDPadDown){
				intake->wristBack();
			} else {
				intake->wristHalt();
			}
		}

		if (operatorController->GetRawButton(XboxButtonBack)){
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
		driveTrain->resetEncoders();
		sensors->resetGyro();
		auton->updateStarts();
		auton->resetZeroed();
		auton->shuffleCheck();
		intake->periodicValues();
		elevator->periodicValues();
		driveTrain->periodicValues();
	}

private:

};

START_ROBOT_CLASS(Robot)
