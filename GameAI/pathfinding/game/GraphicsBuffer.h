#ifndef GRAPHICS_BUFFER_H_
#define GRAPHICS_BUFFER_H_

#include <Trackable.h>

struct SDL_Surface;
struct SDL_Texture;
struct Color;

class GraphicsBuffer : public Trackable
{
	friend class GraphicsSystem;

public:
	explicit GraphicsBuffer(const std::string& imagePath);
	~GraphicsBuffer();

	const int& getWidth() const;
	const int& getHeight() const;
	Color getPixelColor(int x, int y) const;

private:
	explicit GraphicsBuffer(SDL_Surface* pBitmapSurface);
	SDL_Surface* mpBitmapSurface;
	SDL_Texture* mpBitmapTexture;
	int mBitmapWidth;
	int mBitmapHeight;
	bool mOwnsBitmap;

	SDL_Surface* loadSurface(const std::string& imagePath);
	SDL_Texture* surfaceToTexture(SDL_Surface* pSurface);

	uint32_t getPixelAsInt(int x, int y) const;
};

#endif