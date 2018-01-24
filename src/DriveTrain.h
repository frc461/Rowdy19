/*
 * DriveTrain.h
 *
 *  Created on: Jan 20, 2018
 *      Author: Hank Krutulis
 */

#ifndef DRIVETRAIN_H_
#define DRIVETRAIN_H_
#include <WPILib.h>
#include "ctre/Phoenix.h"
#include "Robot.h"

class DriveTrain {
public:
	DriveTrain();
	void ArcadeDrive(double, double, double);
	void TankDrive(double, double, double);
//	PowerDistributionPanel GetPDP();
private:
	const double DRIVE_SPEED  = 0.8;
	const double TURN_SPEED   = 0.8;
	const double STRAFE_SPEED = 0.8;

	PowerDistributionPanel *pdp;
	DifferentialDrive *driveTrain;
	WPI_TalonSRX *rightDrive1;
	WPI_VictorSPX *rightDrive2;
	WPI_VictorSPX *rightDrive3;
	WPI_VictorSPX *leftDrive1;
	WPI_VictorSPX *leftDrive2;
	WPI_VictorSPX *leftDrive3;
	WPI_TalonSRX *strafe1;
	WPI_TalonSRX *strafe2;
};

#endif /* DRIVETRAIN_H_ */
