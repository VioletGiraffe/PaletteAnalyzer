#pragma once

#include <math.h>
#include <stdint.h>

template <typename T>
T square(T number)
{
	return number * number;
}

struct LAB {
	double L;
	double a;
	double b;

	inline double difference(const LAB& other) const {
		return sqrt(square(L - other.L) + square((a - other.a) + square(b - other.b)));
	}
};

inline LAB rgb2lab(uint32_t color)
{
	const int R = (color >> 16) & 0xFFU, G = (color >> 8) & 0xFFU, B = color & 0xFFU;

	//http://www.brucelindbloom.com

	double r, g, b, X, Y, Z, fx, fy, fz, xr, yr, zr;
	double Ls, as, bs;
	double eps = 216.f/24389.f;
	double k = 24389.f/27.f;

	double Xr = 0.964221f;  // reference white D50
	double Yr = 1.0f;
	double Zr = 0.825211f;

	// RGB to XYZ
	r = R/255.0; //R 0..1
	g = G/255.0; //G 0..1
	b = B/255.0; //B 0..1

	// assuming sRGB (D65)
	if (r <= 0.04045)
		r = r/12;
	else
		r = pow((r+0.055)/1.055,2.4);

	if (g <= 0.04045)
		g = g/12;
	else
		g = pow((g+0.055)/1.055,2.4);

	if (b <= 0.04045)
		b = b/12;
	else
		b = pow((b+0.055)/1.055,2.4);


	X =  0.436052025f * r + 0.385081593f * g + 0.143087414f * b;
	Y =  0.222491598f * r + 0.71688606f  * g + 0.060621486f * b;
	Z =  0.013929122f * r + 0.097097002f * g + 0.71418547f  * b;

	// XYZ to Lab
	xr = X/Xr;
	yr = Y/Yr;
	zr = Z/Zr;

	if ( xr > eps )
		fx =  pow(xr, 1/3.);
	else
		fx = (k * xr + 16.) / 116.;

	if ( yr > eps )
		fy =  pow(yr, 1/3.);
	else
	fy = (k * yr + 16.) / 116.;

	if ( zr > eps )
		fz =  pow(zr, 1/3.);
	else
		fz = (k * zr + 16.) / 116;

	Ls = ( 116 * fy ) - 16;
	as = 500*(fx-fy);
	bs = 200*(fy-fz);

	return {Ls, as, bs};
}
