#ifndef FONT_H_
#define FONT_H_

#include <Trackable.h>
#include <SDL_ttf.h>
#include <Vector2D.h>

class Font : public Trackable
{
	friend class GraphicsSystem;

public:
	static Vector2D getDimensions(const Font& font, std::string text);

	Font(const std::string& fontPath, int fontSize);
	~Font();

	const int& getSize() const;

private:
	int mSize;
	TTF_Font* mpFont;

	TTF_Font* initFont(const std::string& fontPath, int fontSize);
};

#endif