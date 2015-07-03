// raytrace.cpp : Defines the entry point for the console application.
//

#include "stdafx.h" 
#include "Ray.h"
#include "Color.h"
#include "Image.h"

#include "Objekt.h"
#include "QuadricObject.h"
#include "SphereObject.h"

#include <vector>
#include <iostream>
#include "Parser.h"

using namespace std;

int main(int argc, _TCHAR* argv[])
{
	Parser parser("data/test.data");
	if (!parser.start())
	{
		std::cin.get();
		return 1;
	}

	int resolutionX = parser.getResoultionX();
	int resolutionY = parser.getResoultionY();

	Vector lookAtPoint = parser.getLookatPoint();
	Vector eyePoint = parser.getEyePoint();
	Vector lookatVector = lookAtPoint.vsub(eyePoint);

	Vector up = parser.getUp();
	
	double aspect = parser.getAspectRatio();
	double fovx = parser.getFieldOfViewX();
	double fovy = parser.getFieldOfViewY();

	if (isnan(fovy)) {
		fovy = fovx / aspect;
	} else {
		fovx = fovy * aspect;
	}
	
	double width  = 2 * tan(0.5*fovx)*lookatVector.veclength();
	double height = width / aspect;
		
	Vector xdir = lookatVector.cross(up).normalize();
	Vector ydir = lookatVector.cross(xdir).normalize();

	Vector dx = xdir.svmpy(width / resolutionX);
	Vector dy = ydir.svmpy(height / resolutionY);

	Vector start = lookAtPoint;
	start = start.vadd(xdir.svmpy(-0.5*width))
			     .vadd(ydir.svmpy(-0.5*height));

	Ray	ray(Vector(), eyePoint, 0);
	Image bild(resolutionX, resolutionY);

	for (int scanline=0; scanline < resolutionY; scanline++) {
		printf("%4d\r", resolutionY-scanline);
	
		Vector renderPoint = start;
		
		for (int sx=0; sx < resolutionX; sx++) {
			ray.setDirection(renderPoint.vsub(ray.getOrigin()).normalize());

			Color color = ray.shade(parser.getObjects(), 
									parser.getLights(), 
									parser.getBackgroundColor(), 
									parser.getGlobalAmbient());

			bild.set(sx, scanline,
				color.r > 1.0 ? 255 : int(255 * color.r),
				color.g > 1.0 ? 255 : int(255 * color.g),
				color.b > 1.0 ? 255 : int(255 * color.b));

			renderPoint = renderPoint.vadd(dx);
		}

		start = start.vadd(dy);
	}

	char *name = "raytrace-bild.ppm";
	bild.save(name);

	std::cin.get();
	return 0;
}

