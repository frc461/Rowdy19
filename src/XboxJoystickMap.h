/*
 * XboxJoystickMap.h
 *
 *  Created on: Jan 18, 2016
 *      Author: Garrett Davidson
 */
#ifndef SRC_XBOXJOYSTICKMAP_H_
#define SRC_XBOXJOYSTICKMAP_H_

enum XboxJoystickButton {
	XboxButtonA = 1,
	XboxButtonB,
	XboxButtonX,
	XboxButtonY,
	XboxButtonLeftBumper,
	XboxButtonRightBumper,
	XboxButtonBack,
	XboxButtonStart,
	XboxButtonLeftStick,
	XboxButtonRightStick,
};

enum XboxJoystickAxis {
	XboxAxisLeftStickX = 0,
	XboxAxisLeftStickY,
	XboxAxisLeftTrigger,
	XboxAxisRightTrigger,
	XboxAxisRightStickX,
	XboxAxisRightStickY,
	XboxDPad,
};

enum XboxDPadDirection {
	XboxDPadUp = 0,
	XboxDPadUpLeft = 315,
	XboxDPadLeft = 270,
	XboxDPadDownLeft = 225,
	XboxDPadDown = 180,
	XboxDPadDownRight = 135,
	XboxDPadRight = 90,
	XboxDPadUpRight = 45
};
#endif /* SRC_XBOXJOYSTICKMAP_H_ */
