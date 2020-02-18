#ifndef ANGLE_H_
#define ANGLE_H_

// Typedefs
typedef float DEGREES;

// Function declarations
DEGREES Angle_Normalise
(
	DEGREES angle
);

float Angle_Sin
(
	DEGREES angle
);

float Angle_Cos
(
	DEGREES angle
);

float Angle_Tan
(
	DEGREES angle
);

DEGREES Angle_Atan2
(
	int y,
	int x
);

#endif