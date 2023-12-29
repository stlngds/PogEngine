#pragma once
#include "bsepch.h"
class Color : public Material
{
public:
	Color() : data({ {0.0, 0.0, 0.0, 0.0} }) {}
	Color(float r, float g, float b, float a) : data({ r, g, b, a }) {}
	virtual ~Color() {}

	void SetRed(float red);
	void SetGreen(float green);
	void SetBlue(float blue);
	void SetAlpha(float alpha);
	void SetColor(int index, float value);
	std::array<float, 4> GetColor();

	std::string ToString();

private:
	std::array<float, 4> data;


};