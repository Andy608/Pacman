#include "Sprite.h"
#include "GraphicsBuffer.h"

Sprite::Sprite(const GraphicsBuffer& spriteBuffer) :
	Sprite(spriteBuffer, 0, 0, spriteBuffer.getWidth(), spriteBuffer.getHeight())
{

}

Sprite::Sprite(const GraphicsBuffer& spriteBuffer, const int startingX, const int startingY, const int width, const int height) :
	mSPRITE_BUFFER(spriteBuffer),
	mSTARTING_X(startingX),
	mSTARTING_Y(startingY),
	mWIDTH(width),
	mHEIGHT(height)
{

}

Sprite::~Sprite()
{

}

const int& Sprite::getStartingX() const
{
	return mSTARTING_X;
}

const int& Sprite::getStartingY() const
{
	return mSTARTING_Y;
}

const int& Sprite::getWidth() const
{
	return mWIDTH;
}

const int& Sprite::getHeight() const
{
	return mHEIGHT;
}