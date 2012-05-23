#include "scale.h"

Scale::Scale(int width, int height):width(width),height(height)
{
}

void Scale::set_width(int width)
{
	this->width = width;
}

void Scale::set_height(int height)
{
	this->height = height;
}

void Scale::set_scale(int width, int height)
{
	this->width = width;
	this->height = height;
}

int Scale::get_width()
{
	return width;
}

int Scale::get_height()
{
	return height;
}