#pragma once

#define black Color()

class Color
{
public:
	double r, g, b;

	Color(void) : r(0.0), g(0.0), b(0.0) {};
	Color(double _r, double _g, double _b) : r(_r), g(_g), b(_b) {};

	Color addcolor(const Color &c) const;
	Color outprodc(const Color &c) const;
	Color scmpy(double s) const;
};

class AccumulatedColor {
	double r, g, b;
	int count;

public:
	AccumulatedColor(void) : r(0.0), g(0.0), b(0.0), count(1) {};
	AccumulatedColor(const Color& c) : r(c.r), g(c.g), b(c.b), count(1) {};
	AccumulatedColor(double _r, double _g, double _b) : r(_r), g(_g), b(_b), count(1) {};

	void addcolor(const Color& c);
	Color getColor() const;
};

