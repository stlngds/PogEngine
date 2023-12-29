#include "bsepch.h"

void Color::SetRed(float red)
{
	data[0] = red;
}

void Color::SetGreen(float green)
{
	data[1] = green;
}

void Color::SetBlue(float blue)
{
	data[2] = blue;
}

void Color::SetAlpha(float alpha)
{
	data[3] = alpha;
}

void Color::SetColor(int index, float value)
{
	data[index] = value;
}

std::array<float, 4> Color::GetColor()
{
	return data;
}

std::string Color::ToString()
{
	std::string str;
	str.append(std::to_string(data[0])).
		append(", ").
		append(std::to_string(data[1])).
		append(", ").
		append(std::to_string(data[2]));
	return str;
}