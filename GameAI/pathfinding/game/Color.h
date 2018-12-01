#ifndef COLOR_H_
#define COLOR_H_

#include <Trackable.h>

struct Color : public Trackable
{
	friend class GraphicsSystem;
	friend class GraphicsBuffer;

	Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	Color(unsigned char r, unsigned char g, unsigned char b);

	bool operator<(const Color& rhs) const;

	unsigned char red;
	unsigned char green;
	unsigned char blue;
	unsigned char alpha;
	size_t mHash;

	bool operator==(const Color& another)
	{
		return (red == another.red && green == another.green && blue == another.blue && alpha == another.alpha);
	}
};

#endif