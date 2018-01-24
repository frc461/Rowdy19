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

	ADXRS450_Gyro *gyro;
	Encoder *leftDriveEncoder;
	Encoder *rightDriveEncoder;
	Autonomous *auton;

	//Custom variables
	double autoDriveSpeed, autoTurnSpeed;
	int ourSwitch, autoState;

	void RobotInit() {
		leftJoystick = new Joystick(0);
		rightJoystick = new Joystick(1);
		pdp = new PowerDistributionPanel(0);


//		leftOutIntake  = new WPI_TalonSRX(LeftOutIntakeCAN);
//		rightOutIntake = new WPI_TalonSRX(RightOutIntakeCAN);
//		leftInIntake   = new WPI_TalonSRX(LeftInIntakeCAN);
//		rightInIntake  = new WPI_TalonSRX(RightInIntakeCAN);
//		intakeArms     = new Solenoid(0);
//		elevator1 = new WPI_TalonSRX(Elevator1CAN);
//		elevator2 = new WPI_TalonSRX(Elevator2CAN);
//		elevator3 = new WPI_TalonSRX(Elevator3CAN);
		leftDriveEncoder = new Encoder(LeftEncoderDIO1, LeftEncoderDIO2);
		rightDriveEncoder = new Encoder(RightEncoderDIO1, RightEncoderDIO2);
		gyro = new ADXRS450_Gyro();

		driveTrain = new DriveTrain(RightDrive1CAN, RightDrive2CAN, RightDrive3CAN, LeftDrive1CAN, LeftDrive2CAN, LeftDrive3CAN, Strafe1CAN, Strafe2CAN);
		boardHandler = new ShuffleboardPoster(*leftDriveEncoder, *rightDriveEncoder, *gyro);
		auton = new Autonomous(*driveTrain, *leftDriveEncoder, *gyro);
	}

	void AutonomousInit() override {
		boardHandler->ShufflePeriodic();
		EncoderReset();

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
		double forward = rightJoystick->GetRawAxis(xAxisJS);
		double rotate  = leftJoystick->GetRawAxis(yAxisJS);
		double strafe  = leftJoystick->GetRawAxis(xAxisJS);

		driveTrain->ArcadeDrive(forward, rotate, strafe);
	}

	void TestPeriodic() {}

	void EncoderReset() {
		leftDriveEncoder->Reset();
		rightDriveEncoder->Reset();
	}

private:

};

START_ROBOT_CLASS(Robot)
