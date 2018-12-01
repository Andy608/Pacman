#ifndef SPRITE_SHEET_H_
#define SPRITE_SHEET_H_

#include <Trackable.h>
#include <vector>

class GraphicsBuffer;
class Sprite;

class SpriteSheet : public Trackable
{
public:
	SpriteSheet(const GraphicsBuffer& spriteSheetBuffer, unsigned int rows, unsigned int columns, unsigned int spriteWidths, unsigned int spriteHeights);
	SpriteSheet(const GraphicsBuffer& spriteSheetBuffer, unsigned int rows, unsigned int columns);
	virtual ~SpriteSheet();

	const std::vector<Sprite*>& getSprites() const;

private:
	const GraphicsBuffer& mSPRITESHEET_BUFFER;
	const unsigned int mROWS;
	const unsigned int mCOLUMNS;
	const unsigned int mSPRITE_WIDTHS;
	const unsigned int mSPRITE_HEIGHTS;

	std::vector<Sprite*> mSprites;
};

#endif