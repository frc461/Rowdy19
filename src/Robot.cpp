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

class Robot : public frc::IterativeRobot {
public:

	//Controls
	Joystick *leftJoystick;
	Joystick *rightJoystick;

	//Robot parts
	PowerDistributionPanel *pdp;
	DriveTrain *driveTrain;
	ShuffleboardPoster *boardHandler;
//	WPI_TalonSRX *leftOutIntake;
//	WPI_TalonSRX *rightOutIntake;
//	WPI_TalonSRX *leftInIntake;
//	WPI_TalonSRX *rightInIntake;
//	WPI_TalonSRX *elevator1;
//	WPI_TalonSRX *elevator2;
//	WPI_TalonSRX *elevator3;

//	Solenoid *intakeArms;

	Autonomous *auton;
	Sensors *sensors;	

	//Custom variables
	double autoDriveSpeed, autoTurnSpeed;
	int ourSwitch, autoState;

	void RobotInit() {
		leftJoystick = new Joystick(0);
		rightJoystick = new Joystick(1);

//		leftOutIntake  = new WPI_TalonSRX(LeftOutIntakeCAN);
//		rightOutIntake = new WPI_TalonSRX(RightOutIntakeCAN);
//		leftInIntake   = new WPI_TalonSRX(LeftInIntakeCAN);
//		rightInIntake  = new WPI_TalonSRX(RightInIntakeCAN);
//		intakeArms     = new Solenoid(0);
//		elevator1 = new WPI_TalonSRX(Elevator1CAN);
//		elevator2 = new WPI_TalonSRX(Elevator2CAN);
//		elevator3 = new WPI_TalonSRX(Elevator3CAN);

		sensors = new Sensors();

		driveTrain = new DriveTrain();
		boardHandler = new ShuffleboardPoster(*driveTrain,*sensors);
		auton = new Autonomous(*driveTrain, *sensors);
	}

	void AutonomousInit() override {
		boardHandler->ShufflePeriodic();

		autoState = InitialStart;
		ourSwitch = boardHandler->GetOurSwitch();
	}

	void AutonomousPeriodic() {
		boardHandler->ShufflePeriodic();

		if (boardHandler->GetOurSwitch() == RightSide) {
			auton->SwitchRightAuto();
		} else if (boardHandler->GetOurSwitch() == LeftSide)  {
			auton->SwitchLeftAuto();
		} else {
			auton->DefaultCross();
	    }	
	}

	void TeleopInit() {}

	void TeleopPeriodic() {
		boardHandler->ShufflePeriodic();
		double forwardR = rightJoystick->GetRawAxis(yAxisJS);
		double forwardL = leftJoystick->GetRawAxis(yAxisJS);
		double rotate  = leftJoystick->GetRawAxis(xAxisJS);
		double strafe  = rightJoystick->GetRawAxis(xAxisJS);

		if (rightJoystick->GetRawButton(trigger)){
			driveTrain->TankDrive(forwardL, forwardR, strafe);
		} else {
			driveTrain->ArcadeDrive(forwardR, rotate, strafe);
		 }
	}

	void TestPeriodic() {}


private:

};

START_ROBOT_CLASS(Robot)
