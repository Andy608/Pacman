#include <iostream>
#include "GraphicsBuffer.h"
#include "Color.h"
#include "GraphicsSystem.h"
#include <SDL.h>
#include <SDL_image.h>

GraphicsBuffer::GraphicsBuffer(SDL_Surface* pBitmapSurface) :
	mpBitmapSurface(pBitmapSurface),
	mpBitmapTexture(surfaceToTexture(pBitmapSurface)),
	mOwnsBitmap(false)
{

}

GraphicsBuffer::GraphicsBuffer(const std::string& imagePath) :
	mpBitmapSurface(loadSurface(imagePath)),
	mpBitmapTexture(surfaceToTexture(mpBitmapSurface)),
	mOwnsBitmap(true)
{

}

GraphicsBuffer::~GraphicsBuffer()
{
	if (mOwnsBitmap)
	{
		SDL_DestroyTexture(mpBitmapTexture);
		mpBitmapTexture = nullptr;

		SDL_FreeSurface(mpBitmapSurface);
		mpBitmapSurface = nullptr;
	}
}

const int& GraphicsBuffer::getWidth() const
{
	return mBitmapWidth;
}

const int& GraphicsBuffer::getHeight() const
{
	return mBitmapHeight;
}

SDL_Surface* GraphicsBuffer::loadSurface(const std::string& imagePath)
{
	SDL_Surface* pSurface = IMG_Load(imagePath.c_str());

	if (!pSurface)
	{
		std::cout << "Error loading surface: \'" << imagePath.c_str() << "\'. Error: " << IMG_GetError() << std::endl;
	}

	return pSurface;
}

SDL_Texture* GraphicsBuffer::surfaceToTexture(SDL_Surface* pSurface)
{
	SDL_Texture* pTexture = nullptr;

	pTexture = SDL_CreateTextureFromSurface(GraphicsSystem::getInstance()->getRenderer(), pSurface);

	if (!pTexture)
	{
		std::cout << "Error converting surface to texture. SDL Error: " << SDL_GetError() << std::endl;
	}

	mBitmapWidth = pSurface->w;
	mBitmapHeight = pSurface->h;

	return pTexture;
}

//https://www.gamedev.net/forums/topic/502040-sdl-get-pixel-color/
Color GraphicsBuffer::getPixelColor(int x, int y)
{
	if (SDL_MUSTLOCK(mpBitmapSurface))
		SDL_LockSurface(mpBitmapSurface);

	SDL_Color color;
	SDL_GetRGB(getPixelAsInt(x, y), mpBitmapSurface->format, &color.r, &color.g, &color.b);

	if (SDL_MUSTLOCK(mpBitmapSurface))
		SDL_UnlockSurface(mpBitmapSurface);

	return Color(color.r, color.g, color.b, 0);
}

uint32_t GraphicsBuffer::getPixelAsInt(int x, int y)
{
	int bpp = mpBitmapSurface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to retrieve */
	Uint8 *p = (Uint8 *)mpBitmapSurface->pixels + y * mpBitmapSurface->pitch + x * bpp;

	switch (bpp) {
	case 1:
		return *p;
	case 2:
		return *(Uint16 *)p;
	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return p[0] << 16 | p[1] << 8 | p[2];
		else
			return p[0] | p[1] << 8 | p[2] << 16;
	case 4:
		return *(Uint32 *)p;
	default:
		return 0;       /* shouldn't happen, but avoids warnings */
	}
}