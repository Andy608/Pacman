#include "Color.h"

Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) :
	red(r),
	green(g),
	blue(b),
	alpha(a)
{
	mHash = (r << 24) + (g << 16) + (b << 8) + a;
}

Color::Color(unsigned char r, unsigned char g, unsigned char b) :
	Color(r, g, b, 255)
{

}

bool Color::operator<(const Color& rhs) const
{
	if (mHash < rhs.mHash)
		return true;

	return false;
}