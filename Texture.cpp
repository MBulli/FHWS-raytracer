#include "stdafx.h"
#include "Texture.h"
#include "Color.h"
#include "lodepng.h"
#include <iostream>
#include <cassert>


Texture::~Texture()
{
}

void Texture::load()
{
	unsigned error = lodepng::decode(imgData, imgWidth, imgHeight, filename);
	if (error) {
		std::cout << "Failed to decode texture " << filename << " with error: " << error << ": " << lodepng_error_text(error) << std::endl;
	}

	// the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA...
}

Color Texture::getTexel(double u, double v) const
{
	assert((0 <= u && u <= 1));
	assert((0 <= v && v <= 1)); // u & v must be in [0;1]

	int pixelU = round(u * (imgWidth  - 1));
	int pixelV = round(v * (imgHeight - 1));

	return getPixel(pixelU, pixelV);
}

Color Texture::getPixel(int x, int y) const
{
	assert((0 <= x && x < imgWidth));
	assert((0 <= y && y < imgHeight));
	
	unsigned char R = imgData.at(y * imgWidth * 4 + x * 4 + 0);
	unsigned char G = imgData.at(y * imgWidth * 4 + x * 4 + 1);
	unsigned char B = imgData.at(y * imgWidth * 4 + x * 4 + 2);

	return Color(R / 255.0, G / 255.0, B / 255.0);
}