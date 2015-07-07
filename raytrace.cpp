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
#include <random>

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

	Vector xdir, ydir, zdir;
	Vector dx, dy;

	Color backgroundColor;
	Color globalAmbient;

	int depthOfFieldSamples = 0;
	double apertureRadius = 0;
	double focalDistance = 0;

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
		zdir = lookatVector.normalize();

		dx = xdir.svmpy(width / resolutionX);
		dy = ydir.svmpy(height / resolutionY);

		backgroundColor = p.getBackgroundColor();
		globalAmbient = p.getGlobalAmbient();

		depthOfFieldSamples = p.getDOFSamples();
		apertureRadius = p.getApatureRadius();
		focalDistance = p.getFocalDistance();

		objects.assign(p.getObjects().begin(), p.getObjects().end());
		lights.assign(p.getLights().begin(), p.getLights().end());

		output = Image(resolutionX, resolutionY);
	}
};


Color traceDOFRay(Ray& ray, const Config& c)
{
	static std::default_random_engine generator;
	static uniform_real_distribution<double> distribution(0, 1);
	static auto random = std::bind(distribution, generator);


	const Vector focalPoint = ray.intersectionPoint(c.focalDistance);

	Color accColor;
	for (int i = 0; i < c.depthOfFieldSamples; i++)
	{
		const double a = random();
		const double b = random();

		const double x = b*c.apertureRadius*cos(2 * M_PI*a);
		const double y = b*c.apertureRadius*sin(2 * M_PI*a);

		const Vector randPoint = c.eyePoint
			.vadd(c.xdir.svmpy(x)
			.vadd(c.ydir.svmpy(y)));

		ray.setOrigin(randPoint);
		ray.setDirection(focalPoint.vsub(ray.getOrigin()).normalize());

		const Color color = ray.shade(c.objects, c.lights, c.backgroundColor, c.globalAmbient);
		accColor = accColor.addcolor(color);
	}

	accColor = accColor.scmpy(1.0 / c.depthOfFieldSamples);
	return accColor;
}

void tracePartition(Config& c, Parser& parser, int num_threads, int startScanline) 
{
	const auto& objects = c.objects;
	const auto& lights = c.lights;
	const auto& backgroundColor = c.backgroundColor;
	const auto& globalAmbient = c.globalAmbient;

	// our delta y needs to skip the other thread scanlines
	const Vector dy = c.dy.svmpy(num_threads);

	Vector start = c.lookAtPoint
					.vadd(c.xdir.svmpy(-0.5*c.width)) // move x=0 to center X
					.vadd(c.ydir.svmpy(-0.5*c.height)) // same for y=0
					.vadd(c.dy.svmpy(startScanline)); // inital delta
	
	Ray	ray(Vector(), c.eyePoint, 0);

	for (int scanline = startScanline; scanline < c.resolutionY; scanline += num_threads) {
		printf("%4d\r", c.resolutionY - scanline);

		Vector renderPoint = start;

		for (int sx = 0; sx < c.resolutionX; sx++) {

			ray.setOrigin(c.eyePoint);
			ray.setDirection(renderPoint.vsub(ray.getOrigin()).normalize());
			
			Color color;
			if (c.apertureRadius != 0.0)
			{
				color = traceDOFRay(ray, c);
			}
			else
			{
				color = ray.shade(c.objects, c.lights, c.backgroundColor, c.globalAmbient);
			}
			
			c.output.set(sx, scanline,
				color.r > 1.0 ? 255 : int(255 * color.r),
				color.g > 1.0 ? 255 : int(255 * color.g),
				color.b > 1.0 ? 255 : int(255 * color.b));

			renderPoint = renderPoint.vadd(c.dx);
		}

		start = start.vadd(dy);
	}
}


int main(int argc, _TCHAR* argv[])
{
	Parser parser("data/scene.data");
	if (!parser.start())
	{
		std::cin.get();
		return 1;
	}

	Config config(parser);

	const int num_threads = 4;
	std::thread t[num_threads];
	auto totalRunTime = std::chrono::system_clock::now();
	
	if (config.apertureRadius != 0.0)
	{
		cout << "Will render depth of field with " << config.depthOfFieldSamples << " samples per ray!! (Take a coffee break)" << endl;
	}
	cout << "Will run on " << num_threads << " threads." << endl;

	for (int i = 0; i < num_threads; ++i) {
		t[i] = std::thread([&config, &parser, num_threads, i]()
		{
			auto threadStartTime = std::chrono::system_clock::now();

			tracePartition(config, parser, num_threads, i);

			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - threadStartTime);
			cout << "Thread " << i << " took " << duration.count() << "ms" << endl;
		});
	}

	// wait for threads to finish
	for (int i = 0; i < num_threads; ++i) {
		t[i].join();
	}

	auto totalRunDuration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - totalRunTime);

	cout << "Tracing took " << totalRunDuration.count() / 1000 << "sec (" << totalRunDuration.count() << "ms) in total." << endl;
	cout << "Done tracing. Writing file ..." << endl;

	char *name = "raytrace-bild.ppm";
	config.output.save(name);

	cout << "Done!" << endl;

	std::cin.get();
	return 0;
}

