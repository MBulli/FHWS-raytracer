#pragma once
#include <string>
#include <vector>
#include <memory>

class Color;

class Texture
{
private:
	std::string filename;
	std::vector<unsigned char> imgData;
	unsigned imgWidth, imgHeight;
public:
	Texture(const char* filename) : filename(filename){};
	~Texture();

	void load();
	Color getTexel(double u, double v) const;
	Color getPixel(int x, int y) const;
};

typedef std::shared_ptr<Texture> TexturePtr;
typedef std::shared_ptr<const Texture> TextureConstPtr;