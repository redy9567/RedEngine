#include "Color.h"

Color::Color()
{
	mR = 0;
	mG = 0;
	mB = 0;
	mA = 255;
}

Color::~Color()
{

}

Color::Color(int red, int green, int blue, int alpha)
{
	mR = red;
	mG = green;
	mB = blue;
	mA = alpha;
}

Color::Color(float red, float green, float blue, float alpha)
{
	mR = (int)(red * MAX_COLOR_VALUE);
	mG = (int)(green * MAX_COLOR_VALUE);
	mB = (int)(blue * MAX_COLOR_VALUE);
	mA = (int)(alpha * MAX_COLOR_VALUE);
}