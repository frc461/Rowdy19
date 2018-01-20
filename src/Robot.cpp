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

class Robot : public frc::IterativeRobot {
public:

	//Controls
	Joystick *leftJoystick;
	Joystick *rightJoystick;

	//Robot parts
	PowerDistributionPanel *pdp;
	DriveTrain *driveTrain;
//	WPI_TalonSRX *leftOutIntake;
//	WPI_TalonSRX *rightOutIntake;
//	WPI_TalonSRX *leftInIntake;
//	WPI_TalonSRX *rightInIntake;
//
//	WPI_TalonSRX *elevator1;
//	WPI_TalonSRX *elevator2;
//	WPI_TalonSRX *elevator3;

	Solenoid *intakeArms;

	AHRS *navxBoard;
	Encoder *leftDriveEncoder;
	Encoder *rightDriveEncoder;



	//Custom variables
	int ourSwitch, autoState, initialDist, lTurn1, lTurn2, lDrive3, lDrive2, rTurn1, rTurn2, rDrive3, rDrive2;
	double autoDriveSpeed, autoTurnSpeed;


	//Constants



	void RobotInit() {

		leftJoystick = new Joystick(0);
		rightJoystick = new Joystick(1);

		pdp = new PowerDistributionPanel(0);

		driveTrain = new DriveTrain(RightDrive1CAN, RightDrive2CAN, RightDrive3CAN, LeftDrive1CAN, LeftDrive2CAN, LeftDrive3CAN, Strafe1CAN, Strafe2CAN);

//		leftOutIntake  = new WPI_TalonSRX(LeftOutIntakeCAN);
//		rightOutIntake = new WPI_TalonSRX(RightOutIntakeCAN);
//		leftInIntake   = new WPI_TalonSRX(LeftInIntakeCAN);
//		rightInIntake  = new WPI_TalonSRX(RightInIntakeCAN);
//		intakeArms     = new Solenoid(0);
//		elevator1 = new WPI_TalonSRX(Elevator1CAN);
//		elevator2 = new WPI_TalonSRX(Elevator2CAN);
//		elevator3 = new WPI_TalonSRX(Elevator3CAN);
//		navxBoard = new AHRS(SerialPort::kMXP);
	}

	void AutonomousInit() override {
		ShuffleboardPeriodic();
		EncoderReset();

		autoState = InitialStart;

		std::string gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
		if (gameData[0] == 'L') {
			ourSwitch = LeftSwitch;
		} else {
			ourSwitch = RightSwitch;
		}

	}

	void AutonomousPeriodic() {
		double leftEncDist = leftDriveEncoder->GetDistance();
		double gyroAngle = navxBoard->GetYaw();
		AutoShuffleboardGet();

//		switch (autoState) {
//			case (InitialStart):
//				if (leftEncDist > initialDist) {
//					driveTrain->TankDrive(autoDriveSpeed, autoDriveSpeed);
//					break;
//				} else {
//					navxBoard->Reset();
//					autoState = TurnDownMiddle;
//					break;
//				}
//			case (TurnDownMiddle):
//				if (ourSwitch == LeftSwitch && gyroAngle > lTurn1) {
//					driveTrain->TankDrive(-autoTurnSpeed, autoTurnSpeed);
//					break;
//				} else if (ourSwitch == RightSwitch && gyroAngle < rTurn1) {
//					driveTrain->TankDrive(autoTurnSpeed, -autoTurnSpeed);
//					break;
//				} else {
//					EncoderReset();
//					autoState = DriveDiagonal;
//					break;
//				}
//			case (DriveDiagonal):
//				if (ourSwitch == RightSwitch && leftEncDist > rDrive2) {
//					driveTrain->TankDrive(autoDriveSpeed, autoDriveSpeed);
//					break;
//				} else if (ourSwitch == LeftSwitch && leftEncDist > lDrive2) {
//					driveTrain->TankDrive(autoDriveSpeed, autoDriveSpeed);
//					break;
//				}
//				else {
//					navxBoard->Reset();
//					autoState = FaceSwitch;
//					break;
//				}
//			case (FaceSwitch):
//				if (ourSwitch == LeftSwitch && gyroAngle < lTurn2) {
//					driveTrain->TankDrive(autoTurnSpeed, -autoTurnSpeed);
//					break;
//				} else if (ourSwitch == RightSwitch && gyroAngle > rTurn2) {
//					driveTrain->TankDrive(-autoTurnSpeed, autoTurnSpeed);
//					break;
//				} else {
//					EncoderReset();
//					autoState = DriveSideSwitch;
//					break;
//				}
//			case (DriveSideSwitch):
//				if (ourSwitch == RightSwitch && leftEncDist > rDrive3) {
//					driveTrain->TankDrive(autoDriveSpeed, autoDriveSpeed);
//					break;
//				} else if ( ourSwitch == LeftSwitch && leftEncDist > lDrive3){
//					driveTrain->TankDrive(autoDriveSpeed, autoDriveSpeed);
//					break;
//				}
//				else {
//					autoState = DeployBlock;
//					break;
//				}
//			case (DeployBlock):
//				break;
//		}
	}

	void TeleopInit() {}

	void TeleopPeriodic() {
		double forward = leftJoystick->GetRawAxis(xAxisJS);
		double rotate  = rightJoystick->GetRawAxis(yAxisJS);
		double strafe  = rightJoystick->GetRawAxis(xAxisJS);

		driveTrain->ArcadeDrive(forward, rotate, strafe);
	}

	void TestPeriodic() {}

	void EncoderReset() {
		leftDriveEncoder->Reset();
		rightDriveEncoder->Reset();
	}

	void AutoShuffleboardGet() {
		initialDist    = SmartDashboard::GetNumber("Auton/initDist", -420);
		lTurn1         = SmartDashboard::GetNumber("Auton/lTurn1", -35);
		lTurn2         = SmartDashboard::GetNumber("Auton/lTurn2", 45);
		lDrive2        = SmartDashboard::GetNumber("Auton/lDrive2", -1530);
		lDrive3        = SmartDashboard::GetNumber("Auton/lDrive3", -500);
		rTurn1         = SmartDashboard::GetNumber("Auton/rTurn1", 55);
		rTurn2         = SmartDashboard::GetNumber("Auton/rTurn2", -45);
		rDrive2        = SmartDashboard::GetNumber("Auton/rDrive2", -1200);
		rDrive3        = SmartDashboard::GetNumber("Auton/rDrive3", -790);
		autoDriveSpeed = SmartDashboard::GetNumber("Auton/autoDriveSpeed", 0.8);
		autoTurnSpeed  = SmartDashboard::GetNumber("Auton/autoTurnSpeed", 0.65);
	}

	void ShuffleboardPeriodic(){
		//SmartDashboard::PutData("navxBoard", navxBoard);
	}

private:

};

START_ROBOT_CLASS(Robot)
