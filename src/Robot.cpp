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

	AHRS *navxBoard;
	Encoder *leftDriveEncoder;
	Encoder *rightDriveEncoder;

	//Custom variables
	int ourSwitch, autoState, initialDist, lTurn1, lTurn2, lDrive3, lDrive2, rTurn1, rTurn2, rDrive3, rDrive2;
	double autoDriveSpeed, autoTurnSpeed;

	void RobotInit() {
		leftJoystick = new Joystick(0);
		rightJoystick = new Joystick(1);

		pdp = new PowerDistributionPanel(0);

		driveTrain = new DriveTrain(RightDrive1CAN, RightDrive2CAN, RightDrive3CAN, LeftDrive1CAN, LeftDrive2CAN, LeftDrive3CAN, Strafe1CAN, Strafe2CAN);
		boardHandler = new ShuffleboardPoster(leftDriveEncoder, rightDriveEncoder, navxBoard);
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
		boardHandler->ShufflePeriodic();
		EncoderReset();

		autoState = InitialStart;
		ourSwitch = boardHandler->GetOurSwitch();
	}

	void AutonomousPeriodic() {
		double leftEncDist = leftDriveEncoder->GetDistance();
		double gyroAngle = navxBoard->GetYaw();
		boardHandler->AutonGet();
		boardHandler->ShufflePeriodic();

    	switch (autoState) {
    		case (InitialStart):
    			if (leftEncDist > initialDist) {
    				driveTrain->TankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
    				break;
    			} else {
    				navxBoard->Reset();
    				autoState = TurnDownMiddle;
    				break;
    			}
    		case (TurnDownMiddle):
    			if (ourSwitch == LeftSide && gyroAngle > lTurn1) {
    				driveTrain->TankDrive(-autoTurnSpeed, autoTurnSpeed, 0.0);
    				break;
    			} else if (ourSwitch == RightSide && gyroAngle < rTurn1) {
    				driveTrain->TankDrive(autoTurnSpeed, -autoTurnSpeed, 0.0);
    				break;
    			} else {
    				EncoderReset();
    				autoState = DriveDiagonal;
    				break;
    			}
    		case (DriveDiagonal):
    			if (ourSwitch == RightSide && leftEncDist > rDrive2) {
    				driveTrain->TankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
    				break;
    			} else if (ourSwitch == LeftSide && leftEncDist > lDrive2) {
    				driveTrain->TankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
    				break;
    			}
    			else {
    				navxBoard->Reset();
    				autoState = FaceSwitch;
    				break;
    			}
    		case (FaceSwitch):
    			if (ourSwitch == LeftSide && gyroAngle < lTurn2) {
    				driveTrain->TankDrive(autoTurnSpeed, -autoTurnSpeed, 0.0);
    				break;
    			} else if (ourSwitch == RightSide && gyroAngle > rTurn2) {
    				driveTrain->TankDrive(-autoTurnSpeed, autoTurnSpeed, 0.0);
    				break;
    			} else {
    				EncoderReset();
    				autoState = DriveSideSwitch;
    				break;
    			}
    		case (DriveSideSwitch):
    			if (ourSwitch == RightSide && leftEncDist > rDrive3) {
    				driveTrain->TankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
    				break;
    			} else if ( ourSwitch == LeftSide && leftEncDist > lDrive3){
    				driveTrain->TankDrive(autoDriveSpeed, autoDriveSpeed, 0.0);
    				break;
    			}
    			else {
    				autoState = DeployBlock;
    				break;
    			}
    		case (DeployBlock):
    			break;
    	}
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

private:

};

START_ROBOT_CLASS(Robot)
