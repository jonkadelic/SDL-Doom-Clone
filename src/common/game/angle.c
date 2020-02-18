// Includes
#include <game/angle.h>

#include <math.h>

// Typedefs
typedef float RADIANS;

// Defines
#define PI			3.14159265358979323846
#define MIN_ANGLE	-180.0
#define MAX_ANGLE	180.0
#define ANGLE_RANGE	360.0

// Function declarations
RADIANS Angle_DegreesToRadians
(
	DEGREES degrees
);

DEGREES Angle_RadiansToDegrees
(
	RADIANS radians
);

// Function definitions
RADIANS Angle_DegreesToRadians
(
	DEGREES degrees
)
{
	return degrees * (PI / 180.0);
}

DEGREES Angle_RadiansToDegrees
(
	RADIANS radians
)
{
	return radians * (180.0 / PI);
}

DEGREES Angle_Normalise
(
	DEGREES angle
)
{
	float tAngle = angle;

	while (tAngle > MAX_ANGLE)
	{
		tAngle -= ANGLE_RANGE;
	}
	while (tAngle < MIN_ANGLE)
	{
		tAngle += ANGLE_RANGE;
	}

	return tAngle;
}

float Angle_Sin
(
	DEGREES angle
)
{
	return sinf(Angle_DegreesToRadians(angle));
}

float Angle_Cos
(
	DEGREES angle
)
{
	return cosf(Angle_DegreesToRadians(angle));
}

float Angle_Tan
(
	DEGREES angle
)
{
	return tanf(Angle_DegreesToRadians(angle));
}

DEGREES Angle_Atan2
(
	int y,
	int x
)
{
	return Angle_RadiansToDegrees(atan2f(y, x));
}