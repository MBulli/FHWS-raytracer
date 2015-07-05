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
#include <thread>

using namespace std;

struct Config {
	int resolutionX;
	int resolutionY;

	Vector lookAtPoint;
	Vector eyePoint;
	Vector lookatVector;
	Vector up;

	double aspect;
	double fovx, fovy;
	double width, height;

	Vector xdir, ydir;
	Vector dx, dy;

	Color backgroundColor;
	Color globalAmbient;

	std::vector<ObjektPtr> objects;
	std::vector<Light> lights;

	Image output;

	Config(Parser& p)
		: output(0, 0)
	{
		resolutionX = p.getResoultionX();
		resolutionY = p.getResoultionY();

		lookAtPoint = p.getLookatPoint();
		eyePoint = p.getEyePoint();
		lookatVector = lookAtPoint.vsub(eyePoint);

		up = p.getUp();

		aspect = p.getAspectRatio();
		fovx = p.getFieldOfViewX();
		fovy = p.getFieldOfViewY();

		if (isnan(fovy)) {
			fovy = fovx / aspect;
		}
		else {
			fovx = fovy * aspect;
		}

		width = 2 * tan(0.5*fovx)*lookatVector.veclength();
		height = width / aspect;

		xdir = lookatVector.cross(up).normalize();
		ydir = lookatVector.cross(xdir).normalize();

		dx = xdir.svmpy(width / resolutionX);
		dy = ydir.svmpy(height / resolutionY);

		backgroundColor = p.getBackgroundColor();
		globalAmbient = p.getGlobalAmbient();

		objects.assign(p.getObjects().begin(), p.getObjects().end());
		lights.assign(p.getLights().begin(), p.getLights().end());

		output = Image(resolutionX, resolutionY);
	}
};

void tracePartition(Config& c, Parser& parser, int index, int count) 
{
	const auto& objects = c.objects;
	const auto& lights = c.lights;
	const auto& backgroundColor = c.backgroundColor;
	const auto& globalAmbient = c.globalAmbient;

	Vector start = c.lookAtPoint
					.vadd(c.xdir.svmpy(-0.5*c.width)) // move x=0 to center X
					.vadd(c.ydir.svmpy(-0.5*c.height)) // same for y=0
					.vadd(c.dy.svmpy(index*count)); // inital delta
	
	Ray	ray(Vector(), c.eyePoint, 0);

	//int start = index * count;
	int end = index*count + count;

	for (int scanline = index * count; scanline < end; scanline++) {
		//printf("%4d\r", c.resolutionY - scanline);

		Vector renderPoint = start;

		for (int sx = 0; sx < c.resolutionX; sx++) {
			ray.setDirection(renderPoint.vsub(ray.getOrigin()).normalize());

			Color color = ray.shade(objects, lights, backgroundColor, globalAmbient);

			c.output.set(sx, scanline,
				color.r > 1.0 ? 255 : int(255 * color.r),
				color.g > 1.0 ? 255 : int(255 * color.g),
				color.b > 1.0 ? 255 : int(255 * color.b));

			renderPoint = renderPoint.vadd(c.dx);
		}

		start = start.vadd(c.dy);
	}
}


int main(int argc, _TCHAR* argv[])
{
	Parser parser("data/test.data");
	if (!parser.start())
	{
		std::cin.get();
		return 1;
	}

	Config config(parser);

	const int num_threads = 1;
	int partSize = 0;
	int roundUp = static_cast<int>(remquof(config.resolutionY, num_threads, &partSize));

	std::thread t[num_threads];
	long long longestRunTime = 0;

	cout << "Will run on " << num_threads << " Threads each calculating " << partSize << " scanlines." << endl;

	for (int i = 0; i < num_threads; ++i) {
		t[i] = std::thread([&config, &parser, num_threads, i, partSize, roundUp, &longestRunTime]()
		{
			int count = partSize;
			if (i == num_threads - 1) {
				count += roundUp;
			}

			auto startTime = std::chrono::system_clock::now();

			tracePartition(config, parser, i, count);

			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - startTime);
			longestRunTime = duration.count(); // slowest thread defines the whole duration
			cout << "Thread " << i << " took " << duration.count() << "ms" << endl;
		});
	}

	// wait for threads to finish
	for (int i = 0; i < num_threads; ++i) {
		t[i].join();
	}

	cout << "Tracing took " << longestRunTime / 1000 << "sec (" << longestRunTime << "ms) in total." << endl;
	cout << "Done tracing. Writing file ..." << endl;

	char *name = "raytrace-bild.ppm";
	config.output.save(name);

	cout << "Done!" << endl;

	std::cin.get();
	return 0;
}

