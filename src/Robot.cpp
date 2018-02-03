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

#include "WPILib.h"
#include "ctre/Phoenix.h"
//Include custom headers
#include "THRSTMSTRmap.h"
#include "Robot.h"
#include "DriveTrain.h"
#include "ShuffleboardPoster.h"
#include "Autonomous.h"
#include "Intake.h"

using namespace frc;
using namespace ctre::phoenix::motorcontrol;
using namespace ctre::phoenix::motorcontrol::can;

class Robot : public frc::IterativeRobot {
public:
	//Controls
	Joystick *leftJoystick;
	Joystick *rightJoystick;
	Joystick *middleJoystick;
	TalonSRX *talon;
	VictorSPX *victor;
	//Robot parts
	DriveTrain *driveTrain;
	ShuffleboardPoster *boardHandler;
	int state = 0;
//	Intake* intake;

	Autonomous *auton;
	Sensors *sensors;	

	//Custom variables
	int ourSwitch;

	//SmartDashboard Selector
	enum side {
		leftside = 0,
		middleside,
		rightside
	};
	SendableChooser<side> sides;
	enum temporaryfeedback {
		left = 0,
		right
	};
	SendableChooser<temporaryfeedback> tempfeed;
	void RobotInit() {
		leftJoystick = new Joystick(0);
		rightJoystick = new Joystick(1);
		sensors = new Sensors();
		driveTrain = new DriveTrain(*sensors);
		boardHandler = new ShuffleboardPoster(*driveTrain,*sensors);
		auton = new Autonomous(*driveTrain, *sensors);
//		intake = new Intake();
		sides.AddDefault("Left",leftside);
		sides.AddObject("Middle",middleside);
		sides.AddObject("Right",rightside);
		tempfeed.AddDefault("Left", left);
		tempfeed.AddObject("Right", right);
		SmartDashboard::PutData("sides", &sides);
		SmartDashboard::PutData("Feedback", &tempfeed);
	}


	void AutonomousInit() override {
		boardHandler->ShufflePeriodic();
		driveTrain->ResetEncoders();
		auton->SetAutoState(InitialStart);
		ourSwitch = boardHandler->GetOurSwitch();
		state=0;
	}


	void AutonomousPeriodic() {
/*		boardHandler->ShufflePeriodic();

		if (ourSwitch == RightSide) {
			auton->SwitchRightAuto();
		} else if (ourSwitch == LeftSide)  {
			auton->SwitchLeftAuto();
		} else {
			auton->DefaultCross();
		}

		if (sides.GetSelected() == leftside) {
			if (tempfeed.GetSelected() == left) {
				if (state==0) {
					if (driveTrain->GetEncoderVal(RightSide) < 20500) {

					} else {
						driveTrain->ResetEncoders();
						gyroscope->Reset();
						state++;
					}
				}
				if (state==1) {
					if (gyroscope->GetAngle() < 90) {

					} else {
						driveTrain->ResetEncoders();
						gyroscope->Reset();
						state++;
					}
				}
				if (state==2) {
					if (driveTrain->GetEncoderVal(RightSide) < 4500) {

					} else {
						gyroscope->Reset();
						driveTrain->ResetEncoders();
						state++;
					}
				}
				if (state==3) {
					if (gyrosocpe->GetAngle() > -90) {

					} else {
						gyroscope->Reset();
						driveTrain->ResetEncoders();
						state++;
					}
				}
				if (state==4) {
//					Put the elevator up here
				} else {
					gyroscope->Reset();
					driveTrain->ResetEncoders();
					state++;
				}
			}
			if (tempfeed.GetSelected() == right) {
				if (state==0) {
					if (driveTrain->GetEncoderVal(RightSide) < 18500) {

					} else {
						driveTrain->ResetEncoders();
						gyroscope->Reset();
						state++;
					}
				}
				if (state==1) {
					if (gyroscope->GetAngle() < 90) {

					} else {
						driveTrain->ResetEncoders();
						gyroscope->Reset();
						state++;
					}
				}
			}
		}
		if (sides.GetSelected() == middleside) {
			if (tempfeed.GetSelected() == left) {

			}
			if (tempfeed.GetSelected() == right) {

			}
		}
		if (sides.GetSelected() == rightside) {
			if (tempfeed.GetSelected() == left) {

			}
			if (tempfeed.GetSelected() == right) {
				if (state==0) {
					if (driveTrain->GetEncoderVal(LeftSide) < [foward1]) {

					} else {
						gyroscope->Reset();
						driveTrain->ResetEncoders();
						state++;
					}
				}
				if (state==1) {
					if (gyroscope->GetAngle() < [turn1]) {

					} else {
						gyroscope->Reset();
						driveTrain->ResetEncoders();
						state++;
					}
				}
				if (state==2) {
					if (driveTrain->GetEncoderVal(LeftSide) < [foward2]) {

					} else {
						gyroscope->Reset();
						driveTrain->ResetEncoders();
						state++;
					}
				}
				if (state==3) {
					if (gyrosocpe->GetAngle() < [turn2]) {

					} else {
						gyroscope->Reset();
						driveTrain->ResetEncoders();
						state++;
					}
				}
				if (state==4) {
//					Put the elevator up here
				} else {
					gyroscope->Reset();
					driveTrain->ResetEncoders();
					state++;
				}
			}
		}*/
	}

	void TeleopInit() {
		driveTrain->ResetEncoders();
		int state = 0;
	}

	void TeleopPeriodic() {
		boardHandler->ShufflePeriodic();
		double forwardR = rightJoystick->GetRawAxis(yAxisJS);
		double forwardL = leftJoystick->GetRawAxis(yAxisJS);
		double rotate  = leftJoystick->GetRawAxis(xAxisJS);
		double strafe  = rightJoystick->GetRawAxis(xAxisJS);

//		if(rightJoystick->GetRawButton(thumbSwitch)){
//			intake->takeInAll();
//		} else if (leftJoystick->GetRawButton(thumbSwitch)){
//			intake->outputAll();
//		} else {
//			intake->allOff();
//		}

		driveTrain->GetEncoderVal(LeftSide);
		if (rightJoystick->GetRawButton(trigger) && rightJoystick->GetRawButton(thumbSwitch)) {
			driveTrain->ResetEncoders();
		}


		if (rightJoystick->GetRawButton(trigger)){
			driveTrain->TankDrive(forwardL, forwardR, strafe);
		} else {
			driveTrain->ArcadeDrive(forwardR, rotate, strafe);
		 }
	}
	void EncoderReset() {}
	void TestPeriodic() {}

private:

};

START_ROBOT_CLASS(Robot)
