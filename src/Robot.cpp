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
	int startPos, target, ourSwitch, ourScale, pushCounter = 0;
	bool previouslyToggled, intakeWristOverride = false, intakeDown = false;


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
		//intake->extendIntake();
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

		if(leftJoystick->GetRawButton(trigger)){
			rotate = rotate / 2;
		}
		if(rightJoystick->GetRawButton(trigger)){
			forwardR = forwardR * 2 / 3;
		}

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
		} else if (operatorController->GetRawButton(XboxButtonB)){
			intake->slowOutput();
		} else if (operatorController->GetRawButton(XboxButtonA)){
			intakeWristOverride = true;
			intakeDown = intake->intakeWithRaise();
		} else {
			intakeWristOverride = false;
			intake->allOff();
		}

		if(!intakeWristOverride && operatorController->GetRawButton(XboxButtonY) && previouslyToggled == false){
			intakeDown = !intakeDown;
		}
		previouslyToggled = operatorController->GetRawButton(XboxButtonY);

		if (intakeDown){
			intake->extendIntake();
		} else {
			intake->retractIntake();
		}


		SmartDashboard::PutNumber("XboxDPad", operatorController->GetPOV(0));

		if (operatorController->GetRawButton(XboxButtonRightBumper) /*|| pdp->GetVoltage() < 7*/){
			elevator->haltMotion();
		} else if(operatorController->GetRawAxis(XboxAxisLeftStickY) < -0.5){
			elevator->goUp();
		} else if (operatorController->GetRawAxis(XboxAxisLeftStickY) > 0.5){
			elevator->goDown();
		} else if (dPad == XboxDPadUp){
			elevator->goToScaleHeight();
		} else if (dPad == XboxDPadRight){
			elevator->goToSwitchHeight();
		} else if (dPad == XboxDPadDown){
			elevator->goToIntakeExchangeHeight();
		} else if (operatorController->GetRawAxis(XboxAxisLeftTrigger) > 0.5
				&& operatorController->GetRawAxis(XboxAxisRightTrigger) > 0.5){
			elevator->move(0.8);
		} else if (operatorController->GetRawButton(XboxButtonStart)){
			elevator->moveIgnore(0.8);
		} else {
			elevator->haltMotion();
		}

		if(pushCounter++ > 12){
			if(!sensors->getIntakeButtonL() && !sensors->getIntakeButtonR()){
				sensors->lightUp();
			} else {
				sensors->lightDown();
			}
			pushCounter = 0;
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
